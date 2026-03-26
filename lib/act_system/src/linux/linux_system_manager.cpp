// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#include "act_system/linux/linux_system_manager.hpp"

#include <unistd.h> // sync

namespace act::system
{

FILE *LinuxSystemManager::openPipe(const std::string &cmd)
{
    return popen(cmd.c_str(), "r");
}

int LinuxSystemManager::closePipe(FILE *pipe)
{
    return pclose(pipe);
}

void LinuxSystemManager::syncBeforeReboot()
{
    sync();
}

} // namespace act::system
