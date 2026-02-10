// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_logger/printers/std_console_logger.hpp"

/* # App includes (in alphabetical order) */
#include "act_logger/printers/abs_external_logger.hpp"

/* # Internal includes library */
#include "act_text/vector_string_util.hpp"

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <iostream>

namespace act::logger
{

    StdConsoleLogger::StdConsoleLogger(
        LogsLevel::Enum minLevel,
        LogsLevel::Enum minLevelToPrintToStdErr,
        const std::map<std::string, LogsLevel::Enum> &minLevelByCategory)
        : AbsExternalLogger(minLevel, minLevelByCategory),
          m_minLevelToPrintToStdErr{minLevelToPrintToStdErr}
    {
    }

    void StdConsoleLogger::logToExternal(LogsLevel::Enum level,
                                         const std::string &message,
                                         const std::vector<std::string> &categories)
    {
        auto formattedMessage = FormatLogMessage(level, message, categories);

        // Output to standard console
        if (level < m_minLevelToPrintToStdErr)
        {
            std::cout << formattedMessage << std::endl;
        }
        else
        {
            std::cerr << formattedMessage << std::endl;
        }
    }

    std::string StdConsoleLogger::FormatLogMessage(LogsLevel::Enum level,
                                                   const std::string &message,
                                                   const std::vector<std::string> &categories)
    {
        std::string formattedMessage;

        // Add level
        formattedMessage += "[" + LogsLevel::ToString(level) + "] ";

        // Add categories if any
        if (!categories.empty())
        {
            formattedMessage += "[";
            formattedMessage += VectorStringUtil::join(categories, CATEGORIES_SEPARATOR);
            formattedMessage += "] ";
        }

        // Add the actual message
        formattedMessage += message;

        return formattedMessage;
    }

} // namespace act::logger
