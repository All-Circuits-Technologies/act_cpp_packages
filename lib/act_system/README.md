# act_system

System-level utilities library providing multi-process synchronization primitives using flock-based locking.

## Dependencies

- **Internal:** act_misc
- **External:** None (uses POSIX flock)

## Debian Packages

```bash
# No additional packages required beyond build-essential
```

## Features

- **System Critical Section:** Multi-process mutex using file locks (flock)
- **System Critical Section Guard:** RAII guard for critical sections
