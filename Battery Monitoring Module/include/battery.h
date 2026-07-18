#ifndef BATTERY_H
#define BATTERY_H

#include <stdint.h>

typedef enum {
    BATTERY_STATE_FULL = 0,
    BATTERY_STATE_GOOD = 1,
    BATTERY_STATE_NORMAL = 2,
    BATTERY_STATE_LOW = 3,
    BATTERY_STATE_CRITICAL = 4,
    BATTERY_STATE_EMPTY = 5
} BatteryState;

float getEstimatedPercentagePerCell(float cellVoltage);
float getEstimatedPercentagePerPackage(float currentVoltage, uint8_t cells);
BatteryState getStatePerPackage(float currentVoltage, uint8_t cells);
char *batteryStateToString(BatteryState state);

#endif