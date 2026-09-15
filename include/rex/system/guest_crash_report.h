/**
 * @file        system/guest_crash_report.h
 * @brief       Guest context logged when a fault is not handled
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#pragma once

#include <cstdint>

namespace rex::system {

// Logs what is known about the guest at a fault the memory handler could not
// resolve, so a crash can be traced without a debugger (rexglue-sdk#409). A
// guest __try block may still handle the fault, so this is a report, not a
// verdict; it is limited to a few per run. It gives the faulting host instruction as
// module + offset (resolvable with the module's symbols), the guest thread, and
// its PPC registers. lr is the guest address after the most recent call, which
// usually names the guest function that faulted or its caller. Registers the
// recompiled code keeps in host registers may be stale.
void LogGuestCrashContext(const char* what, uint64_t host_pc);

}  // namespace rex::system
