#include "clock.h"
#include "scenario.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>

void test_scenario_updates_set_altitude_to_10_when_now_ms_time_is_15000() {
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


void test_scenario_updates_altitude_rise_by_0_1_every_100_ms_up_to_15000_ms() {
    ClockState clock_state;
    SensorData sensor_data;

    clock_init(&clock_state);
    sensors_init(&sensor_data);

    while (clock_state.now_ms < 15000)
    {
        clock_advance_time(&clock_state);

        scenario_updates(&clock_state, &sensor_data);

        if(clock_state.now_ms == 5000) {
            assert(sensor_data.gps_data.altitude_m == 0);
        }

        if(clock_state.now_ms == 10000) {
            assert(sensor_data.gps_data.altitude_m == 5.0);
        }

        if(clock_state.now_ms == 14900) {
            assert(fabsf(sensor_data.gps_data.altitude_m - 9.9) < 0.01f);
        }
    }

    assert(clock_state.now_ms >= 15000);
    assert(sensor_data.gps_data.altitude_m == 10);
}

int main() {
    test_scenario_updates_set_altitude_to_10_when_now_ms_time_is_15000();
    test_scenario_updates_altitude_rise_by_0_1_every_100_ms_up_to_15000_ms();

    printf("[TEST SCENARIO] All tests passed!");

    return 0;
}