# act_threading

Threading utilities for concurrent programming in ACT C++ modules.

## Description

This module provides thread management utilities, synchronization primitives, and abstractions for concurrent programming.

## Contents

- **ReusableThread:** Thread abstraction that can be restarted
- **Mutexed:** Template wrapper for thread-safe access to data
- **Types:** Threading-related types and results

## Dependencies

- act_foundation (base classes)
- act_logger (logging interface)

## Usage

```cpp
#include "act_threading/reusable_thread.hpp"
#include "act_threading/mutexed.hpp"
```

## License

LicenseRef-ALLCircuits-ACT-1.1
