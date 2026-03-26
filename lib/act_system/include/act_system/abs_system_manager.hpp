// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#include "act_foundation/abs_manager.hpp"
#include "act_threading/types/reusable_thread_result.hpp"

#include <cstdio>
#include <memory>
#include <string>
#include <vector>

namespace act::logger
{
class AbsLogger;
} // namespace act::logger

namespace act::threading
{
class ReusableThread;
} // namespace act::threading

namespace act::system
{

/**
 * @brief Abstract base class for system-level operations such as rebooting.
 *
 * Concrete subclasses provide the OS-specific implementations for pipe handling
 * and pre-reboot synchronisation.
 */
class AbsSystemManager : public act::foundation::AbsManager
{
  public:
    /**
     * @brief Constructor
     * @param parentLogger Parent logger used to create this manager's sub-logger
     */
    explicit AbsSystemManager(act::logger::AbsLogger &parentLogger);

    /** @brief Destructor */
    ~AbsSystemManager() override;

  public:
    /**
     * @brief Initialize the manager
     * @return true if initialization was successful, false otherwise
     */
    bool init() override;

    /**
     * @brief Check if a reboot has been asked
     * @return true if a reboot has been asked, false otherwise
     */
    [[nodiscard]] bool isRebootAsked() const
    {
        return m_rebootAsked;
    }

    /**
     * @brief Ask for a system reboot
     * @param delayInSec The delay before rebooting, in seconds. If 0, reboot immediately.
     * @return The result of the reboot request
     */
    act::threading::ReusableThreadResult::Enum askReboot(int delayInSec = 0);

  public:
    /**
     * @brief Call a system command and capture its output
     * @note Uses the platform-specific pipe primitives provided by subclasses.
     * @param cmd The command to execute
     * @param output Stream that receives the command output
     * @param logger Logger used to report errors
     * @return The exit code of the command, or -1 on failure
     */
    int callCommand(const std::string &cmd,
                    std::ostream &output,
                    const act::logger::AbsLogger &logger);

    /**
     * @brief Call a system command with arguments and capture its output
     * @note Joins @p cmdParts with a space separator and delegates to
     *       callCommand(const std::string &, ...).
     * @param cmdParts The command and its arguments as a list of strings
     * @param output Stream that receives the command output
     * @param logger Logger used to report errors
     * @return The exit code of the command, or -1 on failure
     */
    int callCommand(const std::vector<std::string> &cmdParts,
                    std::ostream &output,
                    const act::logger::AbsLogger &logger);

    /**
     * @brief Escape a command argument
     * @param arg The argument to escape
     * @param escapeChar The character to use for escaping (default: single quote)
     * @return The escaped argument
     */
    static std::string EscapeCmdArgument(const std::string &arg,
                                         char escapeChar = SINGLE_QUOTE_CHAR)
    {
        return escapeChar + arg + escapeChar;
    }

  protected:
    /**
     * @brief Open a pipe to execute @p cmd and read its output
     * @param cmd The shell command to execute
     * @return Pointer to the opened pipe, or nullptr on failure
     */
    virtual FILE *openPipe(const std::string &cmd) = 0;

    /**
     * @brief Close a pipe previously opened by openPipe()
     * @param pipe The pipe to close
     * @return The exit code of the underlying process
     */
    virtual int closePipe(FILE *pipe) = 0;

    /**
     * @brief Perform any OS-specific synchronisation required before a reboot
     * @note Called from the reboot thread before the delay and the reboot command.
     */
    virtual void syncBeforeReboot() = 0;

  private:
    /**
     * @brief Thread function to handle the reboot process
     * @param delayInSec The delay before rebooting, in seconds
     * @param systemManager Pointer to the AbsSystemManager instance
     */
    static void RebootThreadFunction(int delayInSec, AbsSystemManager *systemManager);

  public:
    /** @brief Logger category for this manager */
    static const constexpr char *LOGGER_CATEGORY = "sys";

    /** @brief Double quote char used for command arguments */
    static constexpr const char DOUBLE_QUOTE_CHAR = '"';

    /** @brief Single quote char used for command arguments */
    static constexpr const char SINGLE_QUOTE_CHAR = '\'';

  private:
    /** @brief Buffer size for command output */
    static constexpr int CMD_OUTPUT_BUFFER_SIZE = 128;

    /** @brief Separator for command parts when joining them into a single string */
    static constexpr const char *CMD_PART_SEPARATOR = " ";

    /** @brief Reboot command name */
    static constexpr const char *REBOOT_CMD_NAME = "reboot";

  private:
    /** @brief Logger helper */
    std::shared_ptr<act::logger::AbsLogger> m_logger;

    /** @brief Whether a reboot has been asked */
    bool m_rebootAsked = false;

    /** @brief Thread to handle the reboot process */
    act::threading::ReusableThread *m_rebootThread{nullptr};
};

} // namespace act::system
