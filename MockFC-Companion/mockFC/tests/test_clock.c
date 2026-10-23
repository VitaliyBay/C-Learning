#include "clock.h"
#include <assert.h>
#include <stdio.h>

void test_clock_init_set_initial_value_to_0() {
    ClockState clock_state;
    clock_init(&clock_state);

    assert(clock_state.now_ms == 0);
}


void test_clock_advance_time_advance_to_20_ms_after_2_steps() {
    ClockState clock_state;
    clock_init(&clock_state);

    clock_advance_time(&clock_state);
    clock_advance_time(&clock_state);

    assert(clock_state.now_ms == 20);
}

int main() {
    test_clock_init_set_initial_value_to_0();
    test_clock_advance_time_advance_to_20_ms_after_2_steps();

    printf("All tests passed!");

    return 0;
}