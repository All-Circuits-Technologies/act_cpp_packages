// SPDX-FileCopyrightText: 2025 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/// @brief Set of constants related to SQLite
namespace act::sqlite::SQLiteDbConstants
{
    /** @brief SQLite boolean type is an alias for integer with known true/false values.  */
    enum BoolIntVal
    {
        FALSE = 0, ///< SQLite false is coded as integer 0
        TRUE = 1   ///< SQLite true is coded as integer 1
    };
} // namespace act::sqlite::SQLiteDbConstants
