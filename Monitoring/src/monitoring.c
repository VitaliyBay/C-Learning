#include "monitoring.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>

FlightState get_flight_state(const DroneTelemetry *telemetry, uint32_t warning_flags) {
    if(telemetry->armed == 0) {
        return DISARMED;
    }

    if(warning_flags & CRITICAL_FLAGS) {
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

uint32_t get_warning_flags(const DroneTelemetry *telemetry) {
    uint32_t warning_flags = 0;

    if(telemetry->battery_voltage >= 18 && telemetry->battery_voltage < 21) {
        warning_flags |= WARNING_LOW_BATTERY;
    }

    if(telemetry->battery_voltage < 18) {
        warning_flags |= CRITICAL_BATTERY;
    }

    if(telemetry->gps_satellites >= 4 && telemetry->gps_satellites < 7) {
        warning_flags |= WARNING_GPS_SIGNAL_WEAK;
    }

    if(telemetry->gps_satellites < 4) {
        warning_flags |= CRITICAL_GPS_SIGNAL;
    }

    if(fabsf(telemetry->roll) > 30 && fabsf(telemetry->roll) < 45) {
        warning_flags |= WARNING_HIGH_ROLL_ANGLE;
    }

    if(fabsf(telemetry->roll) > 45) {
        warning_flags |= CRITICAL_ROLL_ANGLE;
    }

    if(fabsf(telemetry->pitch) > 30 && fabsf(telemetry->pitch) < 45) {
        warning_flags |= WARNING_HIGH_PITCH_ANGLE;
    }

    if(fabsf(telemetry->pitch) > 45) {
        warning_flags |= CRITICAL_PITCH_ANGLE;
    }

    return warning_flags;
}