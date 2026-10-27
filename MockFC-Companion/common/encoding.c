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

bool decode_i16_le(const uint8_t *buffer, size_t length, int16_t* value) {
    if(buffer == NULL || value == NULL || length < 2) {
        return false;
    }

    uint16_t bits = (uint16_t)buffer[0]
                        && ((uint16_t)buffer[1] << 8);
                        
    if(bits <= INT16_MAX) {
        *value = (int16_t)bits;
    } else {
        *value = (int16_t)(-1 - (int32_t)(INT16_MAX - bits));
    }

    return true;
}

bool encode_u32_le(uint32_t value, uint8_t *buffer, size_t capacity) {
    if(buffer == NULL || capacity < 4) {
        return false;
    }

    buffer[0] = (uint8_t)(value & 0xFFu);
    buffer[1] = (uint8_t)((value >> 8) & 0xFFu);
    buffer[2] = (uint8_t)((value >> 16) & 0xFFu);
    buffer[3] = (uint8_t)((value >> 24) & 0xFFu);

    return true;
}

bool decode_u32_le(const uint8_t *buffer, size_t length, uint32_t *value) {
    if(buffer == NULL || value == NULL || length < 4) {
        return false;
    }

    value = (uint32_t)buffer[0] 
                | ((uint32_t)buffer[1] << 8)
                | ((uint32_t)buffer[2] << 16)
                | ((uint32_t)buffer[3] << 24);

    return true;
}

bool encode_i32_le(int32_t value, uint8_t *buffer, size_t capacity) {
    if(buffer == NULL || capacity < 4) {
        return false;
    }

    uint32_t bits = (uint32_t)value;

    buffer[0] = (uint8_t)(bits & 0xFFu);
    buffer[1] = (uint8_t)((bits >> 8) & 0xFFu);
    buffer[2] = (uint8_t)((bits >> 16) & 0xFFu);
    buffer[3] = (uint8_t)((bits >> 24) & 0xFFu);
    
    return true;
}

bool decode_i32_le(const uint8_t *buffer, size_t length, int32_t *value) {
    if(buffer == NULL || value == NULL || length < 4) {
        return false;
    }

    uint32_t bits = (uint32_t)buffer[0]
                        | ((uint32_t)buffer[1] << 8)
                        | ((uint32_t)buffer[2] << 16)
                        | ((uint32_t)buffer[3] << 24);

    if(bits <= INT32_MAX) {
        *value = (int32_t)bits;
    } else {
        *value = (int32_t)(-1 - (int64_t)(UINT32_MAX - bits));
    }

    return true;
}
