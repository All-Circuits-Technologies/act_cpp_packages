// SPDX-FileCopyrightText: 2026 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#include <string>

/// @brief Set of constants related to SQLite
namespace act::db_core::DbCoreConstants
{
/**
 * @brief The SQL TRANSACTION statement name
 */
static inline const std::string TRANSACTION_NAME = "TRANSACTION";

/**
 * @brief The SQL BEGIN statement name
 */
static inline const std::string BEGIN_NAME = "BEGIN";

/**
 * @brief The SQL COMMIT statement name
 */
static inline const std::string COMMIT_NAME = "COMMIT";

/**
 * @brief The SQL ROLLBACK statement name
 */
static inline const std::string ROLLBACK_NAME = "ROLLBACK";
} // namespace act::db_core::DbCoreConstants
