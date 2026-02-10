// SPDX-FileCopyrightText: 2026 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_misc/utilities/date_time_util.hpp"

/* # App includes (in alphabetical order) */

/* # Internal includes library */
#include "act_misc/constants/def_soft.hpp"

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <ctime>

std::string DateTimeUtil::GetCurrentIsoDateTimeUtc()
{
    return GetCurrentIsoDateTime(std::gmtime);
}

std::string DateTimeUtil::GetCurrentIsoDateTimeLocal()
{
    return GetCurrentIsoDateTime(std::localtime);
}

std::string DateTimeUtil::GetCurrentIsoDateTime(
    const std::function<tm *(const time_t *)> &timeConverter)
{
    const auto now = std::time(nullptr);
    char buffer[ISO_TIME_PATTERN_BUFFER_SIZE] = {0};

    // No need to test the return value, we assume the buffer is large enough
    UNUSED(
        std::strftime(buffer, ISO_TIME_PATTERN_BUFFER_SIZE, ISO_TIME_PATTERN, timeConverter(&now)));

    return {buffer};
}
