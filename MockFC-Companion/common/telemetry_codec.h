#ifndef TELEMETRY_CODEC_H
#define TELEMETRY_CODEC_H

#define ATTITUDE_BEFFER_SIZE 6

#include "types.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

bool encode_attitude(Attitude attitude, uint8_t *buffer, size_t capacity);

bool decode_attitude(uint8_t *buffer, size_t length, Attitude *value);

#endif // TELEMETRY_CODEC_H