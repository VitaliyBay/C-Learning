#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define PROTOCOL_SYNC 0x24
#define PROTOCOL_MAX_PAYLOAD 64

typedef enum {
    WAIT_SYNC,
    READ_CMD,
    READ_LENGTH,
    READ_PAYLOAD,
    READ_CHECKSUM
} ParserState;

typedef struct {
    uint8_t cmd;
    uint8_t length;
    uint8_t payload[PROTOCOL_MAX_PAYLOAD];
} ProtocolFrame;

typedef struct {
    ParserState state;
    ProtocolFrame frame;
    uint8_t payload_index;
    uint8_t checksum;
} ProtocolParser;

#endif // PROTOCOL_H