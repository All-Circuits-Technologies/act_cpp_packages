<!-- SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com> -->

<!-- SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1 -->

# act_sqlite

SQLite database management library providing database abstraction layer, connection management, and
logging integration.

## Dependencies

- act_foundation
- act_logger
- act_system
- SQLiteCpp (libsqlitecpp-dev)

## Debian Packages

```bash
sudo apt install libsqlitecpp-dev
```

## Features

- **Abstract DB Manager:** Base class for database managers with critical section support
- **DB Log Helper:** Logging utilities for database operations
- **SQLite DB Manager:** SQLite-specific database manager implementation
