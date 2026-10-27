#ifndef ENCODING_H
#define ENCODING_H

#include <stdbool.h>
#include <stdint.h>

// u -> unsigned
// i -> signed
// le -> little-endian

bool encode_u16_le(uint16_t value, uint8_t *buffer, size_t capacity);
bool decode_u16_le(const uint8_t *buffer, size_t length, uint16_t *value);

bool encode_i16_le(int16_t value, uint8_t *buffer, size_t capacity);
bool decode_i16_le(const uint8_t *buffer, size_t length, int16_t *value);

bool encode_u32_le(uint32_t value, uint8_t *buffer, size_t capacity);
bool decode_U32_le(const uint8_t *buffer, size_t length, uint32_t *value);

bool encode_i32_le(int32_t value, uint8_t *buffer, size_t capacity);
bool decode_i32_le(const uint8_t *buffer, size_t length, int32_t *value);
#endif // ENCODING_H