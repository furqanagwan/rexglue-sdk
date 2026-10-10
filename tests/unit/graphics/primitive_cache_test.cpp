// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.

#include <array>
#include <cstdint>
#include <deque>
#include <functional>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include <rex/graphics/primitive_processor.h>
#include <rex/thread/mutex.h>

#include "test_memory.h"

namespace {
using namespace rex::graphics;

class CpuSharedMemory final : public SharedMemory {
 public:
  explicit CpuSharedMemory(rex::memory::Memory& memory) : SharedMemory(memory) {
    InitializeCommon();
  }
  void Shutdown() { ShutdownCommon(); }

 private:
  bool UploadRanges(const std::vector<std::pair<uint32_t, uint32_t>>&) override { return false; }
};

class CpuPrimitiveProcessor final : public PrimitiveProcessor {
 public:
  CpuPrimitiveProcessor(const RegisterFile& registers, rex::memory::Memory& memory,
                        SharedMemory& shared)
      : PrimitiveProcessor(registers, memory, shared) {}
  bool Initialize() { return InitializeCommon(true, false, true, true, true, true); }
  void Shutdown() { ShutdownCommon(); }
  std::function<void()> on_allocate_;
  size_t AllocationCount() const { return converted_.size(); }
  uint32_t Index(const ProcessingResult& result, size_t index) const {
    const auto& buffer = converted_.at(result.host_index_buffer_handle);
    if (result.host_index_format == xenos::IndexFormat::kInt16) {
      return reinterpret_cast<const uint16_t*>(buffer.data())[index];
    }
    return buffer.at(index);
  }

 private:
  bool InitializeBuiltinIndexBuffer(size_t size, std::function<void(void*)> fill) override {
    builtin_.resize((size + 3) / 4);
    fill(builtin_.data());
    return true;
  }
  void* RequestHostConvertedIndexBufferForCurrentFrame(xenos::IndexFormat format, uint32_t count,
                                                       bool, uint32_t, size_t& handle) override {
    if (on_allocate_) {
      auto callback = std::move(on_allocate_);
      on_allocate_ = {};
      callback();
    }
    handle = converted_.size();
    const size_t size = size_t(count) * (format == xenos::IndexFormat::kInt16 ? 2 : 4);
    converted_.emplace_back((size + XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE + 3) / 4);
    return converted_.back().data();
  }
  std::vector<uint32_t> builtin_;
  std::deque<std::vector<uint32_t>> converted_;
};

struct Fixture {
  static constexpr uint32_t kVirtualBase = 0xA1000000;
  static constexpr uint32_t kAllocationSize = 0x100000;
  struct PhysicalAllocation {
    explicit PhysicalAllocation(rex::memory::Memory& memory)
        : heap_(const_cast<rex::memory::BaseHeap*>(memory.LookupHeap(kVirtualBase))) {
      REQUIRE(heap_);
      REQUIRE(heap_->AllocFixed(
          kVirtualBase, kAllocationSize, 0x1000,
          rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
          rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite));
    }
    ~PhysicalAllocation() { heap_->Release(kVirtualBase, nullptr); }
    PhysicalAllocation(const PhysicalAllocation&) = delete;
    PhysicalAllocation& operator=(const PhysicalAllocation&) = delete;
    rex::memory::BaseHeap* heap_;
  };
  rex::memory::Memory& memory_ = rex::testing::GetTestMemory();

  PhysicalAllocation allocation_{memory_};
  RegisterFile registers_;
  CpuSharedMemory shared_{memory_};
  CpuPrimitiveProcessor processor_{registers_, memory_, shared_};
  uint32_t base_;
  uint32_t size_;
  xenos::IndexFormat format_;

  explicit Fixture(xenos::IndexFormat index_format, uint32_t offset = 0x1000)
      : base_(memory_.GetPhysicalAddress(kVirtualBase) + offset),
        size_(index_format == xenos::IndexFormat::kInt16 ? 8 : 16),
        format_(index_format) {
    Write(0, 10);
    Write(1, 11);
    Write(2, 12);
    Write(3, 13);
    reg::VGT_DRAW_INITIATOR draw{};
    draw.prim_type = xenos::PrimitiveType::kTriangleFan;
    draw.source_select = xenos::SourceSelect::kDMA;
    draw.index_size = format_;
    draw.num_indices = 4;
    registers_[XE_GPU_REG_VGT_DRAW_INITIATOR] = draw.value;
    reg::VGT_DMA_SIZE dma{};
    dma.num_words = 4;
    dma.swap_mode = xenos::Endian::kNone;
    registers_[XE_GPU_REG_VGT_DMA_SIZE] = dma.value;
    registers_[XE_GPU_REG_VGT_DMA_BASE] = base_;
    REQUIRE(processor_.Initialize());
  }

  void Write(size_t index, uint32_t value) const {
    if (format_ == xenos::IndexFormat::kInt16) {
      memory_.TranslatePhysical<uint16_t*>(base_)[index] = uint16_t(value);
    } else {
      memory_.TranslatePhysical<uint32_t*>(base_)[index] = value;
    }
  }
  PrimitiveProcessor::ProcessingResult Convert() {
    PrimitiveProcessor::ProcessingResult result{};
    REQUIRE(processor_.Process(result));
    REQUIRE(result.index_buffer_type == PrimitiveProcessor::kHostConverted);
    REQUIRE(result.host_draw_vertex_count == 6);
    return result;
  }
};

constexpr std::array kFormats{xenos::IndexFormat::kInt16, xenos::IndexFormat::kInt32};
}

TEST_CASE("Primitive conversions invalidate for every exact overlapping range", "[primitive]") {
  const auto format = GENERATE(from_range(kFormats));
  const uint32_t offset = GENERATE(0x1000u, 0x3FFFCu);
  Fixture fixture(format, offset);
  const auto first = fixture.Convert();
  CHECK(fixture.Convert().host_index_buffer_handle == first.host_index_buffer_handle);
  uint32_t start = fixture.base_;
  uint32_t length = fixture.size_;
  SECTION("equal") {}
  SECTION("covering") {
    start -= 4;
    length += 8;
  }
  SECTION("contained") {
    start += 2;
    length = 2;
  }
  SECTION("left partial") {
    start -= 4;
    length = 6;
  }
  SECTION("right partial") {
    start += fixture.size_ - 2;
    length = 6;
  }
  fixture.processor_.MemoryInvalidationCallback(start, length, true);
  CHECK(fixture.Convert().host_index_buffer_handle != first.host_index_buffer_handle);
  CHECK(fixture.processor_.AllocationCount() == 2);
}

TEST_CASE("Primitive conversions keep exact adjacent and empty ranges", "[primitive]") {
  Fixture fixture(GENERATE(from_range(kFormats)));
  const auto first = fixture.Convert();
  fixture.processor_.MemoryInvalidationCallback(fixture.base_ - 4, 4, true);
  fixture.processor_.MemoryInvalidationCallback(fixture.base_ + fixture.size_, 4, true);
  fixture.processor_.MemoryInvalidationCallback(fixture.base_, 0, true);
  CHECK(fixture.Convert().host_index_buffer_handle == first.host_index_buffer_handle);
  CHECK(fixture.processor_.AllocationCount() == 1);
}

TEST_CASE("Primitive invalidation preserves other entries in the same bucket", "[primitive]") {
  Fixture fixture(GENERATE(from_range(kFormats)));
  const uint32_t first_base = fixture.base_;
  const auto first = fixture.Convert();
  fixture.base_ += 0x80;
  for (size_t index = 0; index < 4; ++index) {
    fixture.Write(index, uint32_t(20 + index));
  }
  fixture.registers_[XE_GPU_REG_VGT_DMA_BASE] = fixture.base_;
  const auto second = fixture.Convert();
  fixture.processor_.MemoryInvalidationCallback(first_base, fixture.size_ + 4, true);
  CHECK(fixture.Convert().host_index_buffer_handle == second.host_index_buffer_handle);
  fixture.registers_[XE_GPU_REG_VGT_DMA_BASE] = first_base;
  CHECK(fixture.Convert().host_index_buffer_handle != first.host_index_buffer_handle);
  fixture.registers_[XE_GPU_REG_VGT_DMA_BASE] = fixture.base_;
  CHECK(fixture.Convert().host_index_buffer_handle == second.host_index_buffer_handle);
  CHECK(fixture.processor_.AllocationCount() == 3);
}

TEST_CASE("Primitive conversions invalidate whole buckets for coarse writes", "[primitive]") {
  Fixture fixture(GENERATE(from_range(kFormats)));
  const auto first = fixture.Convert();
  fixture.processor_.MemoryInvalidationCallback(fixture.base_ + fixture.size_, 4, false);
  CHECK(fixture.Convert().host_index_buffer_handle != first.host_index_buffer_handle);
}

TEST_CASE("Primitive conversion changed while processing is not cached", "[primitive]") {
  Fixture fixture(GENERATE(from_range(kFormats)));
  fixture.processor_.on_allocate_ = [&] {
    fixture.processor_.MemoryInvalidationCallback(fixture.base_, fixture.size_, true);
  };
  const auto first = fixture.Convert();
  const auto second = fixture.Convert();
  CHECK(second.host_index_buffer_handle != first.host_index_buffer_handle);
  CHECK(fixture.Convert().host_index_buffer_handle == second.host_index_buffer_handle);
  CHECK(fixture.processor_.AllocationCount() == 2);
}

TEST_CASE("Primitive conversion ignores unrelated writes while processing", "[primitive]") {
  Fixture fixture(GENERATE(from_range(kFormats)));
  fixture.processor_.on_allocate_ = [&] {
    fixture.processor_.MemoryInvalidationCallback(fixture.base_ + fixture.size_, 4, true);
  };
  const auto first = fixture.Convert();
  CHECK(fixture.Convert().host_index_buffer_handle == first.host_index_buffer_handle);
}

TEST_CASE("Guest index writes refresh converted primitive contents", "[primitive]") {
  Fixture fixture(GENERATE(from_range(kFormats)));
  const auto first = fixture.Convert();
  CHECK(fixture.processor_.Index(first, 0) == 11);

  REQUIRE(fixture.memory_.TriggerPhysicalMemoryCallbacks(
      rex::thread::global_critical_region::AcquireDirect(),
      Fixture::kVirtualBase + (fixture.base_ & 0xFFFFF), fixture.size_, true, true));
  fixture.Write(1, 99);
  const auto second = fixture.Convert();
  CHECK(second.host_index_buffer_handle != first.host_index_buffer_handle);
  CHECK(fixture.processor_.Index(second, 0) == 99);
}
