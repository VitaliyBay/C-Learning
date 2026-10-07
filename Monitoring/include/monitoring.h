#ifndef MONITORING_H
#define MONITORING_H

#include <stdint.h>

#define WARNING_LOW_BATTERY        (1u << 0)
#define WARNING_GPS_SIGNAL_WEAK    (1u << 1)
#define WARNING_HIGH_ROLL_ANGLE    (1u << 2)
#define WARNING_HIGH_PITCH_ANGLE   (1u << 3)

#define CRITICAL_BATTERY           (1u << 4)
#define CRITICAL_GPS_SIGNAL        (1u << 5)
#define CRITICAL_ROLL_ANGLE        (1u << 6)
#define CRITICAL_PITCH_ANGLE       (1u << 7)

#define CRITICAL_FLAGS (CRITICAL_BATTERY | CRITICAL_GPS_SIGNAL | CRITICAL_ROLL_ANGLE | CRITICAL_PITCH_ANGLE)

typedef struct {
    float battery_voltage;
    int gps_satellites;
    float altitude;
    float roll;
    float pitch;
    int throttle;
    int armed;
} DroneTelemetry;

typedef enum {
    DISARMED,
    ARMED,
    FLYING,
    FAILSAFE,
    UNKNOWN
} FlightState;

FlightState get_flight_state(const DroneTelemetry *telemetry, uint32_t warning_flags);
void print_monitoring_warnings(const DroneTelemetry *telemetry);
uint32_t get_warning_flags(const DroneTelemetry *telemetry);

#endif // MONITORING_H