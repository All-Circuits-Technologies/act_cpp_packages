# act_linux_io

Linux-specific I/O library for GPIO control and LED management via sysfs and libgpiod.

## Dependencies

- **Internal:** act_misc, act_logger
- **External:** libgpiod v2.x (libgpiodcxx)

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
  - Abstract LED trigger configuration
  - Oneshot trigger configuration
  - Pattern trigger configuration
  - Simple (on/off) trigger configuration
