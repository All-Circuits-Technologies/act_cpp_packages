// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#include "act_logger/services/logger_manager.hpp"

#include "act_logger/constants/logs_constants.hpp"
#include "act_logger/printers/std_console_logger.hpp"

namespace act::logger
{

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

} // namespace act::logger
