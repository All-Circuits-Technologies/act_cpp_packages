<!-- SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com> -->

<!-- SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1 -->

# act_sqlite

SQLite database management library providing a database abstraction layer, connection management,
schema migration, and logging integration.

## Dependencies

- act_foundation
- act_logger
- act_system
- SQLiteCpp (libsqlitecpp-dev)

## Debian Packages

```bash
sudo apt install libsqlitecpp-dev
```

## Components

| Class               | Header                               | Role                                                    |
| ------------------- | ------------------------------------ | ------------------------------------------------------- |
| `AbsDbManager`      | `act_sqlite/abs_db_manager.hpp`      | Engine-agnostic base: migration runner, script executor |
| `ASqLiteDbManager`  | `act_sqlite/sqlite_db_manager.hpp`   | SQLite-specific manager (opens file, provides handle)   |
| `AbsDbService`      | `act_sqlite/abs_db_service.hpp`      | Base for per-table query services                       |
| `SQLiteDbConstants` | `act_sqlite/sqlite_db_constants.hpp` | Boolean integer value helpers                           |
| `db_log_helper.hpp` | `act_sqlite/db_log_helper.hpp`       | Convenience macros for error/guard returns              |

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

    m_myTableService = std::make_unique<MyTableService>(getHandle(), getLogger());
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

### 2. Declare table and column names as constants

Avoid raw strings scattered across query lambdas. Centralise all table and column names in a
dedicated constants header. This makes schema changes a single-point edit and keeps query code
readable.

```cpp
// my_db_constants.hpp
#pragma once

namespace MyDbConstants
{
    /** @brief Prefix for named SQL parameters */
    static constexpr const char *PREFIX_PARAM_KEY = "$";

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

### 3. Write per-table services with `AbsDbService`

Each table gets its own service class. Inherit `AbsDbService`, inherit its constructor, and use
the two query helpers:

- `executeQuery(name, lambda)` — runs a statement with no return value; returns `bool`.
- `executeQueryWithResult<T>(name, lambda)` — runs a statement that returns `T`; returns
  `std::optional<T>` (`std::nullopt` on any `SQLite::Exception`).

Both helpers log the error and operation name automatically on failure.

```cpp
// my_table_service.hpp
#include "act_sqlite/abs_db_service.hpp"
#include <optional>
#include <vector>

struct MyRow { int id; std::string name; };

class MyTableService : public act::sqlite::AbsDbService
{
  public:
    using act::sqlite::AbsDbService::AbsDbService; // inherit constructor

    ~MyTableService() override = default;

    [[nodiscard]] std::optional<std::vector<MyRow>> getAll() const;
    bool insert(const MyRow &row);
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

std::optional<std::vector<MyRow>> MyTableService::getAll() const
{
    return executeQueryWithResult<std::vector<MyRow>>(
        "getAll", [](SQLite::Database &db) -> std::vector<MyRow> {
            SQLite::Statement query(db, SELECT_ALL);
            std::vector<MyRow> rows;
            while (query.executeStep())
                rows.push_back({query.getColumn(Col::ID).getInt(),
                                query.getColumn(Col::NAME).getString()});
            return rows;
        });
}

bool MyTableService::insert(const MyRow &row)
{
    return executeQuery("insert", [&row](SQLite::Database &db) {
        SQLite::Statement stmt(db, INSERT_ROW);
        stmt.bind(1, row.id);
        stmt.bind(2, row.name);
        stmt.exec();
    });
}
```

### 3. Wire the migration scripts

Migration scripts must be named `<slug>-db-<version>.sql` (e.g. `my-db-1.sql`, `my-db-2.sql`)
and placed in the directory passed as `migrationDir`. The manager runs them in order on `open()`.

---

## CMake integration

```cmake
target_link_libraries(my_target PRIVATE act_sqlite)
```
