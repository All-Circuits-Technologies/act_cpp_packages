// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#ifdef _WIN32
#include "act_system/win/win_system_manager.hpp"
#else
#include "act_system/linux/linux_system_manager.hpp"
#endif

namespace act::system
{

#ifdef _WIN32
/// @brief Platform alias for the system manager (Windows implementation).
using SystemManager = WinSystemManager;
#else
/// @brief Platform alias for the system manager (Linux/POSIX implementation).
using SystemManager = LinuxSystemManager;
#endif

} // namespace act::system
