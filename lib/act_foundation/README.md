<!-- SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com> -->

<!-- SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1 -->

# act_foundation

Foundational types and design patterns used across all ACT C++ modules.

## Description

This module provides core base classes, constants, and common design patterns that are used
throughout the ACT C++ package ecosystem. It has no dependencies on other ACT modules and serves as
the foundation layer.

## Contents

- **Base Classes:** NotCopiableNotMovable, AbsManager
- **Constants:** Software-wide constants and macros (def_soft.hpp)
- **Patterns:** Singleton pattern, Finally (RAII guard)

## Dependencies

None - this is a foundational module.

## Usage

```cpp
#include <act_foundation/not_copiable_not_movable.hpp>
#include <act_foundation/abs_manager.hpp>
#include <act_foundation/constants/def_soft.hpp>
```

## License

LicenseRef-ALLCircuits-ACT-1.1
