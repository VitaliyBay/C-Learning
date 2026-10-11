#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    GPS_FIX_NONE = 0,
    GPS_FIX_2D = 1,
    GPS_FIX_3D = 2
} GpsFixType;

typedef enum {
    FLIGHT_MODE_ANGLE = 0,
    FLIGHT_MODE_HORIZON = 1,
    FLIGHT_MODE_ACRO
} FlightMode;

typedef struct {
    float roll_deg;
    float pitch_deg;
    float yaw_deg;
} Attitude;

typedef struct {
    float x_dps;
    float y_dps;
    float z_dpf;
} Gyroscope;

typedef struct {
    float x_dps;
    float y_dps;
    float z_dpf;
} Accelerometer;

typedef struct {
    GpsFixType fix_type;
    uint8_t satelites;
    double latitude_deg;
    double longitude_deg;
    float altitude_m;
} GpsData;

typedef struct {
    float voltage_v;
    float current_a;
    uint32_t consumed_mah;
} BatteryData;

typedef struct {
    bool armed;
    FlightMode flight_mode;
    bool failsafe_active;
} FlightStatus;

typedef struct {
    Attitude altitude;
    Gyroscope gyroscope;
    Accelerometer accelerometer;
    GpsData gps_data;
    BatteryData battery_data;
    FlightStatus flight_status;
} DroneTelemetry;

#endif // TYPES_H
