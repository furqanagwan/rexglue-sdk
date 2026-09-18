#pragma once

#include <cstdint>

namespace rex::kernel::guest_presence {

// Publishes an XGI presence-context write. Only user 0's gameplay context
// (0x8001) is retained; unrelated presence values are ignored.
void NotifyContext(uint32_t user_index, uint32_t context_id, uint32_t value);

// Returns the most recent gameplay context value, or zero before one is set.
uint32_t GameplayContextValue();

}  // namespace rex::kernel::guest_presence
