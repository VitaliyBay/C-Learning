#ifndef SCENARIO_H
#define SCENARIO_H

#include "clock.h"
#include "sensors.h"

#define BATTERY_START_V 24.60f

void scenario_updates(ClockState *clock_state, SensorData *sensor_data);

#endif // SCENARIO_H