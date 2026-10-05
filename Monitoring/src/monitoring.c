#include "monitoring.h"
#include <math.h>
#include <stdio.h>

FlightState get_flight_state(const DroneTelemetry *telemetry) {
    if(telemetry->armed == 0) {
        return DISARMED;
    }

    if(telemetry->armed == 1 && (telemetry->battery_voltage < 18 || telemetry->gps_satellites < 4 || fabsf(telemetry->roll) > 45.0 || fabsf(telemetry->pitch) > 45.0)) {
        return FAILSAFE;
    }

    if(telemetry->armed == 1 && telemetry->throttle == 0) {
        return ARMED;
    }

    if(telemetry->armed == 1 && telemetry->throttle > 0) {
        return FLYING;
    }

    return UNKNOWN;
}

void print_monitoring_warnings(const DroneTelemetry *telemetry) {
    int hasIssue = 0;
    if(telemetry->battery_voltage >= 18 && telemetry->battery_voltage < 21) {
        hasIssue = 1;
        printf("\n     - LOW BATTERY");
    }

    if(telemetry->battery_voltage < 18) {
        hasIssue = 1;
        printf("\n     - BATTERY CRITICAL");
    }

    if(telemetry->gps_satellites >= 4 && telemetry->gps_satellites < 7) {
        hasIssue = 1;
        printf("\n     - GPS SIGNAL WEAK");
    }

    if(telemetry->gps_satellites < 4) {
        hasIssue = 1;
        printf("\n     - GPS SIGNAL LOST");
    }

    if(fabsf(telemetry->roll) > 30 && fabsf(telemetry->roll) < 45) {
        hasIssue = 1;
        printf("\n     - HIGH ROLL ANGLE");
    }

    if(fabsf(telemetry->roll) > 45) {
        hasIssue = 1;
        printf("\n     - ROLL ANGLE TOO HIGH");
    }

    if(fabsf(telemetry->pitch) > 30 && fabsf(telemetry->pitch) < 45) {
        hasIssue = 1;
        printf("\n     - HIGH PITCH ANGLE");
    }

    if(fabsf(telemetry->pitch) > 45) {
        hasIssue = 1;
        printf("\n     - ROLL PITCH TOO HIGH");
    }

    if(hasIssue == 0) {
        printf("  None");
    }

}