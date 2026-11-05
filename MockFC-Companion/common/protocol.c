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
    return false;
}