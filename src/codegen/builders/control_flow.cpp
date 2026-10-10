/**
 * @file        rexcodegen/builders/control_flow.cpp
 * @brief       PPC control flow instruction code generation
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include "builder_context.h"
#include "helpers.h"

#include <fmt/format.h>

#include <rex/logging.h>

#include "../codegen_logging.h"

namespace rex::codegen {

bool BuildB(BuilderContext& ctx) {
  uint32_t target = ctx.insn.operands[0];

  auto kind = ctx.graph().classifyTarget(target, ctx.base, false, &ctx.fn);

  switch (kind) {
    case TargetKind::InternalLabel:

      ctx.println("\tgoto loc_{:X};", target);
      break;

    case TargetKind::Function:
    case TargetKind::Import:

      ctx.emit_function_call(target);
      ctx.println("\treturn;");
      break;

    case TargetKind::Unknown:

      if (target >= ctx.fn.base() && target < ctx.fn.end()) {
        ctx.println("\tgoto loc_{:X};", target);
      } else {
        REXCODEGEN_WARN("Unresolved b target 0x{:08X} from 0x{:08X}", target, ctx.base);
        ctx.emit_function_call(target);
        ctx.println("\treturn;");
      }
      break;
  }
  return true;
}

bool BuildBl(BuilderContext& ctx) {
  uint32_t target = ctx.insn.operands[0];

  if (!ctx.config().skipLr)
    ctx.println("\tctx.lr = 0x{:X};", ctx.base + 4);

  auto kind = ctx.graph().classifyTarget(target, ctx.base, true, &ctx.fn);

  switch (kind) {
    case TargetKind::InternalLabel:

      ctx.println("\tgoto loc_{:X};", target);
      break;

    case TargetKind::Function:
    case TargetKind::Import:
      ctx.emit_function_call(target);
      ctx.csrState = CSRState::Unknown;
      break;

    case TargetKind::Unknown:
      REXCODEGEN_ERROR("Unresolved bl target 0x{:08X} from 0x{:08X}", target, ctx.base);
      ctx.println("\t// ERROR: unresolved bl target 0x{:08X}", target);
      ctx.println("\tREX_FATAL(\"Unresolved call from 0x{:08X} to 0x{:08X}\");", ctx.base, target);
      break;
  }
  return true;
}

bool BuildBlr(BuilderContext& ctx) {
  ctx.println("\treturn;");
  return true;
}

bool BuildBlrl(BuilderContext& ctx) {
  ctx.println("\t{{ auto old_lr = ctx.lr;");
  if (!ctx.config().skipLr)
    ctx.println("\tctx.lr = 0x{:X};", ctx.base + 4);
  ctx.println("\tREX_CALL_INDIRECT_FUNC(uint32_t(old_lr)); }}");
  ctx.csrState = CSRState::Unknown;
  return true;
}

bool BuildBctr(BuilderContext& ctx) {
  const JumpTable* jt = ctx.activeJumpTable;

  if (!jt) {
    for (const auto& autoJt : ctx.fn.jumpTables()) {
      if (autoJt.bctrAddress == ctx.base) {
        jt = &autoJt;
        break;
      }
    }
  }

  if (jt) {
    ctx.println("\tswitch ({}.u32) {{", ctx.r(jt->indexRegister));

    for (size_t i = 0; i < jt->targets.size(); i++) {
      ctx.println("\tcase {}:", i);
      auto label = jt->targets[i];

      if (label == 0) {
        ctx.println("\t\t__builtin_trap(); // ERROR - detected jump to null value");
        continue;
      }

      auto kind = ctx.graph().classifyTarget(label, ctx.base, false, &ctx.fn);
      switch (kind) {
        case TargetKind::InternalLabel:
          ctx.println("\t\tgoto loc_{:X};", label);
          break;
        case TargetKind::Function:
        case TargetKind::Import:
          if (auto* targetFn = ctx.graph().getFunction(label)) {
            ctx.emitCtx.reference(targetFn->name());
            ctx.println("\t\t{}(ctx, base);", targetFn->name());
          } else {
            REXCODEGEN_ERROR(
                "Jump target 0x{:08X} classified as function but not in graph at bctr 0x{:08X}",
                label, ctx.base);
            ctx.println(
                "\t\tREX_FATAL(\"Jump target 0x{:08X} classified as function but not "
                "in graph at bctr 0x{:08X}\");",
                label, ctx.base);
          }
          ctx.println("\t\treturn;");
          break;
        default:
          REXCODEGEN_ERROR("Jump target 0x{:08X} unresolved at bctr 0x{:08X}", label, ctx.base);
          ctx.println("\t\tREX_FATAL(\"Jump target 0x{:08X} unresolved at bctr 0x{:08X}\");", label,
                      ctx.base);
          break;
      }
    }

    ctx.println("\tdefault:");
    ctx.println("\t\t__builtin_trap(); // Switch case out of range");
    ctx.println("\t}}");

    ctx.reset_switch_table();
  } else {
    ctx.println("\tREX_CALL_INDIRECT_FUNC({}.u32);", ctx.ctr());
    ctx.println("\treturn;");
  }
  return true;
}

bool BuildBctrl(BuilderContext& ctx) {
  if (!ctx.config().skipLr)
    ctx.println("\tctx.lr = 0x{:X};", ctx.base + 4);
  ctx.println("\tREX_CALL_INDIRECT_FUNC({}.u32);", ctx.ctr());
  ctx.csrState = CSRState::Unknown;
  return true;
}

bool BuildBnectr(BuilderContext& ctx) {
  ctx.println("\tif (!{}.eq) {{", ctx.cr(ctx.insn.operands[0]));
  ctx.println("\t\tREX_CALL_INDIRECT_FUNC({}.u32);", ctx.ctr());
  ctx.println("\t\treturn;");
  ctx.println("\t}}");
  return true;
}

bool BuildBdz(BuilderContext& ctx) {
  ctx.println("\t--{}.u64;", ctx.ctr());
  emitBranchWithBoundsCheck(ctx, ctx.insn.operands[0], fmt::format("{}.u32 == 0", ctx.ctr()),
                            "bdz");
  return true;
}

bool BuildBdzlr(BuilderContext& ctx) {
  ctx.println("\t--{}.u64;", ctx.ctr());
  ctx.println("\tif ({}.u32 == 0) return;", ctx.ctr());
  return true;
}

bool BuildBdnzlr(BuilderContext& ctx) {
  ctx.println("\t--{}.u64;", ctx.ctr());
  ctx.println("\tif ({}.u32 != 0) return;", ctx.ctr());
  return true;
}

bool BuildBdnz(BuilderContext& ctx) {
  ctx.println("\t--{}.u64;", ctx.ctr());
  emitBranchWithBoundsCheck(ctx, ctx.insn.operands[0], fmt::format("{}.u32 != 0", ctx.ctr()),
                            "bdnz");
  return true;
}

bool BuildBdnzf(BuilderContext& ctx) {
  auto bit = crBitName(ctx.insn.operands[0]);
  ctx.println("\t--{}.u64;", ctx.ctr());
  emitBranchWithBoundsCheck(
      ctx, ctx.insn.operands[1],
      fmt::format("{}.u32 != 0 && !{}.{}", ctx.ctr(), ctx.cr(ctx.insn.operands[0] / 4), bit),
      "bdnzf");
  return true;
}

bool BuildBdnzt(BuilderContext& ctx) {
  auto bit = crBitName(ctx.insn.operands[0]);
  ctx.println("\t--{}.u64;", ctx.ctr());
  emitBranchWithBoundsCheck(
      ctx, ctx.insn.operands[1],
      fmt::format("{}.u32 != 0 && {}.{}", ctx.ctr(), ctx.cr(ctx.insn.operands[0] / 4), bit),
      "bdnzt");
  return true;
}

bool BuildBdzf(BuilderContext& ctx) {
  auto bit = crBitName(ctx.insn.operands[0]);
  ctx.println("\t--{}.u64;", ctx.ctr());
  emitBranchWithBoundsCheck(
      ctx, ctx.insn.operands[1],
      fmt::format("{}.u32 == 0 && !{}.{}", ctx.ctr(), ctx.cr(ctx.insn.operands[0] / 4), bit),
      "bdzf");
  return true;
}

bool BuildBeq(BuilderContext& ctx) {
  ctx.emit_conditional_branch(false, "eq");
  return true;
}

bool BuildBeqlr(BuilderContext& ctx) {
  ctx.println("\tif ({}.eq) return;", ctx.cr(ctx.insn.operands[0]));
  return true;
}

bool BuildBne(BuilderContext& ctx) {
  ctx.emit_conditional_branch(true, "eq");
  return true;
}

bool BuildBnelr(BuilderContext& ctx) {
  ctx.println("\tif (!{}.eq) return;", ctx.cr(ctx.insn.operands[0]));
  return true;
}

bool BuildBlt(BuilderContext& ctx) {
  ctx.emit_conditional_branch(false, "lt");
  return true;
}

bool BuildBltlr(BuilderContext& ctx) {
  ctx.println("\tif ({}.lt) return;", ctx.cr(ctx.insn.operands[0]));
  return true;
}

bool BuildBge(BuilderContext& ctx) {
  ctx.emit_conditional_branch(true, "lt");
  return true;
}

bool BuildBgelr(BuilderContext& ctx) {
  ctx.println("\tif (!{}.lt) return;", ctx.cr(ctx.insn.operands[0]));
  return true;
}

bool BuildBgt(BuilderContext& ctx) {
  ctx.emit_conditional_branch(false, "gt");
  return true;
}

bool BuildBgtlr(BuilderContext& ctx) {
  ctx.println("\tif ({}.gt) return;", ctx.cr(ctx.insn.operands[0]));
  return true;
}

bool BuildBle(BuilderContext& ctx) {
  ctx.emit_conditional_branch(true, "gt");
  return true;
}

bool BuildBlelr(BuilderContext& ctx) {
  ctx.println("\tif (!{}.gt) return;", ctx.cr(ctx.insn.operands[0]));
  return true;
}

bool BuildBso(BuilderContext& ctx) {
  ctx.emit_conditional_branch(false, "so");
  return true;
}

bool BuildBsolr(BuilderContext& ctx) {
  ctx.println("\tif ({}.so) return;", ctx.cr(ctx.insn.operands[0]));
  return true;
}

bool BuildBns(BuilderContext& ctx) {
  ctx.emit_conditional_branch(true, "so");
  return true;
}

bool BuildBnslr(BuilderContext& ctx) {
  ctx.println("\tif (!{}.so) return;", ctx.cr(ctx.insn.operands[0]));
  return true;
}

}
