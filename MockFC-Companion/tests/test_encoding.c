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


int main() {
    // encode_u16_le
    test_encode_u16_le_returns_false_when_buffer_is_null();
    test_encode_u16_le_returns_false_when_buffer_size_is_lower_than_2();
    test_encode_u16_le_returns_true_and_data_encoded_corectly();

    printf("[Test Encoding] All tests passed!\n");

    return 0;
}