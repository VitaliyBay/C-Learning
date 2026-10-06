#include <stdio.h>
#include <stdint.h>
#include "monitoring.h"

const char* flight_state_to_string(FlightState state) {
    switch(state) {
        case ARMED: return "ARMED";
        case DISARMED: return "DISARMED";
        case FLYING: return "FLYING";
        case FAILSAFE: return "FAILSAFE";
        case UNKNOWN: return "UNKNOWN";
        default: return "UNKNOWN";
    }
}

void print_warning_flags(const uint32_t warning_flags) {
    if(warning_flags & WARNING_LOW_BATTERY) {
        printf("\n     - LOW BATTERY");
    }
    if(warning_flags & WARNING_GPS_SIGNAL_WEAK) {
        printf("\n     - GPS SIGNAL WEAK");
    }
    if(warning_flags & WARNING_HIGH_ROLL_ANGLE) {
        printf("\n     - HIGH ROLL ANGLE");
    }
    if(warning_flags & WARNING_HIGH_PITCH_ANGLE) {
        printf("\n     - HIGH PITCH ANGLE");
    }
    if(warning_flags & CRITICAL_BATTERY) {
        printf("\n     - BATTERY CRITICAL");
    }
    if(warning_flags & CRITICAL_GPS_SIGNAL) {
        printf("\n     - GPS SIGNAL LOST");
    }
    if(warning_flags & CRITICAL_ROLL_ANGLE) {
        printf("\n     - ROLL ANGLE TOO HIGH");
    }
    if(warning_flags & CRITICAL_PITCH_ANGLE) {
        printf("\n     - ROLL PITCH TOO HIGH");
    }

    if(warning_flags == 0) {
        printf("  None");
    }
}

int main() {
    const DroneTelemetry telemetry[] = {
        {24.6f, 12, 0.0f, 0.0f, 0.0f, 0, 0},
        {24.3f, 12, 2.5f, 1.2f, -0.5f, 30, 1},
        {23.8f, 11, 45.0f, 4.2f, -2.1f, 55, 1},
        {20.7f, 10, 50.0f, 60.0f, 1.0f, 60, 1},
        {22.1f, 5, 48.0f, 38.0f, 5.0f, 70, 1}
    };
    int length = sizeof(telemetry) / sizeof(telemetry[0]);
    for(int i = 1; i <= length; i++) {
        printf("---- Telementry #%d ----\n", i);
        FlightState state = get_flight_state(&telemetry[i - 1]);
        printf("State %s \n", flight_state_to_string(state));
        printf("Warnings: ");
        const uint32_t warning_flags = get_warning_flags(&telemetry[i - 1]);
        print_warning_flags(warning_flags);
        printf("\n\n");
    }

    return 0;
}