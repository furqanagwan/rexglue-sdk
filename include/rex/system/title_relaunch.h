/**
 * @file        system/title_relaunch.h
 * @brief       Relaunching a title that launches its own executable
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

namespace rex::system {

// Some titles restart themselves with XamLoaderLaunchTitle("default.xex") and
// pass state to the next run through XamLoaderSetLaunchData (Top Spin 4 does it
// to go from its front end into the game). A recompiled title can't reload its
// executable in-process, so the host process restarts instead:
//
//  1. XamLoaderLaunchTitle calls RequestTitleRelaunch with the launch data.
//  2. When the guest main thread has ended, the app calls RelaunchProcess, which
//     writes the data to a file and starts this executable again with the same
//     arguments plus --launch_data_file=<file>.
//  3. The new process reads the file back with TakeLaunchDataFile (and deletes
//     it), so XamLoaderGetLaunchData returns what the previous run set.

void RequestTitleRelaunch(std::vector<uint8_t> launch_data, uint32_t launch_flags);
bool IsTitleRelaunchRequested();

// Starts the new process. data_dir holds the launch data file. Returns false,
// having logged why, if the process could not be started.
bool RelaunchProcess(const std::filesystem::path& data_dir);

// The launch data passed by the previous run, if any; the file is deleted.
bool TakeLaunchDataFile(std::vector<uint8_t>& launch_data, uint32_t& launch_flags);

}  // namespace rex::system
