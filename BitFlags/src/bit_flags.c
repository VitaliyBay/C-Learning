#include "bit_flags.h"
#include <stdint.h>
#include <stdbool.h>

void setFlag(uint32_t *flags, uint32_t flag) {
    *flags |= flag;
}

void clearFlag(uint32_t *flags, uint32_t flag) {
    *flags &= ~flag;
}

bool isFlagSet(uint32_t flags, uint32_t flag) {
    return (flags & flag) != 0;
}