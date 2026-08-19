# BitFlags

This project is part of my embedded-systems learning roadmap and focuses on understanding how multiple boolean states can be efficiently represented inside a single `uint32_t`.

## Purpose

Embedded systems frequently use individual bits to represent:

* Hardware status
* Configuration options
* Protocol fields
* Sensor status
* Flight-controller state
* Error and warning conditions
* Register values

Instead of storing each state as a separate `bool`, multiple states can be stored inside a single integer.

For example:

```text
uint32_t flags

00000000 00000000 00000000 00100101
                                 ││ │
                                 ││ └── ARMED
                                 │└──── BATTERY_LOW
                                 └───── MOTORS_ENABLED
```

Each bit represents an independent state.

---

## Project Goals

The goal of this project is to practice:

* Binary representation
* Bitwise operators
* Bit shifting
* Bit masks
* Setting individual bits
* Clearing individual bits
* Checking individual bits
* Working with `uint32_t`
* Writing a small reusable C library
* Writing unit-style tests
* Organizing a C project into headers, source files, tests, and examples

---

## Status Flags

The project defines the following flight-controller flags:

| Flag                  | Bit | Meaning                        |
| --------------------- | --: | ------------------------------ |
| `FLAG_ARMED`          |   0 | Vehicle is armed               |
| `FLAG_GPS_AVAILABLE`  |   1 | GPS is available               |
| `FLAG_BATTERY_LOW`    |   2 | Battery level is low           |
| `FLAG_GPS_HOME_SET`   |   3 | GPS home position has been set |
| `FLAG_FAILSAFE`       |   4 | Failsafe mode is active        |
| `FLAG_MOTORS_ENABLED` |   5 | Motors are enabled             |

The flags are defined as individual bit masks:

```c
#define FLAG_ARMED          (1u << 0)
#define FLAG_GPS_AVAILABLE  (1u << 1)
#define FLAG_BATTERY_LOW    (1u << 2)
#define FLAG_GPS_HOME_SET   (1u << 3)
#define FLAG_FAILSAFE       (1u << 4)
#define FLAG_MOTORS_ENABLED (1u << 5)
```

This means:

```text
FLAG_ARMED
00000000 00000000 00000000 00000001

FLAG_GPS_AVAILABLE
00000000 00000000 00000000 00000010

FLAG_BATTERY_LOW
00000000 00000000 00000000 00000100

FLAG_GPS_HOME_SET
00000000 00000000 00000000 00001000

FLAG_FAILSAFE
00000000 00000000 00000000 00010000

FLAG_MOTORS_ENABLED
00000000 00000000 00000000 00100000
```

---

## API

The library provides three operations.

### Set a flag

```c
void set_flag(uint32_t *flags, uint32_t flag);
```

Sets the specified bit to `1`.

Example:

```c
uint32_t flags = 0;

set_flag(&flags, FLAG_ARMED);
```

Result:

```text
00000000 00000000 00000000 00000001
```

---

### Clear a flag

```c
void clear_flag(uint32_t *flags, uint32_t flag);
```

Sets the specified bit to `0` without modifying the other flags.

Example:

```c
clear_flag(&flags, FLAG_ARMED);
```

---

### Check a flag

```c
bool is_flag_set(uint32_t flags, uint32_t flag);
```

Returns `true` if the specified flag is set.

Example:

```c
if (is_flag_set(flags, FLAG_ARMED))
{
    printf("Vehicle is armed\n");
}
```

---

## Bitwise Operations

The core of the library is based on three operations.

### Set

```c
flags |= flag;
```

Bitwise OR sets a bit to `1`.

```text
00000001
   |
00000100
--------
00000101
```

---

### Clear

```c
flags &= ~flag;
```

The `~` operator inverts the mask and `&` clears the selected bit.

```text
00000111
&
11111011
--------
00000011
```

---

### Check

```c
flags & flag
```

If the result is non-zero, the bit is set.

```text
00000111
&
00000100
--------
00000100
```

Therefore:

```c
(flags & flag) != 0
```

returns `true`.

---

## Example

Suppose the flight controller currently has:

```text
ARMED = true
GPS_AVAILABLE = true
BATTERY_LOW = false
GPS_HOME_SET = true
FAILSAFE = false
MOTORS_ENABLED = true
```

The resulting flags value would be:

```text
00000000 00000000 00000000 00101011
```

The individual bits represent:

```text
bit 5 → MOTORS_ENABLED
bit 3 → GPS_HOME_SET
bit 1 → GPS_AVAILABLE
bit 0 → ARMED
```

All other bits are `0`.