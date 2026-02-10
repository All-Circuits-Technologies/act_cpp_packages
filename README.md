<!-- SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com> -->
<!-- SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1 -->

# ACT C++ Libraries

A collection of modular, reusable C++ libraries for embedded Linux systems and general-purpose
applications developed by All-Circuits Technologies.

## Overview

This repository provides a set of independent C++ libraries covering common functionality needed
across multiple projects:

- **Logging infrastructure** with flexible output backends
- **System utilities** for multi-process synchronization
- **Database management** with SQLite integration
- **Linux I/O control** for GPIO and LED management
- **Common utilities** for threading, file operations, and string manipulation

Each library is self-contained with minimal dependencies, allowing you to include only what you
need in your projects.

## Libraries

### [`act_logger`](lib/act_logger)

Logging infrastructure providing logger managers, external loggers, console output, and helper
utilities for consistent logging across modules.

**Features:**

- Multi-logger support with different output backends
- Configurable log levels and formatting
- Thread-safe logging operations
- Integration with external logging systems

### [`act_misc`](lib/act_misc)

Base utility library providing common helpers, threading utilities, file operations, string
manipulation, and other miscellaneous functionalities.

**Features:**

- Threading utilities (mutexed, reusable threads)
- File and CSV utilities
- String and date/time manipulation
- JSON utilities (Crow and nlohmann JSON support)
- Event callback systems
- Action delayer and restartable timers

### [`act_system`](lib/act_system)

System-level utilities library providing multi-process synchronization primitives using flock-based
locking.

**Features:**

- Critical section management across processes
- RAII-style critical section guards
- File-lock based synchronization

### [`act_sqlite`](lib/act_sqlite)

SQLite database management library providing database abstraction layer, connection management, and
logging integration.

**Features:**

- Database connection management
- Query execution helpers
- Logging integration for database operations
- Transaction support

### [`act_linux_io`](lib/act_linux_io)

Linux-specific I/O library for GPIO control and LED management via sysfs and libgpiod.

**Features:**

- GPIO control using libgpiod
- LED management via sysfs
- LED trigger configurations (oneshot, pattern, simple)
- Hardware abstraction for Linux I/O devices

## Requirements

- **C++ Standard:** C++17 or later
- **CMake:** Version 3.23 or later
- **Compiler:** GCC 9+ or Clang 10+
- **OS:** Linux (some libraries are Linux-specific)

### Dependencies

Each library has its own dependencies. Refer to individual library READMEs for specific requirements.

Common dependencies include:

- libgpiod (for `act_linux_io`)
- SQLite3 (for `act_sqlite`)
- nlohmann-json (for JSON utilities in `act_misc`)

## Building

### Build All Libraries

```bash
mkdir build
cd build
cmake ..
make
```

### Build Options

- `BUILD_DEMOS`: Build demo applications (default: OFF)
- `BUILD_TESTS`: Build tests (default: OFF)

Example:

```bash
cmake -DBUILD_DEMOS=ON -DBUILD_TESTS=ON ..
make
```

### Use Individual Libraries

Each library can be integrated into your CMake project using `add_subdirectory()`:

```cmake
add_subdirectory(path/to/act_cpp_packages/lib/act_logger)
target_link_libraries(your_target PRIVATE act_logger)
```

## Development

### Development Container

A development container configuration is provided in [`.devcontainer/`](.devcontainer/) for VSCode
with all required tools and dependencies pre-installed.

### Code Style

- Code formatting: `.clang-format`
- Static analysis: `.clang-tidy`
- Markdown linting: `.markdownlint.yaml`

## License

This project is licensed under the AllCircuits ACT License 1.1. See
[LICENSES/LicenseRef-ALLCircuits-ACT-1.1.txt](LICENSES/LicenseRef-ALLCircuits-ACT-1.1.txt) for
details.

## Contributing

This is an internal All-Circuits Technologies repository. For contribution guidelines, please
contact the development team.

## Maintainers

- Théo Magne <theo.magne@allcircuits.com>
- All-Circuits Technologies team
