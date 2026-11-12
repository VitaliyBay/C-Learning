#ifndef SENSORS_H
#define SENSORS_H

#include <stdbool.h>
#include <stdint.h>
#include "types.h"

typedef struct {
    Attitude attitude;
    Gyroscope gyroscope;
    Accelerometer accelerometer;
    GpsData gps_data;
    BatteryData battery_data;
    FlightStatus flight_status;
} SensorData;

void sensors_init(SensorData *sensors_data);
void sensors_update(SensorData *sensors_data);

#endif // SENSORS_H