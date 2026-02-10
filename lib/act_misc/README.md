<!-- SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com> -->
<!-- SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1 -->

# act_misc

Base utility library providing common helpers, threading utilities, file operations, string manipulation, and other miscellaneous functionalities.

## Dependencies

- **Internal:** None (base module)
- **External:** `pthread` (via CMake Threads)

## Debian Packages

```bash
# No additional packages required beyond build-essential
```

## Features

- **Constants:** Software-wide constants (def_soft.hpp)
- **Events:** Callbacks register, keyed callbacks register
- **Helpers:** Action delayer, logger stream, restartable timer, finally (RAII guard)
- **Managers:** Abstract manager, singleton pattern, system manager
- **Models:** Abstract logger, external file handling
- **Threading:** Mutexed wrapper, reusable thread
- **Types:** Logs level, reusable thread result
- **Utilities:** CSV, date/time, file, string, vector string utilities
