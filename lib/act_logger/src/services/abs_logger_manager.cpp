// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_logger/services/abs_logger_manager.hpp"

/* # App includes (in alphabetical order) */
#include "act_logger/helpers/logger_helper.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <memory>

namespace act::logger
{

    AbsLoggerManager::AbsLoggerManager()
        : AbsManager()
    {
    }

    bool AbsLoggerManager::init()
    {
        auto externalLogger = getExternalLogger();
        m_loggerHelper = std::make_shared<LoggerHelper>(externalLogger);

        info("LoggerManager initialized successfully.");
        return true;
    }

} // namespace act::logger
