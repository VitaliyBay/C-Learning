#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

typedef struct {
    uint32_t now_ms;
} ClockState;

void clock_init(ClockState *clock_state);

void clock_advance_time(ClockState *clock_state);

#endif // CLOCK_H