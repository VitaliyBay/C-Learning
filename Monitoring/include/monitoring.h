#ifndef MONITORING_H
#define MONITORING_H

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
    FAILSAFE
} FlightState;

FlightState get_flight_state(const DroneTelemetry *telemetry[]);

#endif // MONITORING_H