// SPDX-FileCopyrightText: 2026 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#include <string_view>

#include "act_db_core/db_core_constants.hpp"

namespace act::logger
{
class AbsLogger;
}

namespace act::db_core
{
class AbsDbExecutor;

/**
 * @brief Helper class to handle database transactions
 * @note This class will automatically rollback the transaction if it is not committed when
 * destructed, so it is recommended to use it with a local scope to ensure proper transaction
 * handling.
 */
class DbTransaction
{
  private:
    /**
     * @brief State of the transaction, to track if it has been started, committed or rolled back
     */
    enum class State
    {
        NOT_STARTED,
        STARTED,
        COMMITTED,
        ROLLED_BACK
    };

  public:
    /**
     * @brief Construct a new Db Transaction object
     *
     * @param db Shared database provider to use for executing transaction commands
     * @param logger The logger to use for logging transaction operations
     */
    explicit DbTransaction(AbsDbExecutor &db, const act::logger::AbsLogger &logger);

    /** @brief Destructor */
    virtual ~DbTransaction();

  public:
    /**
     * @brief Begin the transaction
     * @param beginExtension This is the extension to the BEGIN statement, which can be used to
     * specify the transaction type.
     * @return True if the transaction was successfully started, false otherwise
     */
    bool begin(std::string_view beginExtension = DbCoreConstants::TRANSACTION_NAME);

    /**
     * @brief Commit the transaction
     * @return True if the transaction was successfully committed, false otherwise
     */
    bool commit();

    /**
     * @brief Rollback the transaction
     * @return True if the transaction was successfully rolled back, false otherwise
     */
    bool rollback();

  private:
    /**
     * @brief Rollback the transaction if it has not been committed yet, to ensure proper
     * transaction handling
     *
     * @return True if the transaction was successfully rolled back, committed or was not started,
     * false if the rollback failed
     */
    bool rollbackIfNotCommitted();

  private:
    /**
     * @brief Default SQL command to commit a transaction, using the standard "COMMIT TRANSACTION"
     */
    static inline const std::string COMMIT_TRANSACTION =
        DbCoreConstants::COMMIT_NAME + " " + DbCoreConstants::TRANSACTION_NAME;

    /**
     * @brief Default SQL command to rollback a transaction, using the standard "ROLLBACK
     * TRANSACTION"
     */
    static inline const std::string ROLLBACK_TRANSACTION =
        DbCoreConstants::ROLLBACK_NAME + " " + DbCoreConstants::TRANSACTION_NAME;

  private:
    /** @brief Shared database handle */
    AbsDbExecutor &m_db;

    /** @brief Logger for transaction operations */
    const act::logger::AbsLogger &m_logger;

    /** @brief Flag to indicate if the transaction has been committed or rolled back */
    State m_state;
};
} // namespace act::db_core
