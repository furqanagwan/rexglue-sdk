/**
 * @file        rexglue/commands/test_recompiler.cpp
 * @brief       Recompiler test command implementation
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include "test_recompiler.h"
#include "../ui/ui.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <CLI/CLI.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include <rex/codegen/binary_view.h>
#include <rex/codegen/codegen_context.h>
#include <rex/codegen/function_graph.h>
#include <rex/codegen/function_scanner.h>
#include <rex/codegen/template_registry.h>
#include <rex/codegen/test_support.h>
#include <rex/logging.h>
#include <rex/string.h>
#include <rex/system/map_parser.h>

#include "codegen/template_registry_internal.h"

namespace rexglue::cli {

namespace {

namespace fs = std::filesystem;
namespace codegen = rex::codegen;

constexpr uint32_t kTestBaseAddress = 0x82010000;

struct RegValue {
  std::string reg;
  std::string value;
  bool is_vector = false;
  bool is_float = false;
  std::string vec_values[4];
};

struct MemValue {
  std::string address;
  std::vector<uint8_t> data;
};

struct TestSpec {
  std::string name;
  std::string symbol;
  std::vector<RegValue> inputs;
  std::vector<RegValue> outputs;
  std::vector<MemValue> mem_inputs;
  std::vector<MemValue> mem_outputs;
};

std::map<size_t, std::string> ParseMapFile(const std::string& mapPath) {
  std::map<size_t, std::string> symbols;
  rex::runtime::MapParseOptions options;
  options.base_address = kTestBaseAddress;

  auto result = rex::runtime::ParseNmMap(mapPath, options);
  if (!result)
    return symbols;
  for (const auto& sym : *result) {
    if (sym.name.empty() || sym.name[0] == '.')
      continue;
    symbols[sym.address] = sym.name;
  }
  return symbols;
}

std::vector<uint8_t> ParseHexBytes(std::string hex) {
  // "ABCD12" or, as hardware captures write them, "[AB, CD, 12]".
  std::erase_if(hex, [](char c) { return c == '[' || c == ']' || c == ',' || c == ' '; });
  std::vector<uint8_t> result;
  for (size_t i = 0; i < hex.size(); i += 2) {
    if (i + 1 >= hex.size())
      break;
    if (hex[i] == ' ') {
      i--;
      continue;
    }
    uint8_t val = 0;
    std::from_chars(&hex[i], &hex[i + 2], val, 16);
    result.push_back(val);
  }
  return result;
}

/* Source order is high-to-low; stored low-to-high to match runtime layout. */
RegValue ParseVectorRegister(const std::string& line, std::string reg, size_t after) {
  RegValue rv;
  rv.reg = std::move(reg);
  rv.is_vector = true;
  auto open = line.find('[', after + 1);
  auto c0 = line.find(',', open + 1);
  auto c1 = line.find(',', c0 + 1);
  auto c2 = line.find(',', c1 + 1);
  auto close = line.find(']', c2 + 1);
  rv.vec_values[3] = line.substr(open + 1, c0 - open - 1);
  rv.vec_values[2] = line.substr(c0 + 2, c1 - c0 - 2);
  rv.vec_values[1] = line.substr(c1 + 2, c2 - c1 - 2);
  rv.vec_values[0] = line.substr(c2 + 2, close - c2 - 2);
  return rv;
}

RegValue ParseRegisterDirective(const std::string& line, size_t directive_idx) {
  auto sp1 = line.find(' ', directive_idx);
  auto sp2 = line.find(' ', sp1 + 1);
  std::string reg = line.substr(sp1 + 1, sp2 - sp1 - 1);
  if (!reg.empty() && reg[0] == 'v')
    return ParseVectorRegister(line, std::move(reg), sp2);

  RegValue rv;
  rv.reg = std::move(reg);
  rv.value = rex::string::trim_string(line.substr(sp2 + 1));
  // A bracketed scalar ("f4 [3FF0000000000000]") is the register's bits.
  if (rv.value.size() > 2 && rv.value.front() == '[' && rv.value.back() == ']') {
    rv.value = "0x" + rv.value.substr(1, rv.value.size() - 2);
    return rv;
  }
  rv.is_float = (line.find('.', sp2) != std::string::npos);
  return rv;
}

MemValue ParseMemoryDirective(const std::string& line, size_t directive_idx) {
  auto sp1 = line.find(' ', directive_idx);
  auto sp2 = line.find(' ', sp1 + 1);
  MemValue mv;
  mv.address = line.substr(sp1 + 1, sp2 - sp1 - 1);
  // Hardware captures write "0x0000000010001000"; the template adds the 0x.
  if (mv.address.starts_with("0x") || mv.address.starts_with("0X")) {
    mv.address = mv.address.substr(2);
  }
  mv.data = ParseHexBytes(line.substr(sp2 + 1));
  return mv;
}

void ApplyDirective(const std::string& line, std::string_view reg_token, std::string_view mem_token,
                    std::vector<RegValue>& regs, std::vector<MemValue>& mems) {
  if (line.size() <= 1 || line[1] != '_')
    return;
  if (auto idx = line.find(reg_token); idx != std::string::npos) {
    regs.push_back(ParseRegisterDirective(line, idx));
  } else if (auto idx2 = line.find(mem_token); idx2 != std::string::npos) {
    mems.push_back(ParseMemoryDirective(line, idx2));
  }
}

std::string BuildHierarchicalName(const std::string& stem, const std::string& label) {
  if (stem.starts_with("instr_")) {
    std::string group = stem.substr(6);
    std::string prefix = "test_" + group + "_";
    if (label.starts_with(prefix))
      return group + ".test_" + label.substr(prefix.size());
    if (label == "test_" + group)
      return group + ".test";
    return group + "." + label;
  }
  if (stem.starts_with("seq_")) {
    if (label.starts_with("seq_"))
      return "seq.test_" + label.substr(4);
    return "seq." + label;
  }
  return stem + "." + label;
}

std::vector<TestSpec> ParseTestSpecs(const std::string& asmPath,
                                     const std::unordered_map<std::string, std::string>& symbols) {
  std::vector<TestSpec> specs;
  std::ifstream in(asmPath);
  if (!in.is_open()) {
    REXLOG_WARN("Unable to open assembly file: {}", asmPath);
    return specs;
  }

  std::string line;
  bool in_block_comment = false;
  auto getline = [&]() -> bool {
    while (std::getline(in, line)) {
      line = rex::string::trim_string(line);
      if (in_block_comment) {
        auto end = line.find("*/");
        if (end == std::string::npos)
          continue;
        in_block_comment = false;
        line = rex::string::trim_string(line.substr(end + 2));
        if (line.empty())
          continue;
      }
      if (auto start = line.find("/*"); start != std::string::npos) {
        if (auto end = line.find("*/", start + 2); end != std::string::npos) {
          line = line.substr(0, start) + line.substr(end + 2);
        } else {
          in_block_comment = true;
          line = line.substr(0, start);
        }
        line = rex::string::trim_string(line);
        if (line.empty())
          continue;
      }
      return true;
    }
    return false;
  };

  while (getline()) {
    if (line.empty() || line[0] == '#')
      continue;
    auto colonIndex = line.find(':');
    if (colonIndex == std::string::npos)
      continue;
    auto name = line.substr(0, colonIndex);
    if (name == "__rex_test_setjmp" || name == "__rex_test_longjmp")
      continue;  // Helper entries are emitted, but have no standalone test spec.
    auto symbolIt = symbols.find(name);
    if (symbolIt == symbols.end())
      continue;

    TestSpec spec;
    spec.name = name;
    spec.symbol = symbolIt->second;

    while (getline() && !line.empty() && line[0] == '#') {
      ApplyDirective(line, "REGISTER_IN", "MEMORY_IN", spec.inputs, spec.mem_inputs);
    }
    while (line.empty() || line[0] != '#') {
      if (!getline())
        break;
    }
    do {
      ApplyDirective(line, "REGISTER_OUT", "MEMORY_OUT", spec.outputs, spec.mem_outputs);
    } while (getline() && !line.empty() && line[0] == '#');

    if (!spec.inputs.empty() || !spec.outputs.empty() || !spec.mem_inputs.empty() ||
        !spec.mem_outputs.empty()) {
      specs.push_back(std::move(spec));
    }
  }
  return specs;
}

nlohmann::json SerializeRegisters(const std::vector<RegValue>& regs) {
  nlohmann::json arr = nlohmann::json::array();
  for (const auto& rv : regs) {
    nlohmann::json reg;
    reg["reg"] = rv.reg;
    if (rv.reg == "cr" || rv.reg == "xer") {
      reg["type"] = rv.reg;
      reg["value"] = rv.value;
    } else if (rv.reg == "xer") {
      reg["type"] = "xer";  // SO, OV and CA are bits 31, 30 and 29
      reg["value"] = rv.value;
    } else if (rv.is_vector) {
      reg["type"] = "vector";
      reg["values"] = {rv.vec_values[3], rv.vec_values[2], rv.vec_values[1], rv.vec_values[0]};
    } else if (rv.is_float) {
      reg["type"] = "float";
      reg["value"] = rv.value;
    } else {
      reg["type"] = "gpr";
      reg["value"] = rv.value;
    }
    arr.push_back(reg);
  }
  return arr;
}

nlohmann::json SerializeMemory(const std::vector<MemValue>& mems) {
  nlohmann::json arr = nlohmann::json::array();
  for (const auto& mv : mems) {
    nlohmann::json mem;
    mem["address"] = mv.address;
    nlohmann::json bytes = nlohmann::json::array();
    for (size_t i = 0; i < mv.data.size(); ++i) {
      bytes.push_back(
          {{"offset", fmt::format("{:X}", i)}, {"value", fmt::format("{:02X}", mv.data[i])}});
    }
    mem["bytes"] = bytes;
    arr.push_back(mem);
  }
  return arr;
}

std::string CategoryFromStem(std::string_view stem) {
  auto contains = [&](std::string_view s) { return stem.find(s) != std::string_view::npos; };
  if (contains("add") || contains("sub") || contains("mul") || contains("div"))
    return "arithmetic";
  if (contains("cmp"))
    return "comparison";
  if (contains("and") || contains("or") || contains("xor") || contains("rl"))
    return "logical";
  if (stem.starts_with("f") || contains("_f"))
    return "floating_point";
  if (stem.starts_with("v") || contains("_v"))
    return "vector";
  if (stem.starts_with("l") || stem.starts_with("st"))
    return "memory";
  return "misc";
}

// Labels named one per line ("#" comments allowed), e.g. Edge's skip.txt.
// With `with_reason`, the rest of a line after the label is kept.
std::unordered_map<std::string, std::string> ReadLabelList(const std::string& path,
                                                           bool with_reason) {
  std::unordered_map<std::string, std::string> labels;
  if (path.empty()) {
    return labels;
  }
  std::ifstream in(path);
  if (!in.is_open()) {
    REXLOG_WARN("Unable to open label list: {}", path);
    return labels;
  }
  std::string line;
  while (std::getline(in, line)) {
    line = rex::string::trim_string(line);
    if (line.empty() || line[0] == '#') {
      continue;
    }
    const auto space = line.find_first_of(" \t");
    std::string label = line.substr(0, space);
    std::string reason =
        space == std::string::npos ? "" : rex::string::trim_string(line.substr(space + 1));
    labels.emplace(std::move(label), with_reason ? std::move(reason) : "");
  }
  return labels;
}

// A file's cases as ppc_table data (ppc_table_runner.h) and one TEST_CASE
// that runs them. Each case carries its known failure cause, or nullptr.
std::string EmitTable(const std::string& stem, const std::string& category,
                      const std::vector<std::pair<const TestSpec*, const std::string*>>& cases) {
  std::string ops, list, pool;
  size_t op_count = 0, pool_size = 0;
  // Some captures already carry a suffix ("0x...ull").
  auto u64 = [](const std::string& v) {
    const char last = v.empty() ? '0' : char(std::tolower(uint8_t(v.back())));
    return last == 'l' || last == 'u' ? v : v + "ULL";
  };
  // u32[3], u32[2] in the high half; u32[1], u32[0] in the low half.
  auto vec_hi = [](const RegValue& rv) {
    return fmt::format("0x{:0>8}{:0>8}ULL", rv.vec_values[3], rv.vec_values[2]);
  };
  auto vec_lo = [](const RegValue& rv) {
    return fmt::format("0x{:0>8}{:0>8}ULL", rv.vec_values[1], rv.vec_values[0]);
  };
  auto add_op = [&](std::string_view kind, std::string_view reg, const std::string& where,
                    const std::string& a, const std::string& b) {
    ops += fmt::format("{{{},\"{}\",{},{},{}}},\n", kind, reg, where, a, b);
    ++op_count;
  };
  auto add_bytes = [&](const std::vector<uint8_t>& bytes) {
    const size_t at = pool_size;
    for (uint8_t b : bytes)
      pool += fmt::format("0x{:02X},", b);
    pool += '\n';
    pool_size += bytes.size();
    return std::to_string(at);
  };
  auto offset = [](const std::string& reg) { return fmt::format("O({})", reg); };
  for (const auto& [spec, known] : cases) {
    const size_t first = op_count;
    for (const auto& rv : spec->inputs) {
      if (rv.reg == "cr")
        add_op("kSetCr", "cr", "0", u64(rv.value), "0");
      else if (rv.reg == "xer")
        add_op("kSetXer", "xer", "0", u64(rv.value), "0");
      else if (rv.is_vector)
        add_op("kSetVec", rv.reg, offset(rv.reg), vec_hi(rv), vec_lo(rv));
      else if (rv.is_float)
        add_op("kSetU64", rv.reg, offset(rv.reg), fmt::format("F({})", rv.value), "0");
      else
        add_op("kSetU64", rv.reg, offset(rv.reg), u64(rv.value), "0");
    }
    for (const auto& mv : spec->mem_outputs)
      add_op("kZeroMem", "memory", "0x" + mv.address, "0", std::to_string(mv.data.size()));
    for (const auto& mv : spec->mem_inputs)
      add_op("kSetMem", "memory", "0x" + mv.address, add_bytes(mv.data),
             std::to_string(mv.data.size()));
    for (const auto& rv : spec->outputs) {
      if (rv.reg == "cr")
        add_op("kCheckCr", "cr", "0", u64(rv.value), "0");
      else if (rv.reg == "xer")
        add_op("kCheckXer", "xer", "0", u64(rv.value), "0");
      else if (rv.is_vector)
        add_op("kCheckVec", rv.reg, offset(rv.reg), vec_hi(rv), vec_lo(rv));
      else if (rv.is_float)
        add_op("kCheckF64", rv.reg, offset(rv.reg), fmt::format("F({})", rv.value), "0");
      else
        add_op("kCheckU64", rv.reg, offset(rv.reg), u64(rv.value), "0");
    }
    for (const auto& mv : spec->mem_outputs)
      add_op("kCheckMem", "memory", "0x" + mv.address, add_bytes(mv.data),
             std::to_string(mv.data.size()));
    std::string cause = "nullptr";
    if (known) {
      cause = "\"";
      for (char ch : *known)
        cause += (ch == '"' || ch == '\\') ? ' ' : ch;
      cause += "\"";
    }
    list += fmt::format("    {{\"{}\", {}, {}, {}, {}}},\n", spec->name, spec->symbol, first,
                        op_count - first, cause);
  }
  std::string out = fmt::format("namespace ppc_table_{} {{\n", stem);
  out += fmt::format("const uint8_t kPool[] = {{\n{}0}};\n", pool);
  out += fmt::format("const ppc_table::Op kOps[] = {{\n{}}};\n", ops);
  out += fmt::format("const ppc_table::Case kCases[] = {{\n{}}};\n}}  // namespace\n", list);
  out += fmt::format(
      "TEST_CASE(\"ppc_corpus/{0}\", \"[ppc][{1}][{0}]\") {{\n"
      "  ppc_table::RunCases(\"{0}\", ppc_table_{0}::kCases, std::size(ppc_table_{0}::kCases),\n"
      "                      ppc_table_{0}::kOps, ppc_table_{0}::kPool);\n}}\n\n",
      stem, category);
  return out;
}

struct RecompileOptions {
  std::string bin_dir, asm_dir, out_dir;
  // Output split over this many function and case files, so a large corpus
  // compiles in parallel; 1 writes ppc_test_functions.cpp and
  // ppc_test_cases.cpp as before.
  size_t chunks = 1;
  std::string skip_list;       // test labels left out (captures judged wrong)
  std::string known_failures;  // labels expected to fail, each with its cause
  // Cases as data run from one loop per file (ppc_table_runner.h), for a
  // corpus too large for a Catch2 test per case.
  bool table = false;
};

bool RecompileTests(const RecompileOptions& opts) {
  const std::string_view binDir = opts.bin_dir, asmDir = opts.asm_dir, outDir = opts.out_dir;
  std::array<ui::KeyValueRow, 3> header_rows = {{
      {"Bin dir", std::string(binDir)},
      {"ASM dir", std::string(asmDir)},
      {"Output dir", std::string(outDir)},
  }};
  ui::KeyValueBlock("Recompiling PPC tests:", header_rows);

  fs::create_directories(outDir);
  const auto skip = ReadLabelList(opts.skip_list, false);
  const auto known_failures = ReadLabelList(opts.known_failures, true);

  struct FileOutput {
    std::string code;
    std::vector<std::string> function_names;
    std::unordered_set<size_t> addresses;
    std::map<size_t, std::string> symbols;
  };
  std::map<std::string, FileOutput> files;

  for (const auto& entry : fs::directory_iterator(binDir)) {
    if (entry.path().extension() != ".bin")
      continue;
    auto stem = entry.path().stem().string();
    REXLOG_DEBUG("Processing binary file: {}", stem);

    std::vector<uint8_t> fileData;
    {
      std::ifstream file(entry.path(), std::ios::binary | std::ios::ate);
      if (!file) {
        REXLOG_WARN("Failed to load binary file: {}", entry.path().string());
        continue;
      }
      auto size = file.tellg();
      file.seekg(0, std::ios::beg);
      fileData.resize(static_cast<size_t>(size));
      file.read(reinterpret_cast<char*>(fileData.data()), size);
    }
    if (fileData.empty())
      continue;

    auto mapPath = fmt::format("{}/{}.map", binDir, stem);
    auto symbols = ParseMapFile(mapPath);
    if (symbols.empty()) {
      REXLOG_ERROR("No symbols found in map file: {}", mapPath);
      continue;
    }

    codegen::TestModule module;
    module.Load(kTestBaseAddress, fileData.data(), fileData.size());
    module.set_name(stem);

    codegen::RecompilerConfig config;
    config.outDirectoryPath = std::string(outDir);
    auto ctx =
        codegen::CodegenContext::Create(codegen::BinaryView::fromModule(module), std::move(config));

    codegen::AnalyzeTestBinary(ctx, stem, symbols, kTestBaseAddress, fileData.data(),
                               fileData.size());

    REXLOG_DEBUG("  Found {} functions", ctx.graph.functionCount());

    std::vector<const codegen::FunctionNode*> functions;
    for (const auto& [addr, node] : ctx.graph.functions())
      functions.push_back(node.get());
    std::sort(functions.begin(), functions.end(),
              [](const auto* a, const auto* b) { return a->base() < b->base(); });

    codegen::EmitContext emitCtx{ctx.binary(), ctx.Config(), ctx.graph, 0, nullptr};

    FileOutput& out = files[stem];
    out.symbols = std::move(symbols);
    for (const auto* fn : functions) {
      std::string code = fn->emitCpp(emitCtx);
      if (code.empty())
        continue;
      out.addresses.emplace(fn->base());
      out.function_names.push_back(fmt::format("{}_{:X}", stem, fn->base()));
      out.code += code;
    }
  }

  // Each file's labels name its own functions: files reuse labels (both
  // instr_vcmpbfp.s and instr_vcmpxxfp.s have test_vcmpbfp_1).
  auto labels_of = [](const std::string& stem, const FileOutput& out) {
    std::unordered_map<std::string, std::string> labels;
    for (const auto& [addr, name] : out.symbols) {
      if (out.addresses.count(addr))
        labels.emplace(name, fmt::format("{}_{:X}", stem, addr));
    }
    return labels;
  };

  nlohmann::json allFunctions = nlohmann::json::array();
  for (const auto& [stem, out] : files) {
    for (const auto& name : out.function_names)
      allFunctions.push_back({{"name", name}});
  }
  auto base_data = [&] {
    nlohmann::json data;
    data["functions"] = allFunctions;
    data["image_base"] = "82010000";
    data["image_size"] = "100000";
    data["code_base"] = "82010000";
    data["code_size"] = "100000";
    return data;
  };

  const size_t chunks = std::max<size_t>(1, opts.chunks);
  std::vector<nlohmann::json> chunkTests(chunks, nlohmann::json::array());
  std::vector<std::string> chunkCode(chunks);
  std::vector<nlohmann::json> chunkFunctions(chunks, nlohmann::json::array());
  std::vector<std::string> chunkTables(chunks);
  size_t totalTests = 0, skipped = 0, expected_failures = 0, fileIndex = 0;
  for (const auto& [stem, out] : files) {
    const size_t chunk = fileIndex++ % chunks;
    chunkCode[chunk] += out.code + '\n';
    for (const auto& name : out.function_names)
      chunkFunctions[chunk].push_back({{"name", name}});
    auto specs = ParseTestSpecs(fmt::format("{}/{}.s", asmDir, stem), labels_of(stem, out));
    std::string category = CategoryFromStem(stem);
    std::vector<std::pair<const TestSpec*, const std::string*>> table_cases;
    for (const auto& spec : specs) {
      // Edge's skip.txt names labels without their "test_" prefix.
      const std::string bare = spec.name.starts_with("test_") ? spec.name.substr(5) : spec.name;
      if (skip.contains(spec.name) || skip.contains(bare)) {
        ++skipped;
        continue;
      }
      nlohmann::json testJson;
      testJson["name"] = BuildHierarchicalName(stem, spec.name);
      testJson["category"] = category;
      testJson["stem"] = stem;
      testJson["symbol"] = spec.symbol;
      // Catch2 reports a known failure that passes, so a fix shows too.
      // Keyed "stem/label": files reuse labels.
      if (auto known = known_failures.find(fmt::format("{}/{}", stem, spec.name));
          known != known_failures.end()) {
        testJson["known_failure"] = true;
        testJson["known_failure_reason"] = known->second;
        ++expected_failures;
      } else {
        testJson["known_failure"] = false;
      }
      ++totalTests;
      if (opts.table) {
        auto known = known_failures.find(fmt::format("{}/{}", stem, spec.name));
        table_cases.emplace_back(&spec, known != known_failures.end() ? &known->second : nullptr);
        continue;
      }
      testJson["inputs"]["registers"] = SerializeRegisters(spec.inputs);
      testJson["inputs"]["memory"] = SerializeMemory(spec.mem_inputs);
      testJson["outputs"]["registers"] = SerializeRegisters(spec.outputs);
      testJson["outputs"]["memory"] = SerializeMemory(spec.mem_outputs);
      chunkTests[chunk].push_back(testJson);
    }
    if (!table_cases.empty())
      chunkTables[chunk] += EmitTable(stem, category, table_cases);
  }

  codegen::TemplateRegistry registry;
  auto writeRendered = [&](std::string_view templateId, const nlohmann::json& data,
                           const std::string& filename) {
    auto rendered = codegen::renderWithJson(registry, std::string(templateId), data);
    std::ofstream out(fmt::format("{}/{}", outDir, filename));
    out << rendered;
  };
  const nlohmann::json shared = base_data();
  writeRendered("test/ppc_config_h", shared, "ppc_config.h");
  writeRendered("test/ppc_test_decls_h", shared, "ppc_test_decls.h");
  if (opts.table)
    writeRendered("test/ppc_table_runner_h", shared, "ppc_table_runner.h");
  for (size_t i = 0; i < chunks; ++i) {
    const std::string suffix = chunks == 1 ? "" : fmt::format("_{}", i);
    nlohmann::json data = base_data();
    data["functions"] = chunkFunctions[i];
    data["functions_code"] = chunkCode[i];
    data["tests"] = chunkTests[i];
    writeRendered("test/ppc_test_functions_cpp", data,
                  fmt::format("ppc_test_functions{}.cpp", suffix));
    if (opts.table) {
      data["table_code"] = chunkTables[i];
      writeRendered("test/ppc_test_table_cpp", data, fmt::format("ppc_test_cases{}.cpp", suffix));
    } else {
      writeRendered("test/ppc_test_cases_cpp", data, fmt::format("ppc_test_cases{}.cpp", suffix));
    }
  }

  REXLOG_INFO("Generated {} test cases in {} chunk(s); {} skipped, {} expected to fail", totalTests,
              chunks, skipped, expected_failures);
  return true;
}

struct RecompileTestsArgs {
  std::string bin_dir;
  std::string asm_dir;
  std::string output;
  size_t chunks = 1;
  std::string skip_list;
  std::string known_failures;
  bool table = false;
};

}  // namespace

void RegisterRecompileTests(CLI::App& parent, const CliContext& ctx, DeferredAction& pending) {
  (void)ctx;
  auto args = std::make_shared<RecompileTestsArgs>();
  auto* sub = parent.add_subcommand("recompile-tests", "Generate Catch2 tests from PPC assembly")
                  ->fallthrough();
  sub->add_option("--bin-dir", args->bin_dir, "Directory containing linked .bin and .map files")
      ->type_name("PATH")
      ->required();
  sub->add_option("--asm-dir", args->asm_dir, "Directory containing .s assembly source files")
      ->type_name("PATH")
      ->required();
  sub->add_option("--output", args->output, "Output path for recompile-tests")
      ->type_name("PATH")
      ->required();
  sub->add_option("--chunks", args->chunks,
                  "Split the generated sources over this many files (default 1)");
  sub->add_option("--skip-list", args->skip_list, "Test labels to leave out, one per line")
      ->type_name("PATH");
  sub->add_option("--known-failures", args->known_failures,
                  "Test labels expected to fail, one per line with their cause")
      ->type_name("PATH");
  sub->add_flag("--table", args->table,
                "Emit the cases as data run from one test per file, for a large corpus");
  sub->callback([args, &pending]() {
    pending = [args]() -> rex::Result<void> {
      RecompileOptions opts{args->bin_dir,   args->asm_dir,        args->output, args->chunks,
                            args->skip_list, args->known_failures, args->table};
      if (!RecompileTests(opts)) {
        return Err<void>(rex::ErrorCategory::Validation, "Test recompilation failed");
      }
      return rex::Ok();
    };
  });
}

}  // namespace rexglue::cli
