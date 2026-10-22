#include <stddef.h>
#include "sensors.h"

void sensors_init(SensorData *sensors_data)
{
    if (sensors_data == NULL) {
        return;
    }

    *sensors_data = (SensorData) {
        .attitude = {
            .roll_deg = 0.0f,
            .pitch_deg = 0.0f,
            .yaw_deg = 0.0f
        },
        .gyroscope = {
            .x_dps = 0.0f,
            .y_dps = 0.0f,
            .z_dpf = 0.0f
        },
        .accelerometer = {
            .x_dps = 0.0f,
            .y_dps = 0.0f,
            .z_dpf = 0.0f
        },
        .gps_data = {
            .fix_type = GPS_FIX_3D,
            .satellites = 10,
            .latitude_deg = 41.3851,
            .longitude_deg = 2.1734,
            .altitude_m = 100.0f
        },
        .battery_data = {
            .voltage_v = 16.8f,
            .current_a = 0.0f,
            .consumed_mah = 0
        },
        .flight_status = {
            .armed = false,
            .flight_mode = FLIGHT_MODE_ANGLE,
            .failsafe_active = false
        }
    };
}

void sensors_update(SensorData *sensors_data) {
    if(sensors_data == NULL) {
        return ;
    }
}