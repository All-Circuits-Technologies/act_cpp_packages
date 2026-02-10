// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_logger/services/logger_manager.hpp"

/* # App includes (in alphabetical order) */
#include "act_logger/constants/logs_constants.hpp"
#include "act_logger/printers/std_console_logger.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */

LoggerManager::LoggerManager(LogsLevel::Enum minLevelToPrintToStdErr)
    : AbsLoggerManager(),
      m_minLevelToPrintToStdErr{minLevelToPrintToStdErr}
{
}

bool LoggerManager::init()
{
    m_consoleLogger = std::make_shared<StdConsoleLogger>(LogsConstants::DEFAULT_CONSOLE_LOGS_LEVEL,
                                                         m_minLevelToPrintToStdErr);

    return AbsLoggerManager::init();
}

void LoggerManager::setCslMinLogLevel(LogsLevel::Enum minLevel)
{
    if (m_consoleLogger)
    {
        m_consoleLogger->setMinLevel(minLevel);
    }
}

std::shared_ptr<AbsExternalLogger> LoggerManager::getExternalLogger() const
{
    return m_consoleLogger;
}
