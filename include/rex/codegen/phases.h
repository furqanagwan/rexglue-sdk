/**
 * @file        rexcodegen/phases.h
 * @brief       Analysis phase entry points
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <string>

#include <rex/codegen/codegen_context.h>
#include <rex/codegen/progress_reporter.h>
#include <rex/result.h>

namespace rex::codegen::phases {

VoidResult Register(CodegenContext& ctx, ProgressReporter* reporter = nullptr);

VoidResult Scan(CodegenContext& ctx, ProgressReporter* reporter = nullptr);

VoidResult Discover(CodegenContext& ctx, ProgressReporter* reporter = nullptr);

VoidResult Merge(CodegenContext& ctx, ProgressReporter* reporter = nullptr);

VoidResult GapFill(CodegenContext& ctx, ProgressReporter* reporter = nullptr);

VoidResult Validate(CodegenContext& ctx, ProgressReporter* reporter = nullptr);

}
