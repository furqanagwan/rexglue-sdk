#include <rex/kernel/guest_presence.h>

#include <atomic>

namespace rex::kernel::guest_presence {
namespace {

constexpr uint32_t kGameplayContextId = 0x8001;
std::atomic<uint32_t> g_gameplay_context_value{0};

}  // namespace

void NotifyContext(uint32_t user_index, uint32_t context_id, uint32_t value) {
  if (user_index == 0 && context_id == kGameplayContextId) {
    g_gameplay_context_value.store(value, std::memory_order_release);
  }
}

uint32_t GameplayContextValue() {
  return g_gameplay_context_value.load(std::memory_order_acquire);
}

}  // namespace rex::kernel::guest_presence
