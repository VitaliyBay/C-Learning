#include "protocol.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

void protocol_parser_init(ProtocolParser *parser) {
    if(parser == NULL) {
        return;
    }

    parser->state = WAIT_SYNC;
    parser->frame.cmd = 0;
    parser->frame.length = 0;
    parser->payload_index = 0;
    parser->checksum = 0;
}

bool protocol_parser_ingest(ProtocolParser *parser, uint8_t byte, ProtocolFrame *out_frame) {
    if(parser == NULL || out_frame == NULL) {
        return false;
    }

    switch (parser->state)
    {
        case WAIT_SYNC:
            if(byte == PROTOCOL_SYNC) {
                parser->state = READ_CMD;
            }
            break;
        
        case READ_CMD:
            parser->frame.cmd = byte;
            parser->checksum = byte;
            parser->state = READ_LENGTH;
            break;

        case READ_LENGTH:
            if(byte > PROTOCOL_MAX_PAYLOAD) {
                protocol_parser_init(parser);
                break;
            }

            parser->frame.length = byte;
            parser->checksum ^= byte;
            parser->payload_index = 0;

            if(byte == 0) {
                parser->state = READ_CHECKSUM;
            } else {
                parser->state = READ_PAYLOAD;
            }
            break;

        case READ_PAYLOAD:
            parser->frame.payload[parser->payload_index] = byte;
            parser->checksum ^= byte;
            parser->payload_index++;

            if(parser->payload_index >= parser->frame.length) {
                parser->state = READ_CHECKSUM;
            }

            break;

        case READ_CHECKSUM:
            if(byte == parser->checksum) {
                *out_frame = parser->frame;
                protocol_parser_init(parser);
                return true;
            }    

            protocol_parser_init(parser);
            break;
        default:
            protocol_parser_init(parser);
            break;
    }

    return false;
}