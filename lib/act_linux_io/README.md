<!-- SPDX-FileCopyrightText: 2026 Théo Magne <theo.magne@allcircuits.com> -->

<!-- SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1 -->

# act_linux_io

Linux-specific I/O library for GPIO control and LED management via sysfs and libgpiod.

## Dependencies

- act_files
- act_logger
- libgpiod v2.x (libgpiodcxx)

## Debian Packages

```bash
# Required: libgpiod v2.0 or later
sudo apt install libgpiod-dev

# Note: Many distributions ship libgpiod v1.x which is incompatible.
# This module requires libgpiod v2.x API. If not available, this module
# will be automatically skipped during build.
```

## Features

- **GPIO:** Linux GPIO control using libgpiod v2 API
- **LED:** LED control via sysfs
  - Manual ON/OFF control
  - Trigger-based control
    - oneshot
    - pattern
    - triggers without settings (panic, etc)
