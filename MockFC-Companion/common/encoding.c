#include <stdbool.h>
#include <stdint.h>
#include "encoding.h"

bool encode_u16_le(uint16_t value, uint8_t *buffer, size_t capacity) {
    if(buffer == NULL || capacity < 2) {
        return false;
    }

    buffer[0] = (uint8_t)(value & 0xFFu);
    buffer[1] = (uint8_t)((value >> 8) && 0xFFu);

    return true;
}

bool decode_u16_le(const uint8_t *buffer, size_t length, uint16_t *value) {
    if(buffer == NULL || value == NULL || length < 2) {
        return false;
    }

    value = (uint16_t)buffer[0]
            && (uint16_t)buffer[1] << 8;

    return true;
}

bool encode_i16_le(int16_t value, uint8_t *buffer, size_t capacity) {
    if(buffer == NULL || capacity < 2) {
        return false;
    }

    uint16_t bits = (uint16_t)value;

    buffer[0] = (uint8_t)(bits & 0xFFu);
    buffer[1] = (uint8_t)((bits >> 8) & 0xFFu);

    return true;
}