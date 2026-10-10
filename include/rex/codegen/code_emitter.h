/**
 * @file        rex/codegen/code_emitter.h
 * @brief       Abstract code emission interface
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <string>
#include <string_view>

#include <fmt/core.h>

namespace rex::codegen {

struct RecompilerConfig;

enum class CsrState { Unknown, Fpu, Vmx };

class CodeEmitter {
 public:
  virtual ~CodeEmitter() = default;

  virtual void indent() = 0;

  virtual void dedent() = 0;

  virtual std::string_view indentString() const = 0;

  virtual void raw(std::string_view text) = 0;

  template <typename... Args>
  void line(fmt::format_string<Args...> fmt, Args&&... args) {
    raw(indentString());
    raw(fmt::format(fmt, std::forward<Args>(args)...));
    raw("\n");
  }

  void blankLine() { raw("\n"); }

  void comment(std::string_view text) {
    raw(indentString());
    raw("// ");
    raw(text);
    raw("\n");
  }

  CsrState csrState() const { return csrState_; }

  void setCsrState(CsrState state) { csrState_ = state; }

  virtual void ensureCsrState(CsrState required);

  void resetCsrState() { csrState_ = CsrState::Unknown; }

 protected:
  CsrState csrState_ = CsrState::Unknown;
};

class StringEmitter : public CodeEmitter {
 public:
  explicit StringEmitter(int indentWidth = 4) : indentWidth_(indentWidth) {}

  void indent() override {
    indentLevel_++;
    updateIndentString();
  }

  void dedent() override {
    if (indentLevel_ > 0)
      indentLevel_--;
    updateIndentString();
  }

  std::string_view indentString() const override { return indentStr_; }

  void raw(std::string_view text) override { buffer_.append(text); }

  const std::string& str() const { return buffer_; }

  void clear() { buffer_.clear(); }

  std::string take() { return std::move(buffer_); }

 private:
  void updateIndentString() { indentStr_ = std::string(indentLevel_ * indentWidth_, ' '); }

  std::string buffer_;
  std::string indentStr_;
  int indentLevel_ = 0;
  int indentWidth_ = 4;
};

}
