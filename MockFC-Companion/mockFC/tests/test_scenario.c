#include "clock.h"
#include "scenario.h"
#include <assert.h>
#include <stdio.h>

void test_scenario_updates_set_altitude_to_20_when_now_ms_time_is_15000() {
    ClockState clock_state;
    SensorData sensor_data;

    clock_init(&clock_state);
    sensors_init(&sensor_data);

    while (clock_state.now_ms < 15000)
    {
        clock_advance_time(&clock_state);
    }

    scenario_updates(&clock_state, &sensor_data);


    assert(clock_state.now_ms >= 15000);
    assert(sensor_data.gps_data.altitude_m == 10);
}

int main() {
    test_scenario_updates_set_altitude_to_20_when_now_ms_time_is_15000();

    printf("[TEST SCENARIO] All tests passed!");

    return 0;
}