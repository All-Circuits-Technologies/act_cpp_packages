<!-- SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com> -->

<!-- SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1 -->

# act_sqlite

SQLite database management library providing a database abstraction layer, connection management,
schema migration, and logging integration.

## Dependencies

- act_db_core
- act_foundation
- act_logger
- act_system
- SQLiteCpp (libsqlitecpp-dev)

## Debian Packages

```bash
sudo apt install libsqlitecpp-dev
```

## Components

| Class               | Header                               | Role                                                  |
| ------------------- | ------------------------------------ | ----------------------------------------------------- |
| `ASqLiteDbManager`  | `act_sqlite/sqlite_db_manager.hpp`   | SQLite-specific manager (opens file, provides handle) |
| `SQLiteDbConstants` | `act_sqlite/sqlite_db_constants.hpp` | Boolean integer value helpers                         |

Engine-agnostic base classes (`AbsDbManager`, `AbsDbExecutor`, `DbProtectService`,
`DbTransaction`) are provided by `act_db_core`. See its README for details.

---

## Usage

### 1. Subclass `ASqLiteDbManager` to own the database lifecycle

Create a concrete class that inherits `ASqLiteDbManager`. Its constructor must forward the
database file path, a slug (used in log traces and migration script names), the migration
directory, and the logger manager.

Override `init()` to open the database, apply migrations, configure options (e.g. busy timeout),
and instantiate per-table services using the shared handle exposed by `getHandle()`.

```cpp
// my_database.hpp
#include "act_sqlite/sqlite_db_manager.hpp"

class MyTableService; // forward declaration

class MyDatabase : public act::sqlite::ASqLiteDbManager
{
  public:
    explicit MyDatabase(std::filesystem::path dbFilePath,
                        std::filesystem::path migrationDir,
                        const act::logger::LoggerManager &loggerManager);
    ~MyDatabase() override;

    bool init() override;
    void shutdown();

    [[nodiscard]] MyTableService &accessMyTable() const;

  private:
    static constexpr int BUSY_TIMEOUT_MS = 1000;
    std::unique_ptr<MyTableService> m_myTableService;
};
```

```cpp
// my_database.cpp
#include "my_database.hpp"
#include "my_table_service.hpp"

MyDatabase::MyDatabase(std::filesystem::path dbFilePath,
                       std::filesystem::path migrationDir,
                       const act::logger::LoggerManager &loggerManager)
    : ASqLiteDbManager(std::move(dbFilePath), "my-db", std::move(migrationDir), loggerManager)
{
}

bool MyDatabase::init()
{
    if (!open(true))           // opens the file and runs pending migrations
        return false;
    if (!setBusyTimeout(BUSY_TIMEOUT_MS))
        return false;

    m_myTableService = std::make_unique<MyTableService>(getHandle(), *getLogger());
    return true;
}

void MyDatabase::shutdown()
{
    m_myTableService.reset();
}

MyTableService &MyDatabase::accessMyTable() const
{
    return *m_myTableService;
}
```

> **Note:** `ASqLiteDbManager` automatically registers a `REGEXP` function on the SQLite
> connection at open time. SQL queries can use `col REGEXP 'pattern'` without any extra setup.

### 2. Declare table and column names as constants

Avoid raw strings scattered across query lambdas. Centralise all table and column names in a
dedicated constants header. This makes schema changes a single-point edit and keeps query code
readable.

```cpp
// my_db_constants.hpp
#pragma once

namespace MyDbConstants
{
    namespace Table::MyTable
    {
        static constexpr const char *NAME = "my_table"; ///< Table name

        namespace Column
        {
            static constexpr const char *ID   = "id";   ///< Primary key
            static constexpr const char *NAME = "name"; ///< Display name
        } // namespace Column
    } // namespace Table::MyTable
} // namespace MyDbConstants
```

### 3. Write per-table services

Each table gets its own service class. Receive the `std::shared_ptr<SQLite::Database>` handle
from `getHandle()` and a logger reference, then use `DbProtectService` (from `act_db_core`) to
wrap queries with error handling and optional transaction management.

- `protectQuery(name, lambda)` — runs a `bool`-returning statement; returns `bool`.
- `protectQueryWithResult<T>(name, lambda)` — runs a statement that returns `T`; returns
  `std::optional<T>` (`std::nullopt` on any exception).

Both helpers wrap the query in a transaction by default.

```cpp
// my_table_service.hpp
#include "act_db_core/services/db_protect_service.hpp"
#include <SQLiteCpp/Database.h>
#include <memory>
#include <optional>
#include <vector>

struct MyRow { int id; std::string name; };

class MyTableService
{
  public:
    explicit MyTableService(std::shared_ptr<SQLite::Database> db,
                            act::logger::AbsLogger &parentLogger);
    ~MyTableService() = default;

    [[nodiscard]] std::optional<std::vector<MyRow>> getAll() const;
    bool insert(const MyRow &row);

  private:
    std::shared_ptr<SQLite::Database> m_db;
    act::db_core::DbProtectService m_protect;
};
```

```cpp
// my_table_service.cpp
#include "my_table_service.hpp"
#include "my_db_constants.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

namespace
{
    namespace Col = MyDbConstants::Table::MyTable::Column;

    // Build the query once at startup — no raw strings in the query logic below.
    // NOLINTNEXTLINE(cert-err58-cpp)
    const std::string SELECT_ALL =
        std::string("SELECT ") + Col::ID + ", " + Col::NAME +
        " FROM " + MyDbConstants::Table::MyTable::NAME;

    const std::string INSERT_ROW =
        std::string("INSERT INTO ") + MyDbConstants::Table::MyTable::NAME +
        " (" + Col::ID + ", " + Col::NAME + ") VALUES (?, ?)";
} // namespace

MyTableService::MyTableService(std::shared_ptr<SQLite::Database> db,
                               act::logger::AbsLogger &parentLogger)
    : m_db(std::move(db)), m_protect(*m_db, parentLogger)
{
}

std::optional<std::vector<MyRow>> MyTableService::getAll() const
{
    return m_protect.protectQueryWithResult<std::vector<MyRow>>(
        "getAll",
        [this](act::db_core::AbsDbExecutor &) -> std::optional<std::vector<MyRow>> {
            SQLite::Statement query(*m_db, SELECT_ALL);
            std::vector<MyRow> rows;
            while (query.executeStep())
                rows.push_back({query.getColumn(Col::ID).getInt(),
                                query.getColumn(Col::NAME).getString()});
            return rows;
        },
        false); // read-only: no transaction needed
}

bool MyTableService::insert(const MyRow &row)
{
    return m_protect.protectQuery(
        "insert",
        [this, &row](act::db_core::AbsDbExecutor &) {
            SQLite::Statement stmt(*m_db, INSERT_ROW);
            stmt.bind(1, row.id);
            stmt.bind(2, row.name);
            stmt.exec();
            return true;
        });
}
```

### 4. Wire the migration scripts

Migration scripts must be named `<slug>-db-v<N>-to-v<N+1>.sql`
(e.g. `my-db-db-v0-to-v1.sql`, `my-db-db-v1-to-v2.sql`) and placed in the directory passed as
`migrationDir`. The manager runs them in version order when `open(true)` is called.

---

## CMake integration

```cmake
target_link_libraries(my_target PRIVATE act_sqlite)
```
