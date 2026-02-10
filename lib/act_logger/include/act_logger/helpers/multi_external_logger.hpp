// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/* # App includes (in alphabetical order) */
#include "act_logger/printers/abs_external_logger.hpp"

/* # Internal includes library */
#include "act_misc/constants/def_soft.hpp"

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <memory>
#include <vector>

/* # Forward declaration */

/** @brief This is an external logger that can log to multiple external loggers */
class MultiExternalLogger : public AbsExternalLogger
{
  public:
    /** @brief Class constructor */
    explicit MultiExternalLogger(const std::vector<std::shared_ptr<AbsExternalLogger>> &loggers);

    /** @brief Class destructor */
    ~MultiExternalLogger() override = default;

  public:
    /**
     * @brief Log a message
     * @param level The logs level
     * @param message The message to log
     * @param categories The categories associated to the log message. This is ignored in this
     *                   implementation, because we use the categories of each logger.
     */
    void log(LogsLevel::Enum level,
             const std::string &message,
             const std::vector<std::string> &categories) override;

  protected:
    /**
     * @brief Log a message to the external loggers
     * @param level The logs level
     * @param message The message to log
     * @param categories The categories associated to the log message
     */
    void logToExternal(LogsLevel::Enum level,
                       const std::string &message,
                       const std::vector<std::string> &categories) override
    {
        // This method is not used in this implementation
        UNUSED(level);
        UNUSED(message);
        UNUSED(categories);
    }

  private:
    /** @brief The list of loggers to use */
    std::vector<std::shared_ptr<AbsExternalLogger>> m_loggers;
};
