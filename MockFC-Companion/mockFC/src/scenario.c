#include "scenario.h"
#include "sensors.h"
#include "clock.h"

void scenario_updates(ClockState *clock_state, SensorData *sensor_data) {
    if(sensor_data == NULL) {
        return;
    }

    if(clock_state->now_ms >= 15000) {
        sensor_data->gps_data.altitude_m = 10;
    }

    if(clock_state->now_ms >= 26000 && clock_state->now_ms < 30000) {
        sensor_data->attitude.roll_deg = 20;
    } else if(clock_state->now_ms >= 30000) {
        sensor_data->attitude.roll_deg = 0;
    }

    if(clock_state->now_ms >= 37500) {
        sensor_data->gps_data.fix_type = GPS_FIX_NONE;
        sensor_data->gps_data.satellites = 3;
    }

    if(clock_state->now_ms >= 45000) {
        uint32_t elapsed_ms = clock_state->now_ms - 45000;
        uint32_t drops = 1 + (elapsed_ms / 1000);

        sensor_data->battery_data.voltage_v = 
                sensor_data->battery_data.voltage_v - (0.2f * drops);
    }
}