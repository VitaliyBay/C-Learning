#include "battery.h"
#include <stdio.h>
#include <stdint.h>
#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

int main() {

    const uint8_t cells = 6;
    const float dischargeStep = 0.4;
    float currentVoltage = 25.2;
    float minVoltage = 3.2 * cells;

    while(currentVoltage >= minVoltage) {
        float batteryPercentage = getEstimatedPercentagePerPackage(currentVoltage, cells);

        printf(
            "Pack %.2f V | Cell %.2f V | SoC %.1f%% | State %s | Warning %s\n",
            currentVoltage,
            currentVoltage / cells,
            batteryPercentage,
            batteryStateToString(getStatePerPackageByBatteryPercentage(batteryPercentage)),
            batteryWarningToString(getWarningPerPackage(currentVoltage, cells))
        );
        printf("\n");

        currentVoltage -= dischargeStep;

        SLEEP_MS(2000);
    }

    return 0;
}