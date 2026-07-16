#ifndef BATTERY_H
#define BATTERY_H

#include <stdint.h>

float getEstimatedPercentagePerCell(float cellVoltage);
float getEstimatedPercentagePerPackage(float currentVoltage, uint8_t cells);

#endif