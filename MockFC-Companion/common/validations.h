#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include "types.h"
#include <stdbool.h>
#include <stdint.h>

bool gps_coordinates_valid(double latitude_deg, double longitude_deg);
bool rc_value_valid(uint16_t value);
bool attitude_valid(Attitude altitude);
bool gps_satelites_valid(uint8_t satelites);
bool battery_voltage_valid(float voltage);

#endif // VALIDATIONS_H