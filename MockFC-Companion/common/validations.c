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

bool attitude_valid(Attitude attitude) {
    if(attitude.roll_deg < -180 || attitude.roll_deg > 180) {
        return false;
    }

    if(attitude.pitch_deg < -180 || attitude.pitch_deg > 180) {
        return false;
    }

    if(attitude.yaw_deg < 0 || attitude.yaw_deg > 360) {
        return false;
    }

    return true;
}

bool gps_satelites_valid(uint8_t satelites) {
    if(satelites > 32) {
        return false;
    }

    return true;
}

bool battery_voltage_valid(float voltage) {
    if(voltage < 0 || voltage > 30) {
        return false;
    }

    return true;
}