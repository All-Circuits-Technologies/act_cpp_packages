// SPDX-FileCopyrightText: 2026 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#include <functional>
#include <string>

class tm;

namespace act::time
{

/** @brief Contains the date and time utility functions */
class DateTimeUtil
{
  public:
    /**
     * @brief Get the current date and time in ISO 8601 format (UTC).
     * @return A string representing the current date and time in ISO 8601 format.
     */
    static std::string GetCurrentIsoDateTimeUtc();

    /**
     * @brief Get the current date and time in ISO 8601 format (Local Time).
     * @return A string representing the current date and time in ISO 8601 format.
     */
    static std::string GetCurrentIsoDateTimeLocal();

  private:
    /**
     * @brief Get the current date and time in ISO 8601 format using the specified time
     * converter.
     * @param timeConverter A function that converts a time_t pointer to a tm pointer.
     * @return A string representing the current date and time in ISO 8601 format.
     */
    static std::string GetCurrentIsoDateTime(
        const std::function<tm *(const time_t *)> &timeConverter);

  private:
    /** @brief ISO time pattern for date-time formatting */
    static const constexpr char *ISO_TIME_PATTERN = "%FT%TZ";

    /** @brief Buffer size for ISO time pattern */
    static const constexpr size_t ISO_TIME_PATTERN_BUFFER_SIZE = 32;
};

} // namespace act::time
