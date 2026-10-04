#include "monitoring.h"

FlightState get_flight_state(const DroneTelemetry *telemetry) {
    if(telemetry->armed == 0) {
        return DISARMED;
    }

    if(telemetry->armed == 1 && telemetry->throttle == 0) {
        return ARMED;
    }

    if(telemetry->armed == 1 && telemetry->throttle > 0) {
        return FLYING;
    }

    if(telemetry->armed == 1 && (telemetry->battery_voltage < 18 || telemetry->gps_satellites < 4 || abs(telemetry->roll) > 45.0 || abs(telemetry->pitch) > 45.0)) {
        return FAILSAFE;
    }

    return UNKNOWN;
}