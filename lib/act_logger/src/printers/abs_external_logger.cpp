// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_logger/printers/abs_external_logger.hpp"

/* # App includes (in alphabetical order) */

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */

namespace act::logger
{

    AbsExternalLogger::AbsExternalLogger(
        LogsLevel::Enum minLevel, const std::map<std::string, LogsLevel::Enum> &minLevelByCategory)
        : m_minLevel{minLevel},
          m_minLevelByCategory{minLevelByCategory}
    {
    }

    bool AbsExternalLogger::isLoggable(LogsLevel::Enum level,
                                       const std::vector<std::string> &categories) const
    {
        bool categoryMatched = false;
        if (m_minLevelByCategory.size() > 0)
        {
            // Check if any category has a specific min level
            for (const auto &category : categories)
            {
                auto it = m_minLevelByCategory.find(category);
                if (it != m_minLevelByCategory.end())
                {
                    // Found a matching category, check its min level
                    if (level < it->second)
                    {
                        // We skip log because the level is lower than the category's minLevel
                        // Continue to check other categories
                        continue;
                    }
                    // We found a matching category and its log level match the requirement, no
                    // need to check further
                    categoryMatched = true;
                    break;
                }
            }
        }

        if (!categoryMatched && level < m_minLevel)
        {
            // We skip log because the level is lower than the minLevel
            return false;
        }

        return true;
    }

    void AbsExternalLogger::log(LogsLevel::Enum level,
                                const std::string &message,
                                const std::vector<std::string> &categories)
    {
        if (!isLoggable(level, categories))
        {
            // Nothing to do
            return;
        }

        logToExternal(level, message, categories);
    }

} // namespace act::logger
