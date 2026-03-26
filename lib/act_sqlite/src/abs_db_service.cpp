// SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#include "act_sqlite/abs_db_service.hpp"

namespace act::sqlite
{

AbsDbService::AbsDbService(std::shared_ptr<SQLite::Database> db,
                           std::shared_ptr<act::logger::LoggerHelper> logger)
    : m_db(std::move(db)),
      m_logger(std::move(logger))
{
}

bool AbsDbService::executeQuery(std::string_view operationName,
                                const std::function<void(SQLite::Database &)> &queryFunc) const
{
    bool success = false;
    try
    {
        queryFunc(*m_db);
        success = true;
    }
    catch (const SQLite::Exception &e)
    {
        m_logger->errorStream() << "Error in " << operationName << ": " << e.what();
    }
    return success;
}

} // namespace act::sqlite
