<!-- SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com> -->

<!-- SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1 -->

# act_threading

Threading utilities for concurrent programming in ACT C++ modules.

## Description

This module provides thread management utilities, synchronization primitives, and abstractions for
concurrent programming.

## Contents

- **Mutexed:** Template wrapper for thread-safe access to data
- **ReusableThread:** Thread abstraction that can be restarted
- **Types:** Threading-related types and results

## Dependencies

- act_foundation
- act_logger

## Usage

```cpp
#include "act_threading/mutexed.hpp"
#include "act_threading/reusable_thread.hpp"
```

## License

LicenseRef-ALLCircuits-ACT-1.1
