#include <stdbool.h>
#include <math.h>

#include "encoding.h"
#include "telemetry_codec.h"

bool encode_attitude(Attitude value, uint8_t *buffer, size_t capacity) {
    if(buffer == NULL || capacity < ATTITUDE_BEFFER_SIZE) {
        return false;
    }
    
    uint8_t yaw_buffer[2];
    float scaled_yaw = roundf(value.yaw_deg * 10.0f);
    bool is_yaw_encodded = encode_i16_le((int16_t)scaled_yaw, yaw_buffer, sizeof(yaw_buffer));

    if(is_yaw_encodded == false) {
        return false;
    }

    uint8_t pitch_buffer[2];
    float scaled_pitch = roundf(value.pitch_deg * 10.0f);
    bool is_pitch_encodded = encode_i16_le((int16_t)scaled_pitch, pitch_buffer, sizeof(pitch_buffer));

    if(is_pitch_encodded == false) {
        return false;
    }

    
    uint8_t roll_buffer[2];
    float scaled_roll = roundf(value.roll_deg * 10.0f);
    bool is_roll_encodded = encode_i16_le((int16_t)scaled_roll, roll_buffer, sizeof(roll_buffer));

    if(is_roll_encodded == false) {
        return false;
    }

    buffer[0] = yaw_buffer[0];
    buffer[1] = yaw_buffer[1];
    buffer[2] = pitch_buffer[0];
    buffer[3] = pitch_buffer[1];
    buffer[4] = roll_buffer[0];
    buffer[5] = roll_buffer[1];

    return true;
}