// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#include "act_system/abs_system_manager.hpp"

namespace act::system
{

/**
 * @brief Windows implementation of the system manager.
 *
 * Provides pipe handling via _popen/_pclose. No filesystem sync is performed
 * before rebooting (Windows handles this at the OS level).
 */
class WinSystemManager : public AbsSystemManager
{
  public:
    using AbsSystemManager::AbsSystemManager;

  protected:
    /**
     * @brief Open a pipe using the Windows _popen() call
     * @param cmd The shell command to execute
     * @return Pointer to the opened pipe, or nullptr on failure
     */
    FILE *openPipe(const std::string &cmd) override;

    /**
     * @brief Close a pipe using the Windows _pclose() call
     * @param pipe The pipe to close
     * @return The exit code of the underlying process
     */
    int closePipe(FILE *pipe) override;

    /**
     * @brief No-op on Windows: the OS handles filesystem synchronisation before reboot
     */
    void syncBeforeReboot() override;
};

} // namespace act::system
