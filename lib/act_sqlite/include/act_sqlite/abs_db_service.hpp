// SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/// @file abs_db_service.hpp
/// @brief Abstract base class for per-table SQLite database services.

#include <functional>
#include <memory>
#include <optional>
#include <string_view>

#include "act_logger/helpers/logger_helper.hpp"

#include <SQLiteCpp/SQLiteCpp.h>

namespace act::sqlite
{

/**
 * @brief Abstract base class for per-table SQLite database services.
 *
 * Provides common infrastructure for services that perform queries on a
 * specific database table: a shared database handle, a logger, and helper
 * methods that wrap queries in try/catch blocks for consistent error handling.
 */
class AbsDbService
{
  public:
    /** @brief Construct a database service
     * @param db SQLite database handle (must be opened)
     * @param logger Logger helper for this service
     */
    AbsDbService(std::shared_ptr<SQLite::Database> db,
                 std::shared_ptr<act::logger::LoggerHelper> logger);

    /** @brief Destructor */
    virtual ~AbsDbService() = default;

  protected:
    /** @brief Execute a query with no return value
     * @param operationName Name used in error logs
     * @param queryFunc Lambda receiving the database handle
     * @return true on success, false if an exception was caught
     */
    bool executeQuery(std::string_view operationName,
                      const std::function<void(SQLite::Database &)> &queryFunc) const;

    /** @brief Execute a query returning a result
     * @tparam T The result type
     * @param operationName Name used in error logs
     * @param queryFunc Lambda receiving the database handle and returning a value
     * @return The result on success, std::nullopt if an exception was caught
     */
    template <typename T>
    std::optional<T> executeQueryWithResult(
        std::string_view operationName, const std::function<T(SQLite::Database &)> &queryFunc) const
    {
        std::optional<T> result;
        try
        {
            result = queryFunc(*m_db);
        }
        catch (const SQLite::Exception &e)
        {
            m_logger->errorStream() << "Error in " << operationName << ": " << e.what();
        }
        return result;
    }

    /** @brief Shared database handle */
    std::shared_ptr<SQLite::Database> m_db;

    /** @brief Logger helper */
    std::shared_ptr<act::logger::LoggerHelper> m_logger;
};

} // namespace act::sqlite
