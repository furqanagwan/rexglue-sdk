// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <rex/filesystem/devices/optical_disc_reader.h>
#include <mutex>
#include <windows.h>
#include <winioctl.h>
#include <ntddcdrm.h>

namespace rex::filesystem {
namespace {
class NativeDiscReader : public FileHandle {
 public:
  NativeDiscReader(const std::filesystem::path& path, HANDLE handle)
      : FileHandle(path), handle_(handle) {}
  ~NativeDiscReader() override { CloseHandle(handle_); }
  bool Read(size_t offset, void* buffer, size_t size, size_t* read) override {
    *read = 0;
    if (size > MAXDWORD)
      return false;
    OVERLAPPED operation{};
    operation.Offset = DWORD(offset);
    operation.OffsetHigh = DWORD(uint64_t(offset) >> 32);
    DWORD count = 0;
    if (!ReadFile(handle_, buffer, DWORD(size), &count, &operation))
      return false;
    *read = count;
    return true;
  }
  bool Write(size_t, const void*, size_t, size_t*) override { return false; }
  bool SetLength(size_t) override { return false; }
  bool Flush() override { return true; }

 private:
  HANDLE handle_;
};
class AlignedDiscReader : public FileHandle {
 public:
  AlignedDiscReader(std::unique_ptr<FileHandle> reader, size_t sector, size_t size)
      : FileHandle(reader->path()), reader_(std::move(reader)), sector_(sector), size_(size) {}
  ~AlignedDiscReader() override {
    if (buffer_)
      VirtualFree(buffer_, 0, MEM_RELEASE);
  }
  bool Read(size_t offset, void* target, size_t count, size_t* read) override {
    *read = 0;
    if (offset > size_ || count > size_ - offset || count > 16 * 1024 * 1024)
      return false;
    if (!count)
      return true;
    const size_t start = offset - offset % sector_;
    const size_t skip = offset - start;
    const size_t aligned = ((skip + count + sector_ - 1) / sector_) * sector_;
    if (aligned > size_ - start)
      return false;
    std::lock_guard lock(mutex_);
    if (aligned > capacity_) {
      if (buffer_)
        VirtualFree(buffer_, 0, MEM_RELEASE);
      buffer_ = VirtualAlloc(nullptr, aligned, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
      capacity_ = buffer_ ? aligned : 0;
    }
    if (!buffer_)
      return false;
    size_t got = 0;
    if (!reader_->Read(start, buffer_, aligned, &got) || got != aligned)
      return false;
    std::memcpy(target, static_cast<uint8_t*>(buffer_) + skip, count);
    *read = count;
    return true;
  }
  bool Write(size_t, const void*, size_t, size_t*) override { return false; }
  bool SetLength(size_t) override { return false; }
  bool Flush() override { return true; }

 private:
  std::unique_ptr<FileHandle> reader_;
  size_t sector_, size_, capacity_ = 0;
  void* buffer_ = nullptr;
  std::mutex mutex_;
};
}  // namespace
bool IsOpticalDiscPath(const std::filesystem::path& path) {
  const auto& text = path.native();
  return text.size() == 6 && text.starts_with(L"\\\\.\\") && text[5] == L':' &&
         ((text[4] >= L'A' && text[4] <= L'Z') || (text[4] >= L'a' && text[4] <= L'z'));
}
std::unique_ptr<FileHandle> MakeSectorAlignedDiscReader(std::unique_ptr<FileHandle> reader,
                                                        size_t sector, size_t size) {
  if (!reader || sector < 512 || sector > 65536 || (sector & (sector - 1)) || size % sector)
    return nullptr;
  return std::make_unique<AlignedDiscReader>(std::move(reader), sector, size);
}
std::unique_ptr<FileHandle> OpenOpticalDisc(const std::filesystem::path& path, size_t* size) {
  *size = 0;
  if (!IsOpticalDiscPath(path))
    return nullptr;
  const std::wstring root{path.native()[4], L':', L'\\'};
  if (GetDriveTypeW(root.c_str()) != DRIVE_CDROM)
    return nullptr;
  const HANDLE handle = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                    nullptr, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, nullptr);
  if (handle == INVALID_HANDLE_VALUE)
    return nullptr;
  auto reader = std::make_unique<NativeDiscReader>(path, handle);
  DISK_GEOMETRY_EX geometry{};
  DWORD returned = 0;
  if (!DeviceIoControl(handle, IOCTL_CDROM_GET_DRIVE_GEOMETRY_EX, nullptr, 0, &geometry,
                       sizeof(geometry), &returned, nullptr) ||
      returned < offsetof(DISK_GEOMETRY_EX, Data) || geometry.DiskSize.QuadPart <= 0)
    return nullptr;
  const size_t bytes = size_t(geometry.DiskSize.QuadPart);
  auto aligned =
      MakeSectorAlignedDiscReader(std::move(reader), geometry.Geometry.BytesPerSector, bytes);
  if (aligned)
    *size = bytes;
  return aligned;
}
}  // namespace rex::filesystem
