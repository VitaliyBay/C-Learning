# MockFC-Companion — Learning Tasks (fix-up before Day 11)

These tasks are for you to do by hand. Each one is small (about 15–45 minutes), explains the concept behind it, and ends with a clear "done when" check. Work in order: later tasks assume earlier ones are finished.

**Rules for yourself:**
- Write the test first when a task says "add a test". Watch it fail, then fix the code.
- Keep the build clean with `-Wall -Wextra -Wpedantic -std=c11`. Treat every warning as a question to answer.
- Commit after each task with a message that names the task (for example `Task 04: remove duplicate type definitions`).

Status legend: `[ ]` not done, `[x]` done.

---

## Phase 1 — Build and small validation fixes

- [X] **Task 01 — Fix the `mockFC/tests` build**
- [X] **Task 02 — Longitude range check**
- [X] **Task 03 — Yaw range is half-open `[0, 360)`**

## Phase 2 — Data model cleanup

- [ ] **Task 04 — Remove duplicate type definitions**
- [ ] **Task 05 — Fix names and typos in the data model**
- [ ] **Task 06 — Initialize mock sensors to the handbook values**

## Phase 3 — Attitude codec correctness

- [ ] **Task 07 — Stop losing decimals when decoding**
- [ ] **Task 08 — Reject out-of-range values when encoding**
- [ ] **Task 09 — Make decoding all-or-nothing**
- [ ] **Task 10 — Decide and enforce the attitude byte order**

## Phase 4 — Scenario timeline

- [ ] **Task 11 — Make battery drop depend on time, not on previous value**
- [ ] **Task 12 — Climb ramp from 5 s to 15 s**
- [ ] **Task 13 — Roll disturbance and recovery ramps**
- [ ] **Task 14 — GPS satellite degradation schedule**

## Phase 5 — Documentation

- [ ] **Task 15 — Complete the MiniMSP response specification**

---

## Phase 1 — Build and small validation fixes

### Task 01 — Fix the `mockFC/tests` build

**Goal:** `make -C mockFC/tests run` builds and runs without errors.

**What to do**
1. Open `mockFC/tests/Makefile`. The `TARGET = test_clock` rule links `test_clock.o` **and** `test_scenario.o`. Each test file has its own `main()`, so the linker fails with `multiple definition of 'main'`.
2. Change the `test_clock` target so it links only `test_clock.c` with the source files it needs (`clock.c`).
3. Make sure `make run` builds `test_clock` and `make scenario` builds `test_scenario`. Both must run and print their "passed" message.
4. Make `make clean` remove every object file and executable you create.

**Explanation:** Every executable in C has exactly one `main()`. Test files are separate programs, so each one needs its own target that links only what it uses. The linker is what reports "multiple definition"; the compiler accepted each file on its own. Learning to read linker errors is a core embedded skill, because on a microcontroller you often can't run a debugger and the link step is where many problems show up.

**Done when:** `make -C mockFC/tests run` and `make -C mockFC/tests scenario` both succeed, and `make clean` leaves no `.o` or `.exe` files behind.

---

### Task 02 — Longitude range check

**Goal:** `gps_coordinates_valid` rejects longitudes outside −180…180.

**What to do**
1. Open `common/validations.c` and read `gps_coordinates_valid`. Find the branch where `longitude_deg > 180` returns `true`. That is wrong.
2. Rewrite the function so it returns `true` only when both latitude and longitude are inside their ranges. One `return` statement with one condition is enough.
3. Add tests in `tests/test_validations.c` for: longitude `181` (invalid), `-180.5` (invalid), `180` (valid), `-180` (valid), and latitude `90.5` (invalid).

**Explanation:** A range check has two boundaries, and each one has to be correct. Writing the valid condition as one expression (`lat >= -90 && lat <= 90 && lon >= -180 && lon <= 180`) is easier to verify than several `if` statements that each return early. When you add a return path, check every case it covers, not only the one you were thinking about.

**Done when:** every longitude case in the list above gives the expected result, and the test program still passes.

---

### Task 03 — Yaw range is half-open `[0, 360)`

**Goal:** `attitude_valid` accepts yaw values from 0 up to but **not** including 360.

**What to do**
1. In `common/validations.c`, `attitude_valid` currently accepts `yaw_deg == 360`.
2. Change the check so yaw `< 0` or `>= 360` is rejected.
3. Add tests: yaw `0` (valid), `359.9` (valid), `360` (invalid), `-0.1` (invalid).

**Explanation:** Mathematical intervals come in two forms. A closed interval `[0, 360]` includes both ends. A half-open interval `[0, 360)` includes 0 and excludes 360. A compass heading of 360 is the same direction as 0, so the code should store only one of them. Choosing the right kind of boundary is a decision you should make on purpose and document in a comment.

**Done when:** the four test cases above pass.

---

## Phase 2 — Data model cleanup

### Task 04 — Remove duplicate type definitions

**Goal:** Each type is defined in exactly one header.

**Problem:** `common/types.h` and `mockFC/src/sensors.h` both define `GpsFixType`, `FlightMode`, `Attitude`, `GpsData`, `BatteryData`, and `FlightStatus`. Including both in the same file fails with `redeclaration of enumerator 'GPS_FIX_NONE'`. The Day 11 handler will need both, so this must be fixed first.

**What to do**
1. Keep `common/types.h` as the single place for these types.
2. Delete the duplicate definitions from `mockFC/src/sensors.h`. Make it `#include "types.h"` instead. Keep `SensorData` in `sensors.h`, because it is mock-only.
3. Build a tiny file that includes both `types.h` and `sensors.h`. It must compile.

**Explanation:** Include guards (`#ifndef TYPES_H`) only stop a header from being read twice *in one file*. They do not stop two *different* headers from defining the same type. Every type should have one source of truth. If two copies drift apart, the compiler may accept code that is wrong. This is also why the "one definition rule" exists: a struct or enum may be defined only once per program.

**Done when:** `#include "types.h"` and `#include "sensors.h"` in the same file compiles with no errors, and all existing tests still pass.

---

### Task 05 — Fix names and typos in the data model

**Goal:** Field names match their units and meaning. The handbook lists the expected names.

**What to do**
1. In `common/types.h`:
   - `Gyroscope.z_dpf` → `z_dps` (degrees per second, not "dpf").
   - `Accelerometer` fields should be `x_g`, `y_g`, `z_g` (in g), not `_dps`.
   - `GpsData.satelites` → `satellites`.
   - `DroneTelemetry.altitude` (which is an `Attitude`) → `attitude`.
2. Fix every place that used the old names. The compiler will list them for you.
3. Compare `DroneTelemetry` with the handbook's data model. Note what is still missing (`ImuData`, `altitude_relative_m`, `sample_time_ms`). **Do not add them yet.** Write the missing items in a comment at the top of `types.h` as a TODO list.

**Explanation:** Good names carry units. `voltage_v` tells you the unit without reading the docs; `z_dpf` does not. In embedded code, a unit mistake (degrees vs. radians, volts vs. millivolts) is a common and dangerous bug. Let the compiler find all the call sites when you rename a field: change the header first, then fix each error it reports.

**Done when:** the build is clean with `-Wall -Wextra -Wpedantic`, and `grep` finds none of the old names in the project.

---

### Task 06 — Initialize mock sensors to the handbook values

**Goal:** `sensors_init` sets the values the handbook specifies.

**What to do**
1. Open `mockFC/src/sensors.c` and compare each value with the "Initial values" table in the handbook (Quick reference → Data model → Initial values). Current differences:
   - GPS: 10 satellites, 41.3851 / 2.1734, 100 m → should be 12 satellites, 41.3874 / 2.1686, 35 m.
   - Battery: 16.8 V → should be 24.60 V.
   - Accelerometer Z: 0 g → should be 1 g (a level drone at rest reads gravity on Z).
2. Replace the number literals with named `#define` or `const` values at the top of the file (for example `INITIAL_BATTERY_V`). This makes the handbook values easy to find.
3. Add a test that calls `sensors_init` and checks every field.

**Explanation:** Initialization is where you decide what a simulation starts from. Every field should be set on purpose. A "magic number" in the middle of a function is hard to review; a named constant tells the reader what the number means. Also note that an accelerometer reads gravity, so a level, stationary drone reads (0, 0, 1 g), not zeros.

**Done when:** the new test passes and each field matches the handbook table.

---

## Phase 3 — Attitude codec correctness

### Task 07 — Stop losing decimals when decoding

**Goal:** `decode_attitude` returns `12.4` for the wire value `124`, not `12.0`.

**Problem:** In `common/telemetry_codec.c`, the decode code does `roundf(yaw_value / 10)`. `yaw_value` is an `int16_t`, and `10` is an integer, so the division is **integer division** and the fraction is thrown away before `roundf` runs. `roundf` also rounds to whole degrees, which is wrong on the decode side.

**What to do**
1. Change each decode line to divide by a float: `value->yaw_deg = yaw_value / 10.0f;` (do the same for pitch and roll). Remove `roundf` from the decode side. Rounding belongs on the encode side, because that is where the precision is lost.
2. Add a test that decodes the bytes for `(12.4, -3.2, 91.0)`. Those bytes are `7C 00 E0 FF 8E 03`, but check the byte order you use. Use a tolerance of `0.05` (for example `fabsf(decoded - expected) < 0.05f`).
3. Keep the existing whole-number tests. They must still pass.

**Explanation:** In C, the type of the operands decides the arithmetic. `7 / 2` is `3`, but `7 / 2.0f` is `3.5`. This is one of the most common C bugs. Also notice that the existing tests only used whole degrees (11.0, 12.0, 13.0), which hid the problem. A good test uses values that could expose the bug, such as values with decimals and negative values.

**Done when:** the fractional decode test passes within 0.05°, and the old tests still pass.

---

### Task 08 — Reject out-of-range values when encoding

**Goal:** `encode_attitude` returns `false` for values it cannot represent, instead of producing garbage bytes.

**Problem:** `encode_attitude` converts a float to `int16_t` with a plain cast. If the float is out of range, that conversion is **undefined behavior** in C, not just a wrap-around.

**What to do**
1. At the start of `encode_attitude`, call `attitude_valid(value)` (from `common/validations.h`). Return `false` if it fails.
2. Add tests for: roll `200.0` (invalid), pitch `-190.0` (invalid), yaw `360.0` (invalid), and a valid value at the edge such as roll `180.0`.
3. Check that a valid value still gives the same bytes as before.

**Explanation:** Converting a float to an integer that is too big for the target type is undefined behavior. The compiler may do anything, and the result can differ between compilers and optimization levels. The fix is to check the range *before* the cast. This is a general rule: validate at the boundary, before you convert or store data. Note the difference between "reject" (return an error) and "clamp" (silently change the value). For telemetry, reject is safer.

**Done when:** all the out-of-range cases return `false`, and valid values still encode to the same bytes.

---

### Task 09 — Make decoding all-or-nothing

**Goal:** If any part of the attitude payload is invalid, the caller's `Attitude` is not changed at all.

**Problem:** `decode_attitude` writes `value->yaw_deg` before it checks pitch and roll. If pitch fails, the caller already has a new yaw and an old pitch and roll: a half-updated state.

**What to do**
1. Decode all three values into local variables first.
2. Only if all three decodes succeed, assign them to `*value` at the same time.
3. Add a test: fill `Attitude` with known values, then call `decode_attitude` with a buffer that is too short (or otherwise bad). Check that the struct still contains the known values.

**Explanation:** An output parameter that is written in pieces can leave the program in an inconsistent state. This is called a "partial update", and it causes hard-to-find bugs in control software: for example, a new heading combined with an old attitude. The usual pattern is "decode into a temporary, commit on success". You will use this pattern again when you build the companion's telemetry state.

**Done when:** the partial-update test passes.

---

### Task 10 — Decide and enforce the attitude byte order

**Goal:** The codec writes attitude bytes in the order the protocol document says.

**Problem:** `docs/protocol.md` and the handbook say the attitude payload is **roll, pitch, yaw**. `encode_attitude` writes **yaw, pitch, roll**, and the tests assert that order. The code and the contract disagree.

**What to do**
1. Read the protocol contract in `docs/protocol.md` and the handbook's MiniMSP section. Decide which one is the contract. Write one sentence on your choice and why.
2. If the document is the contract: change `encode_attitude` and `decode_attitude` to roll, pitch, yaw, and update the test vectors in `tests/test_telemetry_codec.c`.
3. If the code is the contract: update `docs/protocol.md` to say yaw, pitch, roll, and explain why in the document.
4. Either way, the test byte vectors must match the document exactly.

**Explanation:** A protocol has two sides, and both must agree. The **specification** (the document) defines what goes on the wire. The **implementation** (the code) must follow the specification. When they differ, the bug is in one of them, and you must decide which is correct before you change anything. In real embedded projects this is a daily question, and the answer should be written down, not left in someone's head.

**Done when:** the document, the code, and the test vectors all state the same byte order.

---

## Phase 4 — Scenario timeline

Read the "Timeline" and "Exact checkpoints" tabs of the handbook's Mock scenario reference before you start Phase 4. Every task below must match those checkpoints exactly.

### Task 11 — Make battery drop depend on time, not on previous value

**Goal:** At any simulated time, the battery voltage is a function of time alone.

**Problem:** In `mockFC/src/scenario.c`, the code does `voltage = voltage - 0.2 * drops`. The scenario runs every 10 ms, so the voltage is reduced again on every tick. In a quick check, starting at 24.60 V and running to 45.99 s gave 4.60 V.

**What to do**
1. Store the starting voltage as a constant (you did this in Task 06).
2. Compute the voltage from the timeline: `voltage = BATTERY_START_V - 0.2f * drops`, where `drops` is computed from the current time.
3. Add a test that runs the scenario every 10 ms up to 46000 ms, and checks 24.60 V before 45000 ms and 24.40 V at 46000 ms. Add 55000 ms (22.60 V) and 60000 ms (21.60 V).

**Explanation:** A function is *idempotent* when calling it many times gives the same result as calling it once. Your scenario function is called every tick, so it must be idempotent. The safe pattern in simulations and control code is: derive state from time, not from the previous state. Accumulating state ("subtract a bit each call") drifts and makes the test results depend on how often you call the function.

**Done when:** all five checkpoints pass, and calling the scenario every tick gives the same result as calling it once.

---

### Task 12 — Climb ramp from 5 s to 15 s

**Goal:** Altitude rises by 0.1 m every 100 ms from 5000 ms and reaches 10.0 m at 15000 ms.

**What to do**
1. In `scenario_updates`, replace the single step at 15000 ms with a ramp for `5000 ≤ now < 15000`.
2. Compute the altitude from elapsed time: `steps = (now - 5000) / 100` (integer division is correct here), then `altitude = steps * 0.1f`. Hold at 10.0 m from 15000 ms.
3. Test: 5000 ms → 0.0 m, 10000 ms → 5.0 m, 14900 ms → 9.9 m, 15000 ms → 10.0 m.

**Explanation:** Adding 0.1 on each tick looks simpler, but floating-point rounding accumulates and the value at 15000 ms may not be exactly 10.0. Computing the value from a whole number of steps is exact in the way that matters here. Integer division (`/` on two integers) is useful exactly when you want to discard the remainder, like counting completed 100 ms steps.

**Done when:** all four tests pass.

---

### Task 13 — Roll disturbance and recovery ramps

**Goal:** Roll goes from 0° to 20° between 25000 and 26000 ms, holds until 29000 ms, then returns to 0° by 30000 ms.

**What to do**
1. Use the same step-from-time approach as Task 12. Roll rises by 2° every 100 ms from 25000 ms.
2. Hold at 20° from 26000 ms to 29000 ms.
3. Fall back by 2° every 100 ms from 29000 ms, and stop at 0° at 30000 ms.
4. Test the handbook checkpoints: 25100 ms → 2°, 26000 ms → 20°, 29100 ms → 18°, 30000 ms → 0°.

**Explanation:** This is a piecewise function: a different formula applies in each time window. Write each window as its own `if` with both bounds, and make sure windows do not overlap. Test the boundaries: 26000 ms is the end of the rise and the start of the hold, so it must give exactly 20°.

**Done when:** all four checkpoints pass, and no two windows overlap.

---

### Task 14 — GPS satellite degradation schedule

**Goal:** Satellites drop from 12 to 3 between 35000 and 37500 ms, and the fix is lost at 37500 ms.

**What to do**
1. The handbook schedule: 35000 ms → 12, 35500 ms → 10, 36000 ms → 8, 36500 ms → 6, 37000 ms → 4, 37500 ms → 3. Each step lasts 500 ms.
2. Set `fix_type = GPS_FIX_NONE` at 37500 ms (keep 3D before that).
3. Test each step, and test 35500 ms → 10 satellites.

**Explanation:** This is a lookup table in time. You can write it as an `if` chain, or as an array of `{time, value}` pairs that you walk through. The array version is easier to read and extend. Both are fine; choose one and explain why.

**Done when:** all six satellite values and the fix change are tested.

---

## Phase 5 — Documentation

### Task 15 — Complete the MiniMSP response specification

**Goal:** Someone who has never seen your code could write a MiniMSP responder from `docs/protocol.md` alone.

**What to do**
1. Open `docs/protocol.md`. It lists command IDs and request payloads, but not the responses.
2. For each command (01 ATTITUDE, 02 IMU, 03 ALTITUDE, 04 BATTERY, 05 STATUS, 06 SET_CONTROL, 07 GPS), add: the response payload length in bytes, the field order, the type of each field, and the scale factor. Use the "Numeric encoding" and "Command IDs" tabs in the handbook as the source.
3. Add an error response section: a rejected request is answered with `CMD | 0x80` and a one-byte error code. Copy the codes from the handbook.
4. Add one worked example in hex, for example the full 6-byte `GET_ATTITUDE` response for `(12.4, -3.2, 91.0)` (after you have decided the byte order in Task 10).
5. Fix the spelling mistakes in the checksum section ("biwise", "erros", "exluded").

**Explanation:** A protocol specification is a contract between two programs. It is only useful if it is complete and precise. "Some bytes" is not enough: you must give the length, the order, the type, the byte order, and the scale of every field. Writing a worked example by hand is one of the best ways to find ambiguities in your own spec. Your future self, and any real Betaflight MSP code you write later, will depend on this document.

**Done when:** you can hand the document to a classmate and they can write the attitude responder without asking you a question.

---

## After these tasks

When Phases 1–5 are done, Day 11 (end-to-end attitude request and response) can start. Its acceptance criteria will then be testable against the fixed codec and scenario.
