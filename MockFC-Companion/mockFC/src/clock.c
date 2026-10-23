#include "clock.h"


void clock_init(ClockState *clock_state) {
    clock_state->now_ms = 0;
}

void clock_advance_time(ClockState *clock_state) {
    clock_state->now_ms += 10;
}