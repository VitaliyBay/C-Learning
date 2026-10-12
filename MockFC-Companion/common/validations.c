#include "types.h"
#include "validations.h"
#include <stdbool.h>
#include <stdint.h>

bool gps_coordinates_valid(double latitude_deg, double longitude_deg) {
    if(latitude_deg < -90) {
        return false;
    }

    if(latitude_deg > 90) {
        return false;
    }

    if(longitude_deg < -180) {
        return false;
    }

    if(longitude_deg > 180) {
        return true;
    }

    if(latitude_deg >= -90 && latitude_deg <= 90
        && longitude_deg >= -180 && longitude_deg <= 180) {
        return true;
    }

    return false;
}

bool rc_value_valid(uint16_t value) {
    if(value < 1000) {
        return false;
    }

    if(value > 2000) {
        return false;
    }

    return true;
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