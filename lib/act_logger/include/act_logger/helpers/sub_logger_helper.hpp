// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/* # App includes (in alphabetical order) */
#include "act_logger/helpers/logger_helper.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */

class SubLoggerHelper : public LoggerHelper
{
  public:
    /**
     * @brief Class constructor
     * @param category The additional category for this sub-logger
     * @param parentLogger The parent logger
     * @param minLevel The minimum logs level for this sub-logger
     */
    explicit SubLoggerHelper(const std::string &category,
                             LoggerHelper &parentLogger,
                             LogsLevel::Enum minLevel = LogsLevel::Enum::TRACE);

    /**
     * @brief Class constructor
     * @param parentLogger The parent logger
     * @param minLevel The minimum logs level for this sub-logger
     */
    explicit SubLoggerHelper(LoggerHelper &parentLogger,
                             LogsLevel::Enum minLevel = LogsLevel::Enum::TRACE);

    /** @brief Class destructor */
    ~SubLoggerHelper() override = default;

  public:
    /**
     * @brief Get the external logger
     * @return The external logger
     */
    [[nodiscard]] const std::shared_ptr<AbsExternalLogger> &getLogger() const override
    {
        return m_parentLogger.getLogger();
    }

    /**
     * @brief Update the external logger
     * @param externalLogger The new external logger
     */
    void updateLogger(const std::shared_ptr<AbsExternalLogger> &externalLogger) override
    {
        m_parentLogger.updateLogger(externalLogger);
    }

  private:
    /**
     * @brief Concatenate the categories of the parent logger with the new category
     * @param category The new category
     * @param parentLogger The parent logger
     * @return The concatenated categories
     */
    static std::vector<std::string> ConcatenateCategories(const std::string &category,
                                                          const LoggerHelper &parentLogger);

  private:
    /** @brief The parent logger */
    LoggerHelper &m_parentLogger;
};
