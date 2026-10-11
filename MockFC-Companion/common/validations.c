#include "types.h"
#include "validations.h"
#include <stdbool.h>
#include <stdint.h>

bool gps_coordinates_valid(double latitude_deg, double longitude_deg) {
    return false;
}

bool rc_value_valid(uint16_t value) {
    return false;
}

bool attitude_valid(Attitude altitude) {
    return false;
}

bool gps_satelites_valid(uint8_t satelites) {
    return false;
}

bool battery_voltage_valid(float voltage) {
    return false;
}