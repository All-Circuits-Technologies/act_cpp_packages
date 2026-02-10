<!-- SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com> -->
<!-- SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1 -->

# act_files

File system operations and file management utilities for ACT C++ modules.

## Description

This module provides utilities for file I/O operations, path manipulation, and file management.

## Contents

- **FileUtil:** File system utilities (read, write, exists, etc.)
- **ExtFile:** Extended file abstraction with automatic cleanup

## Dependencies

- act_foundation (base classes)
- act_logger (logging interface)

## Usage

```cpp
#include "act_files/file_util.hpp"
#include "act_files/ext_file.hpp"
```

## License

LicenseRef-ALLCircuits-ACT-1.1
