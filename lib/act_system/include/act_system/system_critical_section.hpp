// SPDX-FileCopyrightText: 2025 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#ifdef _WIN32
#include "act_system/win/win_system_critical_section.hpp"
#else
#include "act_system/linux/linux_system_critical_section.hpp"
#endif

namespace act::system
{

#ifdef _WIN32
/// @brief Platform alias for the system-wide critical section (Windows implementation).
using SystemCriticalSection = WinSystemCriticalSection;
#else
/// @brief Platform alias for the system-wide critical section (Linux/POSIX implementation).
using SystemCriticalSection = LinuxSystemCriticalSection;
#endif

} // namespace act::system
