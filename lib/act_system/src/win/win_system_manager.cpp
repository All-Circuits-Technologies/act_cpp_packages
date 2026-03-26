// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#include "act_system/win/win_system_manager.hpp"

namespace act::system
{

FILE *WinSystemManager::openPipe(const std::string &cmd)
{
    return _popen(cmd.c_str(), "r");
}

int WinSystemManager::closePipe(FILE *pipe)
{
    return _pclose(pipe);
}

void WinSystemManager::syncBeforeReboot()
{
    // No-op: Windows flushes filesystems during the shutdown/reboot sequence
}

} // namespace act::system
