// SPDX-FileCopyrightText: 2026 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#include <filesystem>
#include <optional>
#include <string>

namespace act::db::core
{
/**
 * @brief Abstract database executor interface, to be implemented by database engine specific
 * executors, and used by database engine agnostic services to execute queries without knowing
 * the underlying database engine.
 */
class AbsDbExecutor
{
  public:
    /**
     * @brief Construct a new Abs Db Provider object
     */
    explicit AbsDbExecutor() = default;

    /** @brief Destroy the Abs Db Provider object */
    virtual ~AbsDbExecutor() = default;

  public:
    /**
     * @brief Tells if database is opened
     * @return True if database is opened, false otherwise
     */
    [[nodiscard]] virtual bool isOpened() const = 0;

    /**
     * @brief Execute a simple statement with no request result
     * @param sql SQL query to execute, or PRAGMA query, etc
     * @return True if executed successfully, false otherwise
     */
    virtual bool exec(const std::string &sql) = 0;

    /**
     * @brief Script execution helper
     * @return True upon success, false otherwise
     */
    virtual bool runScript(const std::filesystem::path &scriptPath) = 0;

    /**
     * @brief Helper for queries returning a simple integer
     * @param sql Query to execute
     * @return The integer result (first column of first result row),
     *         or empty optional if error
     */
    virtual std::optional<int> execAndGetInt(const std::string &sql) = 0;
};
} // namespace act::db::core
