#include "telemetry_codec.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>

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
        .roll_deg = 11.0f,
        .pitch_deg = 12.0f,
        .yaw_deg = 13.0f
    };

    bool is_attitude_encoded = encode_attitude(attitude, buffer, sizeof(buffer));

    assert(is_attitude_encoded == true);
    assert(buffer[0] == 0x82); // 130 le -> yaw
    assert(buffer[1] == 0x00);
    assert(buffer[2] == 0x78); // 120 le -> pitch
    assert(buffer[3] == 0x00);
    assert(buffer[4] == 0x6E); // 110 le -> roll
    assert(buffer[5] == 0x00);
}

// decode_attitude
void test_decode_attitude_return_false_when_buffer_is_null() {
    Attitude attitude;

    bool is_attitude_decoded = decode_attitude(NULL, sizeof(int16_t), &attitude);

    assert(is_attitude_decoded == false);
}

void test_decode_attitude_return_false_when_value_is_null() {
    uint8_t buffer[6];

    bool is_attitude_decoded = decode_attitude(buffer, sizeof(buffer), NULL);

    assert(is_attitude_decoded == false);
}

void test_decode_attitude_return_false_when_buffer_length_is_lower_than_6() {
    uint8_t buffer[5];
    Attitude attitude;

    bool is_attitude_decoded = decode_attitude(buffer, sizeof(buffer), &attitude);

    assert(is_attitude_decoded == false);
}

void test_decode_attitude_return_decode_attitude_when_data_are_valid() {
    uint8_t buffer[6] = {
        0x82, 0x00, // 130 le -> yaw
        0x78, 0x00, // 120 le -> pitch
        0x6E, 0x00 // 110 le -> roll
    };
    Attitude attitude;

    bool is_attitude_decoded = decode_attitude(buffer, sizeof(buffer), &attitude);

    assert(is_attitude_decoded == true);
    assert(attitude.yaw_deg == 13.0 && "Yaw deg is valid");
    assert(attitude.pitch_deg == 12.0 && "Pitch deg is valid");
    assert(attitude.roll_deg == 11.0 && "Roll deg is valid");
}

int main() {
    // encode_attitude
    test_encode_attitude_should_return_false_when_buffer_is_null();
    test_encode_attitude_should_return_false_when_buffer_capacity_is_lower_than_6();
    test_encode_attitude_should_return_true_when_data_are_valid();

    // decode_attitude
    test_decode_attitude_return_false_when_buffer_is_null();
    test_decode_attitude_return_false_when_value_is_null();
    test_decode_attitude_return_false_when_buffer_length_is_lower_than_6();
    test_decode_attitude_return_decode_attitude_when_data_are_valid();

    printf("[TELEMETRY CODEC] All tests passed!!!\n");

    return 0;
}