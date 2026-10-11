#include <stdio.h>
#include "types.h"
#include "validations.h"

const Attitude attitude = {
    .roll_deg = 0,
    .pitch_deg = 10,
    .yaw_deg = 0,
};


int main() {
    const bool is_gps_coordinates_valid = gps_coordinates_valid(0, 0);
    printf("Hello from Companion!\n");
    printf("attitude.roll_deg %f\n", attitude.roll_deg);
    printf("attitude.pitch_deg %f\n", attitude.pitch_deg);
    printf("attitude.yaw_deg %f\n", attitude.yaw_deg);
    if(is_gps_coordinates_valid) {
        printf("GPS Coordinates are Valid\n");
    } else {
        printf("GPS Coordinates are NOT Valid\n");
    }
    return 0;
}