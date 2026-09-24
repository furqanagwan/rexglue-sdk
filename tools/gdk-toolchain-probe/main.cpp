#include <Windows.h>
#include <XGameRuntime.h>

#include <cstdio>

int main() {
  const HRESULT result = XGameRuntimeInitialize();
  std::printf("XGameRuntimeInitialize: 0x%08lX\n",
              static_cast<unsigned long>(result));
  if (SUCCEEDED(result)) {
    XGameRuntimeUninitialize();
  }
  return SUCCEEDED(result) ? 0 : 1;
}
