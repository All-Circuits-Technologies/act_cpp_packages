// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/* # App includes (in alphabetical order) */
#include "act_logger/models/abs_logger.hpp"
#include "act_misc/managers/abs_manager.hpp"
#include "act_misc/types/reusable_thread_result.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <string>
#include <vector>

/* # Forward declaration */

class AbsLogger;
class ReusableThread;

/** @brief The SystemManager class handles system-level operations such as rebooting */
class SystemManager : public AbsManager
{
  public:
    /**
     * @brief Constructor
     */
    explicit SystemManager(AbsLogger &parentLogger);

    /**
     * @brief Destructor
     */
    ~SystemManager() override;

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
     * @param logger The logger to use for logging
     * @param delayInSec The delay before rebooting, in seconds. If 0, reboot immediately.
     * @return The result of the reboot request
     */
    ReusableThreadResult::Enum askReboot(int delayInSec = 0);

  public:
    /**
     * @brief Call a system command
     * @note We use popen to capture the command output, execl needs to be used in a forked process
     *       or it will replace the current process and kill the application at the end.
     * @param cmd The command to execute
     * @param output The output of the command
     * @param logger The logger to use for logging errors
     * @return The return code of the command
     */
    static int CallCommand(const std::string &cmd, std::ostream &output, const AbsLogger &logger);

    /**
     * @brief Call a system command with arguments
     * @note We use popen to capture the command output, execl needs to be used in a forked process
     *       or it will replace the current process and kill the application at the end.
     * @param cmdParts The command and its arguments as a list of strings
     * @param output The output of the command
     * @param logger The logger to use for logging errors
     * @return The return code of the command
     */
    static int CallCommand(const std::vector<std::string> &cmdParts,
                           std::ostream &output,
                           const AbsLogger &logger);

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

  private:
    /**
     * @brief Thread function to handle the reboot process
     * @param delayInSec The delay before rebooting, in seconds
     * @param systemManager Pointer to the SystemManager instance
     */
    static void RebootThreadFunction(int delayInSec, SystemManager *systemManager);

  public:
    /** @brief Logger category for this manager */
    static const constexpr char *LOGGER_CATEGORY = "sys";

    /**
     * @brief Double quote char used for command arguments
     */
    static constexpr const char DOUBLE_QUOTE_CHAR = '"';

    /**
     * @brief Single quote char used for command arguments
     */
    static constexpr const char SINGLE_QUOTE_CHAR = '\'';

  private:
    /**
     * @brief Buffer size for command output
     */
    static constexpr int CMD_OUTPUT_BUFFER_SIZE = 128;

    /**
     * @brief Separator for command parts when joining them into a single string
     */
    static constexpr const char *CMD_PART_SEPARATOR = " ";

    /**
     * @brief reboot command name
     */
    static constexpr const char *REBOOT_CMD_NAME = "reboot";

  private:
    /** @brief Logger helper */
    std::shared_ptr<AbsLogger> m_logger;

    /**
     * @brief Whether a reboot has been asked
     */
    bool m_rebootAsked = false;

    /** @brief Thread to handle firmware update process */
    ReusableThread *m_rebootThread{nullptr};
};
