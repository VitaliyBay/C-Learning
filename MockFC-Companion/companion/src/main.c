#include <stdio.h>
#include "types.h"

const Attitude attitude = {
    .roll_deg = 0,
    .pitch_deg = 10,
    .yaw_deg = 0,
};


int main() {
    printf("Hello from Companion!\n");
    printf("attitude.roll_deg %f\n", attitude.roll_deg);
    printf("attitude.pitch_deg %f\n", attitude.pitch_deg);
    printf("attitude.yaw_deg %f\n", attitude.yaw_deg);
    return 0;
}