<!--
SPDX-FileCopyrightText: 2026 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>

SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1
-->

# act_db_core

Engine-agnostic database management library providing a database abstraction layer, connection
management, schema migration, transaction handling, and logging integration.

This library is not used directly by application code. It provides the base classes and
interfaces that concrete database backends (e.g. `act_sqlite`) build upon.

## Dependencies

- act_foundation
- act_logger
- act_system

## Components

| Class/File            | Header                                        | Role                                                                                                 |
| --------------------- | --------------------------------------------- | ---------------------------------------------------------------------------------------------------- |
| `AbsDbExecutor`       | `act_db_core/services/abs_db_executor.hpp`    | Engine-agnostic query executor interface                                                             |
| `AbsDbManager`        | `act_db_core/services/abs_db_manager.hpp`     | Engine-agnostic base: migration runner, script executor                                              |
| `DbProtectService<T>` | `act_db_core/services/db_protect_service.hpp` | Template query wrapper with error handling and optional transactions. Default `T` = `AbsDbExecutor`. |
| `DbTransaction`       | `act_db_core/db_transaction.hpp`              | RAII transaction helper (auto-rollback on destruction)                                               |
| `DbCoreConstants`     | `act_db_core/db_core_constants.hpp`           | SQL transaction statement constants                                                                  |
| `db_log_helper.hpp`   | `act_db_core/db_log_helper.hpp`               | Convenience macros for early-return error guards                                                     |

## Usage

### 1. Implement `AbsDbExecutor` for your database engine

`AbsDbExecutor` is the lowest-level interface. Concrete backends may implement it to provide
actual query execution. Better to implement `AbsDbManager` (next step) which inherits from
`AbsDbExecutor` and provides migration management and logging integration out of the box.

```cpp
// my_engine_executor.hpp
#include "act_db_core/services/abs_db_executor.hpp"

class MyEngineExecutor : public act::db_core::AbsDbExecutor
{
  public:
    [[nodiscard]] bool isOpened() const override;
    bool exec(const std::string &sql) override;
    bool runScript(const std::filesystem::path &scriptPath) override;
    std::optional<int> execAndGetInt(const std::string &sql) override;
};
```

---

### 2. Subclass `AbsDbManager` to own the database lifecycle

`AbsDbManager` is the base class for all concrete database managers. It handles opening the
database, running migration scripts in order, and logging. You must implement several pure
virtual methods that are engine-specific.

```cpp
// my_database.hpp
#include "act_db_core/services/abs_db_manager.hpp"

class MyDatabase : public act::db_core::AbsDbManager
{
  public:
    explicit MyDatabase(std::filesystem::path migrationDir,
                        const act::logger::LoggerManager &loggerManager);
    ~MyDatabase() override;

    bool init() override;

    // Pure virtuals from AbsDbManager — engine-specific implementations
    [[nodiscard]] int getMigrationVersion() const override;
    bool setMigrationVersion(int version) override;
    bool defrag() override;
    bool sync() override;
    bool setBusyTimeout(int busyTimeoutMs) override;

  protected:
    bool openImpl() override; // actually open the underlying database file/connection
};
```

```cpp
// my_database.cpp
#include "my_database.hpp"

MyDatabase::MyDatabase(std::filesystem::path migrationDir,
                       const act::logger::LoggerManager &loggerManager)
    : AbsDbManager("my-db", std::move(migrationDir), loggerManager)
{
}

bool MyDatabase::init()
{
    if (!open(true))           // opens the connection and runs pending migrations
        return false;
    if (!setBusyTimeout(1000))
        return false;
    return true;
}

bool MyDatabase::openImpl()
{
    // Engine-specific: open file, establish connection, etc.
    return true;
}

int MyDatabase::getMigrationVersion() const
{
    // Engine-specific: query the stored schema version (e.g. PRAGMA user_version)
    return 0;
}

bool MyDatabase::setMigrationVersion(int version)
{
    // Engine-specific: persist the new schema version
    return true;
}
```

---

### 3. Use `DbProtectService` to guard queries

`DbProtectService<DbExecutor>` is a template that wraps a query lambda with exception catching,
error logging, and optional automatic transaction management. The default template argument is
`AbsDbExecutor`, which accepts any executor. Specialize it with a concrete type to receive a
typed reference inside the lambda — useful when the concrete executor exposes additional methods
(e.g. a raw database handle).

- `protectQuery(name, lambda)` — lambda receives `DbExecutor &`; returns `bool`.
- `protectQueryWithResult<T>(name, lambda)` — lambda receives `DbExecutor &`; returns
  `std::optional<T>` (`std::nullopt` on any exception or when the lambda returns `std::nullopt`).
- `accessDb()` — returns `DbExecutor &` (mutable access to the wrapped executor).
- `getDb()` — returns `const DbExecutor &`.

Both query overloads wrap the call in a transaction by default (pass `false` as third argument to
opt out).

```cpp
#include "act_db_core/services/db_protect_service.hpp"

// Default instantiation — DbExecutor = AbsDbExecutor
act::db_core::DbProtectService<> protect(m_db, *m_logger);

// Typed instantiation — lambdas receive MyConcreteExecutor & directly
act::db_core::DbProtectService<MyConcreteExecutor> typedProtect(m_concreteDb, *m_logger);

// Simple write query (returns bool)
bool ok = protect.protectQuery(
    [&row](act::db_core::AbsDbExecutor &db) {
        return db.exec("INSERT INTO my_table VALUES (1, 'hello')");
    },
    "insert-my-row");

// Read query returning a value (returns std::optional<T>)
std::optional<int> version = protect.protectQueryWithResult<int>(
    [](act::db_core::AbsDbExecutor &db) -> std::optional<int> {
        return db.execAndGetInt("PRAGMA user_version");
    },
    "get-version",
    false); // no transaction needed for a read

// Direct access to the underlying executor
MyConcreteExecutor &executor = typedProtect.accessDb();
```

---

### 4. Use `DbTransaction` for manual transaction control

`DbTransaction` is a RAII helper. If `commit()` is never called before the object goes out of
scope, the destructor calls `rollback()` automatically.

```cpp
#include "act_db_core/db_transaction.hpp"

act::db_core::DbTransaction tx(m_db, *m_logger);

if (!tx.begin())
    return false;

if (!m_db.exec("INSERT INTO my_table VALUES (1, 'hello')"))
{
    tx.rollback(); // explicit rollback; destructor would also do it
    return false;
}

return tx.commit();
```

---

### 5. Use `db_log_helper.hpp` macros for early-return guards

These macros provide concise checks at the top of query methods. They log an error and return
immediately if the database is not open or if a statement throws.

| Macro                            | Returns on error |
| -------------------------------- | ---------------- |
| `FALSE_IF_NO_DB(caller, log)`    | `false`          |
| `EMPTY_IF_NO_DB(caller, log)`    | `{}`             |
| `ZERO_IF_NO_DB(caller, log)`     | `0`              |
| `FALSE_IF_THROW(name, log, cmd)` | `false`          |
| `EMPTY_IF_THROW(name, log, cmd)` | `{}`             |
| `ZERO_IF_THROW(name, log, cmd)`  | `0`              |

```cpp
#include "act_db_core/db_log_helper.hpp"

bool MyService::insertRow(const MyRow &row)
{
    FALSE_IF_NO_DB(insertRow, m_logger); // returns false if db is not open

    FALSE_IF_THROW(
        "insertRow",
        m_logger,
        {
            // engine-specific statement execution
        });

    return true;
}
```

---

### 6. Wire migration scripts

Migration scripts must be named `<slug>-db-v<N>-to-v<N+1>.sql`
(e.g. `my-db-db-v0-to-v1.sql`, `my-db-db-v1-to-v2.sql`) and placed in the directory passed as
`migrationDataDir`. The manager runs them in version order when `open(true)` is called.

---

## CMake integration

```cmake
target_link_libraries(my_target PRIVATE act_db_core)
```
