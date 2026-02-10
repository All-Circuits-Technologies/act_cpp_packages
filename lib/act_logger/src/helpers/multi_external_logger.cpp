// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_logger/helpers/multi_external_logger.hpp"

/* # App includes (in alphabetical order) */
#include "act_logger/helpers/logger_helper.hpp"

/* # Internal includes library */
#include "act_misc/constants/def_soft.hpp"

/* # Extern includes: Library */

/* # Extern includes: Global */

MultiExternalLogger::MultiExternalLogger(
    const std::vector<std::shared_ptr<AbsExternalLogger>> &loggers)
    : AbsExternalLogger(LogsLevel::Enum::TRACE),
      m_loggers{loggers}
{
}

void MultiExternalLogger::log(LogsLevel::Enum level,
                              const std::string &message,
                              const std::vector<std::string> &categories)
{
    for (const auto &logger : m_loggers)
    {
        if (logger)
        {
            logger->log(level, message, categories);
        }
    }
}
