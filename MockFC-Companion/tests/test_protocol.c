#include <stdio.h>
#include <assert.h>
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

int main() {
    // protocol_parser_init
    test_protocol_parser_init_returns_valid_parser_state();

    printf("[PROTOCOL] All test passed!");
    
    return 0;
}