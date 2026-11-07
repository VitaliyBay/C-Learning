#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include "protocol.h" 

// protocol_parser_init
void test_protocol_parser_init_returns_valid_parser_state() {
    ProtocolParser parser = {
        .state = READ_CHECKSUM
    };

    protocol_parser_init(&parser);

    assert(parser.state == WAIT_SYNC && "Valid Parser state");
}

// protocol_parser_ingest
void test_protocol_parser_ingest_when_valid_frame() {
    ProtocolParser parser;
    ProtocolFrame frame;

    protocol_parser_init(&parser);

    uint8_t input[] = {
        0x24,   // SYNC
        0x03,   // CMD
        0x05,   // LENGTH
        0xAA,   // PAYLOAD
        0xBB,
        0xCC,
        0xDD,
        0xEE,
        0xE8    // CHECKSUM 0x03 ^ 0x05 ^ 0xAA ^ 0xBB ^ 0xCC ^ 0xDD ^ 0xEE
    };

    for(size_t i = 0; i < sizeof(input); i++) {
        bool complete = protocol_parser_ingest(&parser, input[i], &frame);

        if(i < sizeof(input) - 1) {
            assert(complete == false && "Ingest is not completed");
        } else {
            assert(complete == true && "Ingest is completed");
        }
    }

    assert(frame.cmd == 0x03);
    assert(frame.length == 5);
    assert(frame.payload[0] == 0xAA);
    assert(frame.payload[1] == 0xBB);
    assert(frame.payload[2] == 0xCC);
    assert(frame.payload[3] == 0xDD);
    assert(frame.payload[4] == 0xEE);
}

void test_protocol_parser_ingest_skip_noise_bytes() {
    ProtocolParser parser;
    ProtocolFrame frame;

    protocol_parser_init(&parser);

    uint8_t input[] = {
        0x33, 0x21, 0x58,   // NOISE
        0x24,               // SYNC
        0x01,               // CMD
        0x00,               // LENGTH
        0x01                // CHECKSUM
    };

    bool complete = false;
    for(size_t i = 0; i < sizeof(input); i++) {
        complete = protocol_parser_ingest(&parser, input[i], &frame);
    }

    assert(complete == true);
    assert(frame.cmd == 0x01);
    assert(frame.length == 0x00);
}

int main() {
    // protocol_parser_init
    test_protocol_parser_init_returns_valid_parser_state();

    // protocol_parser_ingest
    test_protocol_parser_ingest_when_valid_frame();
    test_protocol_parser_ingest_skip_noise_bytes();

    printf("[PROTOCOL] All test passed!");
    
    return 0;
}