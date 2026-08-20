#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#include "bit_flags.h"

static void test_initial_state(void) {
    uint32_t flags = 0;

    assert(!isFlagSet(flags, FLAG_ARMED));
    assert(!isFlagSet(flags, FLAG_GPS_AVAILABLE));
    assert(!isFlagSet(flags, FLAG_BATTERY_LOW));
}

static void test_set_flag(void) {
    uint32_t flags = 0;

    setFlag(&flags, FLAG_ARMED);

    assert(isFlagSet(flags, FLAG_ARMED));
    assert(!isFlagSet(flags, FLAG_BATTERY_LOW));
    assert(!isFlagSet(flags, FLAG_GPS_AVAILABLE));
}

static void test_multiple_flags_set(void) {
    uint32_t flags = 0;

    setFlag(&flags, FLAG_ARMED);
    setFlag(&flags, FLAG_BATTERY_LOW);
    setFlag(&flags, FLAG_GPS_AVAILABLE);

    assert(isFlagSet(flags, FLAG_ARMED));
    assert(isFlagSet(flags, FLAG_BATTERY_LOW));
    assert(isFlagSet(flags, FLAG_GPS_AVAILABLE));
    assert(!isFlagSet(flags, FLAG_FAILSAFE));
    assert(!isFlagSet(flags, FLAG_MOTORS_ENABLED));
}

static void test_clear_flag(void) {
    uint32_t flags = 0;

    setFlag(&flags, FLAG_ARMED);
    setFlag(&flags, FLAG_GPS_AVAILABLE);

    clearFlag(&flags, FLAG_GPS_AVAILABLE);

    assert(isFlagSet(flags, FLAG_ARMED));
    assert(!isFlagSet(flags, FLAG_GPS_AVAILABLE));
}

static void test_clear_flag_does_not_affect_other(void) {
    uint32_t flags = 0;

    setFlag(&flags, FLAG_ARMED);
    setFlag(&flags, FLAG_GPS_AVAILABLE);
    setFlag(&flags, FLAG_BATTERY_LOW);

    clearFlag(&flags, FLAG_GPS_AVAILABLE);

    assert(isFlagSet(flags, FLAG_ARMED));
    assert(!isFlagSet(flags, FLAG_GPS_AVAILABLE));
    assert(isFlagSet(flags, FLAG_BATTERY_LOW));
}

int main(void) {
    test_initial_state();
    test_set_flag();
    test_multiple_flags_set();
    test_clear_flag();
    test_clear_flag_does_not_affect_other();

    printf("All tests passed!\n");

    return 0;
}