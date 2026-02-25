<!-- SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com> -->

<!-- SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1 -->

# act_system

System-level utilities library providing multi-process synchronization primitives using flock-based
locking.

## Dependencies

- act_foundation
- act_logger
- act_text
- act_threading

## Features

- **System Critical Section:** Multi-process mutex using file locks (flock)
- **System Manager:** System reboot and command execution utilities
