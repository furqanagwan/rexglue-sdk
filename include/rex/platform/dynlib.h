

#pragma once

#include <cstdint>
#include <filesystem>

#include <rex/platform.h>

namespace rex::platform {

enum class SymbolResolution {

  kLazy,

  kImmediate,
};

class DynamicLibrary {
 public:
  DynamicLibrary() = default;
  ~DynamicLibrary();

  DynamicLibrary(const DynamicLibrary&) = delete;
  DynamicLibrary& operator=(const DynamicLibrary&) = delete;
  DynamicLibrary(DynamicLibrary&& other) noexcept;
  DynamicLibrary& operator=(DynamicLibrary&& other) noexcept;

  bool Load(const std::filesystem::path& path, SymbolResolution mode = SymbolResolution::kLazy);
  void Close();
  explicit operator bool() const { return handle_ != nullptr; }

  void* GetRawSymbol(const char* name) const;

  template <typename T>
  T GetSymbol(const char* name) const {
    return reinterpret_cast<T>(GetRawSymbol(name));
  }

 private:
  void* handle_ = nullptr;
};

namespace lib_names {

inline constexpr const char* kRenderDoc = "renderdoc.dll";

}

}
