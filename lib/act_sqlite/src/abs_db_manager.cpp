// SPDX-FileCopyrightText: 2025 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_sqlite/abs_db_manager.hpp"

/* # App includes (in alphabetical order) */

/* # Internal includes library */
#include "act_logger/services/logger_manager.hpp"
#include "act_system/system_critical_section.hpp"
#include "act_system/system_critical_section_guard.hpp"

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <fstream>
#include <iostream>

namespace act::sqlite
{

    AbsDbManager::AbsDbManager(const std::string &dbSlug,
                               const std::optional<std::filesystem::path> &migrationDataDir,
                               const act::logger::LoggerManager &loggerManager)
        : AbsManager(),
          m_dbSlug(dbSlug + "-db"),
          m_migrationDataDir(migrationDataDir),
          m_logger{loggerManager.createSubLogger(dbSlug + "-db")}
    {
    }

    bool AbsDbManager::applyMigrationUpdates()
    {
        act::system::SystemCriticalSection criticalSection(getDbSlug() + "-database-migration",
                                                           *m_logger);
        act::system::SystemCriticalSectionGuard guard(criticalSection);

        if (!m_migrationDataDir.has_value())
        {
            m_logger->error("Migration data directory is not set.");
            return false;
        }

        int currentVersion = getMigrationVersion();
        std::filesystem::path versionBumpScript = computeMigrationScriptPath(currentVersion);

        m_logger->infoStream() << "Current database version is " << currentVersion;
        m_logger->debugStream() << "Looking for migration scripts in " << m_migrationDataDir.value()
                                << ", starting with " << versionBumpScript.filename();

        bool allSucceed = true;
        int bumpCount = 0;
        while (allSucceed && std::filesystem::exists(versionBumpScript))
        {
            m_logger->debugStream() << "Applying migration script " << versionBumpScript.filename();

            allSucceed &= runScript(versionBumpScript);
            if (!allSucceed)
            {
                m_logger->errorStream()
                    << "Migration script " << versionBumpScript.filename() << " failed";
                return false;
            }

            allSucceed &= setMigrationVersion(currentVersion + 1);
            if (!allSucceed)
            {
                m_logger->errorStream()
                    << "Failed to bump migration version to " << (currentVersion + 1);
                return false;
            }

            (void)sync();

            currentVersion++;
            versionBumpScript = computeMigrationScriptPath(currentVersion);
            bumpCount++;
        }

        if (bumpCount == 0)
        {
            m_logger->debug("No migration found/required");
        }
        else
        {
            m_logger->debugStream() << "Successfully applied " << bumpCount << " migration scripts";
        }

        return allSucceed;
    }

    std::filesystem::path AbsDbManager::computeMigrationScriptPath(int currentVersion) const
    {
        if (!m_migrationDataDir.has_value())
        {
            m_logger->error("Migration data directory is not set.");
            return {};
        }

        // Look like <slug>-v<currentVersion>-to-v<currentVersion+1>.sql
        const std::filesystem::path filename = getDbSlug() + "-v" + std::to_string(currentVersion) +
                                               "-to-v" + std::to_string(currentVersion + 1) +
                                               ".sql";
        return m_migrationDataDir.value() / filename;
    }

    bool AbsDbManager::runScript(const std::filesystem::path &scriptPath)
    {
        std::ifstream scriptFile(scriptPath);

        if (!scriptFile)
        {
            m_logger->errorStream() << "Failed to open script file: " << scriptPath;
            return false;
        }

        std::string sql((std::istreambuf_iterator<char>(scriptFile)),
                        std::istreambuf_iterator<char>());
        return exec(sql);
    }

    bool AbsDbManager::open(bool autoMigrate)
    {
        bool allSucceed = true;

        m_logger->debug("Opening database");

        if (allSucceed)
        {
            allSucceed &= openImpl();
        }

        if (allSucceed && autoMigrate)
        {
            allSucceed &= applyMigrationUpdates();
        }

        return allSucceed;
    }

} // namespace act::sqlite
