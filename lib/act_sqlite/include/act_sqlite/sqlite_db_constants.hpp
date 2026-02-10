// SPDX-FileCopyrightText: 2025 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/// @brief Set of constants related to SQLite
namespace SQLiteDbConstants
{
    /** @brief SQLite boolean type is an alias for integer with known true/false values.  */
    enum BoolIntVal
    {
        False = 0, ///< SQLite false is coded as integer 0
        True = 1   ///< SQLite true is coded as integer 1
    };
} // namespace SQLiteDbConstants