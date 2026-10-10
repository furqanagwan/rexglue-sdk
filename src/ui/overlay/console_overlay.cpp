/**
 * @file        ui/overlay/console_overlay.cpp
 *
 * @brief       Console overlay implementation. See console_overlay.h for details.
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#include <rex/ui/overlay/console_overlay.h>
#include <rex/cvar.h>
#include <imgui.h>
#include <algorithm>
#include <iterator>
#include <string>

namespace rex::ui {

static ImVec4 LevelColor(spdlog::level::level_enum level, const ConsoleStyle& style) {
  const auto index = static_cast<size_t>(level);
  return index < std::size(style.level) ? style.level[index] : style.level[spdlog::level::info];
}

ConsoleDialog::ConsoleDialog(ImGuiDrawer* imgui_drawer, std::shared_ptr<rex::LogCaptureSink> sink)
    : ImGuiDialog(imgui_drawer), sink_(std::move(sink)) {}

ConsoleDialog::~ConsoleDialog() {}

void ConsoleDialog::RefreshCategories() {
  for (auto& entry : entries_) {
    if (entry.category.empty() || entry.category == "console")
      continue;
    if (known_categories_.insert(entry.category).second) {
      category_filter_[entry.category] = true;
    }
  }
}

int ConsoleDialog::InputTextCallback(ImGuiInputTextCallbackData* data) {
  auto* self = static_cast<ConsoleDialog*>(data->UserData);
  switch (data->EventFlag) {
    case ImGuiInputTextFlags_CallbackAlways:
      self->UpdateCompletionCandidates(data->Buf, data->BufTextLen);
      break;
    case ImGuiInputTextFlags_CallbackCompletion:
      self->ApplyCompletion(data);
      break;
    case ImGuiInputTextFlags_CallbackHistory:
      self->HandleHistoryOrCompletionNav(data);
      break;
    default:
      break;
  }
  return 0;
}

void ConsoleDialog::UpdateCompletionCandidates(const char* buf, int len) {
  std::string_view text(buf, static_cast<size_t>(len));

  if (text.empty() || text.find(' ') != std::string_view::npos) {
    completion_candidates_.clear();
    completion_open_ = false;
    completion_index_ = -1;
    return;
  }
  std::vector<std::string> matches;
  for (auto& name : rex::cvar::ListFlags()) {
    if (name.size() >= text.size() && std::string_view(name).substr(0, text.size()) == text) {
      matches.push_back(name);
    }
  }
  if (matches != completion_candidates_) {
    completion_candidates_ = std::move(matches);
    completion_index_ = -1;
  }
  completion_open_ = !completion_candidates_.empty();
}

void ConsoleDialog::ApplyCompletion(ImGuiInputTextCallbackData* data) {
  if (completion_candidates_.empty())
    return;
  std::string completion;
  bool full = false;
  if (completion_index_ >= 0 &&
      completion_index_ < static_cast<int>(completion_candidates_.size())) {
    completion = completion_candidates_[completion_index_];
    full = true;
  } else if (completion_candidates_.size() == 1) {
    completion = completion_candidates_[0];
    full = true;
  } else {
    completion = completion_candidates_[0];
    for (size_t i = 1; i < completion_candidates_.size(); ++i) {
      const std::string& cand = completion_candidates_[i];
      size_t j = 0;
      while (j < completion.size() && j < cand.size() && completion[j] == cand[j])
        ++j;
      completion.resize(j);
    }
  }
  data->DeleteChars(0, data->BufTextLen);
  data->InsertChars(0, completion.c_str());
  if (full) {
    data->InsertChars(data->CursorPos, " ");
    completion_candidates_.clear();
    completion_open_ = false;
    completion_index_ = -1;
  }
}

void ConsoleDialog::HandleHistoryOrCompletionNav(ImGuiInputTextCallbackData* data) {
  if (completion_open_ && !completion_candidates_.empty()) {
    const int count = static_cast<int>(completion_candidates_.size());
    if (data->EventKey == ImGuiKey_UpArrow) {
      completion_index_ = (completion_index_ <= 0) ? count - 1 : completion_index_ - 1;
    } else if (data->EventKey == ImGuiKey_DownArrow) {
      completion_index_ = (completion_index_ + 1) % count;
    }
    return;
  }

  const int prev = history_pos_;
  if (data->EventKey == ImGuiKey_UpArrow) {
    if (history_pos_ == -1) {
      history_pos_ = static_cast<int>(history_.size()) - 1;
    } else if (history_pos_ > 0) {
      --history_pos_;
    }
  } else if (data->EventKey == ImGuiKey_DownArrow) {
    if (history_pos_ != -1) {
      if (++history_pos_ >= static_cast<int>(history_.size())) {
        history_pos_ = -1;
      }
    }
  }
  if (prev != history_pos_) {
    const char* hist = (history_pos_ >= 0) ? history_[history_pos_].c_str() : "";
    data->DeleteChars(0, data->BufTextLen);
    data->InsertChars(0, hist);
  }
}

void ConsoleDialog::AddLocal(spdlog::level::level_enum level, std::string text) {
  const uint64_t seq = sink_ ? sink_->generation() : 0;
  local_entries_.push_back({rex::LogEntry{level, "console", std::move(text)}, seq});
}

void ConsoleDialog::ExecuteCommand(std::string_view cmd) {
  while (!cmd.empty() && cmd.front() == ' ')
    cmd.remove_prefix(1);
  while (!cmd.empty() && cmd.back() == ' ')
    cmd.remove_suffix(1);
  if (cmd.empty())
    return;

  if (history_.empty() || history_.back() != cmd) {
    if (history_.size() >= kMaxHistory)
      history_.pop_front();
    history_.push_back(std::string(cmd));
  }
  history_pos_ = -1;

  if (cmd == "help" || cmd == "?") {
    auto names = rex::cvar::ListFlags();
    std::sort(names.begin(), names.end());
    for (auto& n : names) {
      const auto* info = rex::cvar::GetFlagInfo(n);
      std::string line = "  " + n;
      if (info)
        line += " = " + info->getter() + "  (" + info->description + ")";
      AddLocal(spdlog::level::info, line);
    }
    return;
  }

  auto sep = cmd.find(' ');
  std::string name(sep == std::string_view::npos ? cmd : cmd.substr(0, sep));
  std::string args;
  if (sep != std::string_view::npos) {
    std::string_view rest = cmd.substr(sep + 1);
    while (!rest.empty() && rest.front() == ' ')
      rest.remove_prefix(1);
    args = std::string(rest);
  }

  const auto* info = rex::cvar::GetFlagInfo(name);

  if (info && info->type == rex::cvar::FlagType::Command) {
    AddLocal(spdlog::level::info, "[console] > " + name + (args.empty() ? "" : " " + args));
    rex::cvar::InvokeCommand(name, args);
    scroll_to_bottom_ = true;
    return;
  }

  if (sep == std::string_view::npos) {
    std::string val = rex::cvar::GetFlagByName(name);
    if (val.empty() && !info) {
      AddLocal(spdlog::level::warn, "[console] unknown cvar: " + name);
    } else {
      AddLocal(spdlog::level::info, "[console] " + name + " = " + val);
    }
    return;
  }

  if (rex::cvar::SetFlagByName(name, args)) {
    AddLocal(spdlog::level::info, "[console] " + name + " = " + args);
  } else {
    AddLocal(spdlog::level::warn, "[console] unknown cvar: " + name);
  }
  scroll_to_bottom_ = true;
}

void ConsoleDialog::OnDraw(ImGuiIO& io) {
  const ConsoleStyle& style = imgui_drawer()->style().console;

  if (sink_) {
    uint64_t gen = sink_->generation();
    if (gen != last_generation_) {
      sink_->CopyEntries(entries_);
      last_generation_ = gen;
      RefreshCategories();
    }
  }

  if (console_height_ <= 0.0f)
    console_height_ = io.DisplaySize.y * 0.45f;
  const float min_height = ImGui::GetFrameHeightWithSpacing() * 3.0f;
  console_height_ = std::clamp(console_height_, min_height, io.DisplaySize.y);

  ImGui::SetNextWindowPos(ImVec2(0, io.DisplaySize.y - console_height_), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, console_height_), ImGuiCond_Always);
  ImGui::SetNextWindowBgAlpha(0.80f);

  ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
                           ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;

  if (!ImGui::Begin("Console##rex", nullptr, flags)) {
    ImGui::End();
    return;
  }

  ImGui::InvisibleButton("##resize_handle", ImVec2(-1.0f, 4.0f));
  if (ImGui::IsItemHovered() || ImGui::IsItemActive())
    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
  if (ImGui::IsItemActive())
    console_height_ = std::clamp(console_height_ - io.MouseDelta.y, min_height, io.DisplaySize.y);

  static const char* kLevelNames[] = {"trace", "debug", "info", "warn", "error", "critical"};
  ImGui::Text("Level:");
  ImGui::SameLine();
  ImGui::SetNextItemWidth(80.0f);
  ImGui::Combo("##lvl", &min_level_, kLevelNames, 6);
  ImGui::SameLine();
  ImGui::Text("Categories:");
  ImGui::SameLine();
  int cat_idx = 0;
  for (auto& [cat_name, enabled] : category_filter_) {
    ImGui::Checkbox(cat_name.c_str(), &enabled);
    if (++cat_idx < static_cast<int>(category_filter_.size()))
      ImGui::SameLine();
  }

  const float input_height = ImGui::GetFrameHeightWithSpacing() + 4.0f;
  ImGui::BeginChild("##log", ImVec2(0, -input_height), false, ImGuiWindowFlags_HorizontalScrollbar);

  bool at_bottom = (ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 2.0f);

  auto draw_entry = [&](const rex::LogEntry& entry) {
    if (static_cast<int>(entry.level) < min_level_)
      return;

    bool show_cat = (entry.category == "console");
    if (!show_cat) {
      auto it = category_filter_.find(entry.category);
      if (it != category_filter_.end())
        show_cat = it->second;
    }
    if (!show_cat)
      return;

    ImGui::PushStyleColor(ImGuiCol_Text, LevelColor(entry.level, style));
    ImGui::TextUnformatted(entry.text.c_str());
    ImGui::PopStyleColor();
  };

  const uint64_t base_gen =
      last_generation_ >= entries_.size() ? last_generation_ - entries_.size() + 1 : 1;
  size_t li = 0;
  for (size_t i = 0; i < entries_.size(); ++i) {
    const uint64_t gen_i = base_gen + i;
    for (; li < local_entries_.size() && local_entries_[li].seq < gen_i; ++li)
      draw_entry(local_entries_[li].entry);
    draw_entry(entries_[i]);
  }
  for (; li < local_entries_.size(); ++li)
    draw_entry(local_entries_[li].entry);

  if (scroll_to_bottom_ || at_bottom) {
    ImGui::SetScrollHereY(1.0f);
    scroll_to_bottom_ = false;
  }
  ImGui::EndChild();

  ImGui::Separator();
  bool submit = false;
  ImGuiInputTextFlags input_flags =
      ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackHistory |
      ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackAlways;
  ImGui::SetNextItemWidth(-1.0f);
  if (focus_input_next_frame_) {
    ImGui::SetKeyboardFocusHere();
    focus_input_next_frame_ = false;
  }
  if (ImGui::InputText("##cmd", input_buf_, sizeof(input_buf_), input_flags, InputTextCallback,
                       this)) {
    submit = true;
  }
  const ImVec2 input_min = ImGui::GetItemRectMin();
  const ImVec2 input_max = ImGui::GetItemRectMax();

  if (!ImGui::IsItemFocused()) {
    completion_open_ = false;
    completion_candidates_.clear();
    completion_index_ = -1;
  }

  if (submit && input_buf_[0] != '\0') {
    ExecuteCommand(input_buf_);
    input_buf_[0] = '\0';
    completion_candidates_.clear();
    completion_open_ = false;
    completion_index_ = -1;
    ImGui::SetKeyboardFocusHere(-1);
  }

  if (completion_open_ && !completion_candidates_.empty()) {
    const int count = static_cast<int>(completion_candidates_.size());
    const float line_h = ImGui::GetTextLineHeightWithSpacing();
    const float pad_y = ImGui::GetStyle().WindowPadding.y * 2.0f;
    const float height = std::min(count * line_h + pad_y, 200.0f);
    const float width = input_max.x - input_min.x;

    ImGui::SetCursorScreenPos(ImVec2(input_min.x, input_min.y - height));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, style.completion_bg);
    if (ImGui::BeginChild("##rex_completions", ImVec2(width, height), true,
                          ImGuiWindowFlags_NoNavInputs)) {
      ImDrawList* dl = ImGui::GetWindowDrawList();
      for (int i = 0; i < count; ++i) {
        if (i == completion_index_) {
          const ImVec2 p = ImGui::GetCursorScreenPos();
          dl->AddRectFilled(p, ImVec2(p.x + ImGui::GetContentRegionAvail().x, p.y + line_h),
                            ImGui::GetColorU32(style.completion_highlight));
        }
        ImGui::TextUnformatted(completion_candidates_[i].c_str());
        if (i == completion_index_)
          ImGui::SetScrollHereY();
      }
    }
    ImGui::EndChild();
    ImGui::PopStyleColor();
  }

  ImGui::End();
}

}
