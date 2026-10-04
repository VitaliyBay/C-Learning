#include "monitoring.h"
#include <math.h>

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