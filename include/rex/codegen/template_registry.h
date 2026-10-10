/**
 * @file        rex/codegen/template_registry.h
 * @brief       Template registry for inja-based code generation
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 * @license     BSD 3-Clause License
 */

#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <stdexcept>

namespace rex::codegen {

class TemplateError : public std::runtime_error {
 public:
  TemplateError(const std::string& templateId, const std::string& message,
                const std::string& source = "embedded");

  const std::string& templateId() const { return templateId_; }
  const std::string& source() const { return source_; }

 private:
  std::string templateId_;
  std::string source_;
};

class TemplateRegistry {
 public:
  TemplateRegistry();
  ~TemplateRegistry();

  TemplateRegistry(const TemplateRegistry&) = delete;
  TemplateRegistry& operator=(const TemplateRegistry&) = delete;
  TemplateRegistry(TemplateRegistry&&) noexcept;
  TemplateRegistry& operator=(TemplateRegistry&&) noexcept;

  void loadOverrides(const std::filesystem::path& dir);

  std::string render(const std::string& id, const std::string& jsonData);

  std::string renderString(const std::string& templateContent, const std::string& jsonData);

  std::vector<std::string> registeredIds() const;

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

std::string EmbeddedTemplatesHash();

}
