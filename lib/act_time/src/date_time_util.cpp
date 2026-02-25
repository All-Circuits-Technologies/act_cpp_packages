// SPDX-FileCopyrightText: 2026 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#include "act_time/date_time_util.hpp"

#include "act_foundation/constants/def_soft.hpp"

#include <ctime>

namespace act::time
{

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

} // namespace act::time
