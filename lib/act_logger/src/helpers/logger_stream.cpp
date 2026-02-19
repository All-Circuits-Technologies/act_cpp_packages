// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_logger/helpers/logger_stream.hpp"

/* # App includes (in alphabetical order) */
#include "act_logger/models/abs_logger.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */

namespace act::logger
{

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

} // namespace act::logger
