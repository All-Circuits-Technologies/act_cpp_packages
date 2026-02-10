<!-- SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com> -->
<!-- SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1 -->

# act_time

Date, time, and timing utilities for ACT C++ modules.

## Description

This module provides utilities for time handling, delays, timers, and scheduling operations.

## Contents

- **DateTimeUtil:** Date and time formatting and parsing
- **RestartableTimer:** Timer that can be restarted dynamically
- **ActionDelayer:** Delays action execution with configurable bounds

## Dependencies

- act_foundation (base classes)
- act_logger (logging interface)
- act_threading (for timer threads)

## Usage

```cpp
#include "act_time/date_time_util.hpp"
#include "act_time/restartable_timer.hpp"
#include "act_time/action_delayer.hpp"
```

## License

LicenseRef-ALLCircuits-ACT-1.1
