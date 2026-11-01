#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "../common/encoding.h"

// encode_u16_le
void test_encode_u16_le_returns_false_when_buffer_is_null() {
    uint16_t value = 100;

    bool is_succeeded = encode_u16_le(value, NULL, sizeof(0));

    assert(is_succeeded == false);
}

void test_encode_u16_le_returns_false_when_buffer_size_is_lower_than_2() {
    uint8_t buffer[1];
    uint16_t value = 100;

    bool is_succeeded = encode_u16_le(value, buffer, sizeof(buffer));

    assert(is_succeeded == false);
}

void test_encode_u16_le_returns_true_and_data_encoded_corectly() {
    uint8_t buffer[2];

    bool is_succeeded = encode_u16_le(0x1234, buffer, sizeof(buffer));

    assert(is_succeeded == true);
    assert(buffer[0] == 0x34);
    assert(buffer[1] == 0x12);
}

// decode_u16_le
void test_decode_u16_le_return_false_when_buffer_is_null() {
    uint16_t value = 0;

    bool is_succeeded = decode_u16_le(NULL, sizeof(0), &value);

    assert(is_succeeded == false);
}

void test_decode_u16_le_returns_false_when_buffer_size_is_lower_than_2() {
    uint8_t buffer[1];
    uint16_t value = 0;

    bool is_succeeded = decode_u16_le(buffer, sizeof(buffer), &value);

    assert(is_succeeded == false);
}

void test_decode_u16_le_return_false_when_value_is_null() {
    uint8_t buffer[2];

    bool is_succeeded = decode_u16_le(buffer, sizeof(buffer), NULL);

    assert(is_succeeded == false);
}

void test_decode_u16_le_returns_true_and_data_decoded_corectly() {
    uint8_t buffer[2] = { 0x34, 0x12 };
    uint16_t value = 0;

    bool is_succeeded = decode_u16_le(buffer, sizeof(buffer), &value);

    assert(is_succeeded == true);
    assert(value == 0x1234);
}

// encode_i16_le
void test_encode_i16_le_returns_false_when_buffer_is_null() {
    uint16_t value = 100;

    bool is_succeeded = encode_i16_le(value, NULL, sizeof(0));

    assert(is_succeeded == false);
}

void test_encode_i16_le_returns_false_when_buffer_size_is_lower_than_2() {
    uint8_t buffer[1];
    uint16_t value = 100;

    bool is_succeeded = encode_i16_le(value, buffer, sizeof(buffer));

    assert(is_succeeded == false);
}

void test_encode_i16_le_returns_true_and_data_encoded_corectly() {
    uint8_t buffer[2];

    bool is_succeeded = encode_i16_le(0x7FFE, buffer, sizeof(buffer));

    assert(is_succeeded == true);
    assert(buffer[0] == 0xFE);
    assert(buffer[1] == 0x7F);
}

// decode_i16_le
void test_decode_i16_le_return_false_when_buffer_is_null() {
    int16_t value = 0;

    bool is_succeeded = decode_i16_le(NULL, sizeof(0), &value);

    assert(is_succeeded == false);
}

void test_decode_i16_le_returns_false_when_buffer_size_is_lower_than_2() {
    uint8_t buffer[1];
    int16_t value = 0;

    bool is_succeeded = decode_i16_le(buffer, sizeof(buffer), &value);

    assert(is_succeeded == false);
}

void test_decode_i16_le_return_false_when_value_is_null() {
    uint8_t buffer[2];

    bool is_succeeded = decode_i16_le(buffer, sizeof(buffer), NULL);

    assert(is_succeeded == false);
}

void test_decode_i16_le_returns_true_and_data_decoded_corectly() {
    uint8_t buffer[2] = { 0x34, 0x12 };
    int16_t value = 0;

    bool is_succeeded = decode_i16_le(buffer, sizeof(buffer), &value);

    assert(is_succeeded == true);
    assert(value == 0x1234);
}

// encode_u32_le
void test_encode_u32_le_returns_false_when_buffer_is_null() {
    uint16_t value = 100;

    bool is_succeeded = encode_u32_le(value, NULL, sizeof(0));

    assert(is_succeeded == false);
}

void test_encode_u32_le_returns_false_when_buffer_size_is_lower_than_4() {
    uint8_t buffer[3];
    uint16_t value = 100;

    bool is_succeeded = encode_u32_le(value, buffer, sizeof(buffer));

    assert(is_succeeded == false);
}

void test_encode_u32_le_returns_true_and_data_encoded_corectly() {
    uint8_t buffer[4];

    bool is_succeeded = encode_u32_le(0xFFFFFFFE, buffer, sizeof(buffer));

    assert(is_succeeded == true);
    assert(buffer[0] == 0xFE);
    assert(buffer[1] == 0xFF);
    assert(buffer[2] == 0xFF);
    assert(buffer[3] == 0xFF);
}

// encode_i32_le
void test_encode_i32_le_returns_false_when_buffer_is_null() {
    uint16_t value = 100;

    bool is_succeeded = encode_i32_le(value, NULL, sizeof(0));

    assert(is_succeeded == false);
}

void test_encode_i32_le_returns_false_when_buffer_size_is_lower_than_4() {
    uint8_t buffer[3];
    uint16_t value = 100;

    bool is_succeeded = encode_i32_le(value, buffer, sizeof(buffer));

    assert(is_succeeded == false);
}

void test_encode_i32_le_returns_true_and_data_encoded_corectly() {
    uint8_t buffer[4];

    bool is_succeeded = encode_i32_le(0x7FFFFFFF, buffer, sizeof(buffer));

    assert(is_succeeded == true);
    assert(buffer[0] == 0xFF);
    assert(buffer[1] == 0xFF);
    assert(buffer[2] == 0xFF);
    assert(buffer[3] == 0x7F);
}

int main() {
    // encode_u16_le
    test_encode_u16_le_returns_false_when_buffer_is_null();
    test_encode_u16_le_returns_false_when_buffer_size_is_lower_than_2();
    test_encode_u16_le_returns_true_and_data_encoded_corectly();

    // decode_u16_le
    test_decode_u16_le_return_false_when_buffer_is_null();
    test_decode_u16_le_returns_false_when_buffer_size_is_lower_than_2();
    test_decode_u16_le_return_false_when_value_is_null();
    test_decode_u16_le_returns_true_and_data_decoded_corectly();

    // decode_i16_le
    test_decode_i16_le_return_false_when_buffer_is_null();
    test_decode_i16_le_returns_false_when_buffer_size_is_lower_than_2();
    test_decode_i16_le_return_false_when_value_is_null();
    test_decode_i16_le_returns_true_and_data_decoded_corectly();

    // encode_16_le
    test_encode_i16_le_returns_false_when_buffer_is_null();
    test_encode_i16_le_returns_false_when_buffer_size_is_lower_than_2();
    test_encode_i16_le_returns_true_and_data_encoded_corectly();

    // encode_u32_le
    test_encode_u32_le_returns_false_when_buffer_is_null();
    test_encode_u32_le_returns_false_when_buffer_size_is_lower_than_4();
    test_encode_u32_le_returns_true_and_data_encoded_corectly();

    // encode_i32_le
    test_encode_i32_le_returns_false_when_buffer_size_is_lower_than_4();
    test_encode_i32_le_returns_true_and_data_encoded_corectly();
    test_encode_i32_le_returns_false_when_buffer_is_null();

    printf("[Test Encoding] All tests passed!\n");

    return 0;
}