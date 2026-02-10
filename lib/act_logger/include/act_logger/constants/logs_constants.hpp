// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/* # App includes (in alphabetical order) */
#include "act_misc/types/logs_level.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */

/* # Forward declaration */

namespace act::logger::LogsConstants
{
    /** @brief Default console logs level */
    constexpr const LogsLevel::Enum DEFAULT_CONSOLE_LOGS_LEVEL = LogsLevel::Enum::INFO;
} // namespace act::logger::LogsConstants
