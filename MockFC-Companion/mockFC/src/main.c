#include <stdio.h>
#include "types.h"
#include "sensors.h"

const Attitude attitude = {
    .roll_deg = 0,
    .pitch_deg = 10,
    .yaw_deg = 0,
};


int main() {
    SensorData sensors;
    sensors_init(&sensors);
    printf("Hello from MockFC!\n");
    printf("attitude.roll_deg %f\n", attitude.roll_deg);
    printf("attitude.pitch_deg %f\n", attitude.pitch_deg);
    printf("attitude.yaw_deg %f\n", attitude.yaw_deg);
    printf("sensors.gps_data.satelites %d\n", sensors.gps_data.satelites);
}