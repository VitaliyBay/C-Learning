#ifndef SCENARIO_H
#define SCENARIO_H

#include "clock.h"
#include "sensors.h"

void scenario_updates(ClockState *clock_state, SensorData *sensor_data);

#endif // SCENARIO_H