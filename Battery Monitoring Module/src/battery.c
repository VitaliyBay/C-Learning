#include "battery.h"
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    float voltage;
    uint8_t percentage;
} BatteryPoint;

static const BatteryPoint batteryVoltageTable[] =
{
    {4.20f, 100},
    {4.15f, 95},
    {4.11f, 90},
    {4.08f, 85},
    {4.02f, 80},
    {3.98f, 75},
    {3.95f, 70},
    {3.91f, 65},
    {3.87f, 60},
    {3.85f, 55},
    {3.84f, 50},
    {3.82f, 45},
    {3.80f, 40},
    {3.79f, 35},
    {3.77f, 30},
    {3.75f, 25},
    {3.73f, 20},
    {3.71f, 15},
    {3.69f, 10},
    {3.61f, 5},
    {3.27f, 0}
};

#define TABLE_SIZE (sizeof(batteryVoltageTable) / sizeof(batteryVoltageTable[0]))

float getEstimatedPercentagePerCell(float cellVoltage) {
    if (cellVoltage >= batteryVoltageTable[0].voltage) {
        return 100.0f;
    }

    if (cellVoltage <= batteryVoltageTable[TABLE_SIZE - 1].voltage) {
        return 0.0f;
    }

    for(size_t i = 0; i < (TABLE_SIZE - 1); i++) {
        BatteryPoint high = batteryVoltageTable[i];
        BatteryPoint low = batteryVoltageTable[i + 1];

        if(cellVoltage <= high.voltage && cellVoltage >= low.voltage) {
            float interpolationFactor = (cellVoltage - low.voltage) / (high.voltage - low.voltage);

            return low.percentage + interpolationFactor * (high.percentage - low.percentage);
        }
    }

    return 0.0f;
}

float getEstimatedPercentagePerPackage(float currentVoltage, uint8_t cells) {
    return getEstimatedPercentagePerCell(currentVoltage / cells);
}

BatteryState getStatePerPackage(float currentVoltage, uint8_t cells) {
    float batteryPercentage = getEstimatedPercentagePerPackage(currentVoltage, cells);

    return getStatePerPackageByBatteryPercentage(batteryPercentage);
}

BatteryState getStatePerPackageByBatteryPercentage(float batteryPercentage) {
    if(batteryPercentage >= 95) {
        return BATTERY_STATE_FULL;
    }

    if(batteryPercentage >= 70 && batteryPercentage <= 94) {
        return BATTERY_STATE_GOOD;
    }

    if(batteryPercentage >= 40 && batteryPercentage <= 69) {
        return BATTERY_STATE_NORMAL;
    }

    if(batteryPercentage >= 20 && batteryPercentage <= 39) {
        return BATTERY_STATE_LOW;
    }

    if(batteryPercentage >= 10 && batteryPercentage <= 19) {
        return BATTERY_STATE_CRITICAL;
    }

    return BATTERY_STATE_EMPTY;
}

char *batteryStateToString(BatteryState state) {
    switch (state)
    {
        case BATTERY_STATE_FULL:
            return "FULL";

        case BATTERY_STATE_GOOD:
            return "GOOD";
            
        case BATTERY_STATE_NORMAL:
            return "NORMAL";
            
        case BATTERY_STATE_LOW:
            return "LOW";
            
        case BATTERY_STATE_CRITICAL:
            return "CRITICAL";
            
        case BATTERY_STATE_EMPTY:
            return "EMPTY";
        
        default:
            return "UNKNOWN";
    }
}

BatteryWarning getWarningPerPackage(float currentVoltage, uint8_t cells) {
    float batteryPercentage = getEstimatedPercentagePerPackage(currentVoltage, cells);

    if(batteryPercentage >= 20 && batteryPercentage <= 30) {
        return BATTERY_WARNING_LOW_BATTERY;
    }

    if(batteryPercentage >= 10 && batteryPercentage <= 19) {
        return BATTERY_WARNING_RETURN_HOME;
    }

    if(batteryPercentage <= 9) {
        return BATTERY_WARNING_LAND_NOW;
    }
    
    return BATTERY_WARNING_NONE;
}


char *batteryWarningToString(BatteryWarning warning) {
    switch (warning)
    {
        case BATTERY_WARNING_NONE:
            return "NONE";

        case BATTERY_WARNING_LOW_BATTERY:
            return "LOW BATTERY";

        case BATTERY_WARNING_RETURN_HOME:
            return "RETURN HOME";

        case BATTERY_WARNING_LAND_NOW:
            return "LAND NOW";
        
        default:
            return "UNKNOWN";
    }
}