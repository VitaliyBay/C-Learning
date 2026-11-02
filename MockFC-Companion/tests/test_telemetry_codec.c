#include "telemetry_codec.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

// encode_attitude
void test_encode_attitude_should_return_false_when_buffer_is_null() {
    Attitude attitude = {
        .roll_deg = 10.0f,
        .pitch_deg = 10.0f,
        .yaw_deg = 10.0f
    };

    bool is_attitude_encoded = encode_attitude(attitude, NULL, sizeof(int16_t));

    assert(is_attitude_encoded == false);
}

void test_encode_attitude_should_return_false_when_buffer_capacity_is_lower_than_6() {
    uint8_t buffer[5];
    Attitude attitude = {
        .roll_deg = 10.0f,
        .pitch_deg = 10.0f,
        .yaw_deg = 10.0f
    };

    bool is_attitude_encoded = encode_attitude(attitude, buffer, sizeof(buffer));

    assert(is_attitude_encoded == false);
}


void test_encode_attitude_should_return_true_when_data_are_valid() {
    uint8_t buffer[6];
    Attitude attitude = {
        .roll_deg = 10.0f,
        .pitch_deg = 10.0f,
        .yaw_deg = 10.0f
    };

    bool is_attitude_encoded = encode_attitude(attitude, buffer, sizeof(buffer));

    assert(is_attitude_encoded == true);
    assert(buffer[0] == 0x64);
    assert(buffer[1] == 0x00);
    assert(buffer[2] == 0x64);
    assert(buffer[3] == 0x00);
    assert(buffer[4] == 0x64);
    assert(buffer[5] == 0x00);
}

int main() {
    // encode_attitude
    test_encode_attitude_should_return_false_when_buffer_is_null();
    test_encode_attitude_should_return_false_when_buffer_capacity_is_lower_than_6();
    test_encode_attitude_should_return_true_when_data_are_valid();

    printf("[TELEMETRY CODEC] All tests passed!!!\n");

    return 0;
}