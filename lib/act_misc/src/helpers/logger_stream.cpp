// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_misc/helpers/logger_stream.hpp"

/* # App includes (in alphabetical order) */
#include "act_misc/models/abs_logger.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */

LoggerStream::LoggerStream(LogsLevel::Enum level, const AbsLogger &logger)
    : m_logger{logger},
      m_level{level}
{
}

LoggerStream::~LoggerStream()
{
    auto tmpLog = m_stream.str();
    if (tmpLog.empty())
    {
        // No log to perform
        return;
    }

    m_logger.log(m_level, tmpLog);
}
