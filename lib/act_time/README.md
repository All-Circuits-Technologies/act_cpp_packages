<!-- SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com> -->

<!-- SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1 -->

# act_time

Date, time, and timing utilities for ACT C++ modules.

## Description

This module provides utilities for time handling, delays, timers, and scheduling operations.

## Contents

- **ActionDelayer:** Delays action execution with configurable bounds
- **DateTimeUtil:** Date and time formatting and parsing
- **RestartableTimer:** Timer that can be restarted dynamically

## Dependencies

- act_foundation
- act_logger
- act_threading

## Usage

```cpp
#include <act_time/action_delayer.hpp>
#include <act_time/date_time_util.hpp>
#include <act_time/restartable_timer.hpp>
```

## License

LicenseRef-ALLCircuits-ACT-1.1
