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

void test_protocol_parser_ingest_oversize_payload_length() {
    ProtocolParser parser;
    ProtocolFrame frame;

    protocol_parser_init(&parser);

    uint8_t input[] = {
        0x24,               // SYNC
        0x01,               // CMD
        65,               // LENGTH (> than PROTOCOL_MAX_PAYLOAD)
    };

    bool complete = false;
    for(size_t i = 0; i < sizeof(input); i++) {
        complete = protocol_parser_ingest(&parser, input[i], &frame);
    }

    assert(complete == false);
    assert(parser.state == WAIT_SYNC);
}

void test_protocol_parser_ingest_two_frames_in_strem() {
    ProtocolParser parser;
    ProtocolFrame frame;

    protocol_parser_init(&parser);

    uint8_t input[] = {
        0x24,   // SYNC 1
        0x01,   // CMD 1
        0x00,   // LENGTH 1
        0x01,   // CHECKSUM 1
        // ----------------------
        0x24,   // SYNC 2
        0x02,   // CMD 2
        0x00,   // LENGTH 2
        0x02,   // CHECKSUM 2     
    };

    int completed_frame_count = 0;
    for(size_t i = 0; i < sizeof(input); i++) {
        if(protocol_parser_ingest(&parser, input[i], &frame)) {
            completed_frame_count++;
        }
    }

    assert(completed_frame_count == 2);
}

void test_protocol_parser_ingest_maximum_payload() {
    ProtocolParser parser;
    ProtocolFrame frame;

    protocol_parser_init(&parser);

    assert(protocol_parser_ingest(&parser, PROTOCOL_SYNC, &frame) == false);
    assert(protocol_parser_ingest(&parser, 0x01, &frame) == false);
    assert(protocol_parser_ingest(&parser, PROTOCOL_MAX_PAYLOAD, &frame) == false);

    uint8_t checksum = 0x01 ^ PROTOCOL_MAX_PAYLOAD;

    for(size_t i = 0; i < PROTOCOL_MAX_PAYLOAD; i++) {
        checksum ^= i;
        assert(protocol_parser_ingest(&parser, i, &frame) == false);
    }

    assert(protocol_parser_ingest(&parser, checksum, &frame) == true);
    
    assert(frame.cmd == 0x01);
    assert(frame.length == PROTOCOL_MAX_PAYLOAD);
    assert(frame.payload[0] == 0);
    assert(frame.payload[32] == 32);
    assert(frame.payload[63] == 63);
}

int main() {
    // protocol_parser_init
    test_protocol_parser_init_returns_valid_parser_state();

    // protocol_parser_ingest
    test_protocol_parser_ingest_when_valid_frame();
    test_protocol_parser_ingest_skip_noise_bytes();
    test_protocol_parser_ingest_oversize_payload_length();
    test_protocol_parser_ingest_two_frames_in_strem();
    test_protocol_parser_ingest_maximum_payload();

    printf("[PROTOCOL] All test passed!");
    
    return 0;
}