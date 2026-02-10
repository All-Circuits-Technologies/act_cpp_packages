// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_logger/helpers/sub_logger_helper.hpp"

/* # App includes (in alphabetical order) */

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */

namespace act::logger
{

    SubLoggerHelper::SubLoggerHelper(const std::string &category,
                                     LoggerHelper &parentLogger,
                                     LogsLevel::Enum minLevel)
        : LoggerHelper(SubLoggerHelper::ConcatenateCategories(category, parentLogger), minLevel),
          m_parentLogger{parentLogger}
    {
    }

    SubLoggerHelper::SubLoggerHelper(LoggerHelper &parentLogger, LogsLevel::Enum minLevel)
        : LoggerHelper(parentLogger.getCategories(), minLevel),
          m_parentLogger{parentLogger}
    {
    }

    std::vector<std::string> SubLoggerHelper::ConcatenateCategories(
        const std::string &category, const LoggerHelper &parentLogger)
    {
        std::vector<std::string> categories = parentLogger.getCategories();
        categories.push_back(category);
        return categories;
    }

} // namespace act::logger
