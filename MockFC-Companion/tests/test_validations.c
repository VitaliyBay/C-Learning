#include <assert.h>
#include <stdio.h>
#include "validations.h"

static void test_gps_coordinates_valid_with_latitude_deg_lower_that_negative_90() {
    double latitude_deg = -91;
    double longitude_deg = 0;

    assert(gps_coordinates_valid(latitude_deg, longitude_deg) == false);
}

static void test_gps_coordinates_valid_with_latitude_deg_greater_that_90() {
    double latitude_deg = 91;
    double longitude_deg = 0;

    assert(gps_coordinates_valid(latitude_deg, longitude_deg) == false);
}

static void test_gps_coordinates_valid_with_latitude_deg_valid() {
    double latitude_deg = 15;
    double longitude_deg = 51;

    assert(gps_coordinates_valid(latitude_deg, longitude_deg) == true);
}

static void test_rc_value_valid_with_value_lower_than_1000() {
    uint16_t value = 999;

    assert(rc_value_valid(value) == false);
}

static void test_rc_value_valid_with_value_greater_than_2000() {
    uint16_t value = 2001;

    assert(rc_value_valid(value) == false);
}

static void test_rc_value_valid_with_value_between_1000_and_2000() {
    uint16_t value = 1500;

    assert(rc_value_valid(value) == true);
}

static void test_gps_satelites_valid_with_negative_value() {
    uint8_t satelites = -1;

    assert(gps_satelites_valid(satelites) == false);
}

static void test_gps_satelites_valid_with_value_greater_than_32() {
    uint8_t satelites = 35;

    assert(gps_satelites_valid(satelites) == false);
}

static void test_gps_satelites_valid_with_correct_value() {
    uint8_t satelites = 12;

    assert(gps_satelites_valid(satelites) == true);
}

static void test_battery_voltage_valid_with_negative_value() {
    float voltage = -1;

    assert(battery_voltage_valid(voltage) == false);
}

static void test_battery_voltage_valid_with_value_greater_than_30() {
    float voltage = 35;

    assert(battery_voltage_valid(voltage) == false);
}

static void test_battery_voltage_valid_with_correct_value() {
    float voltage = 12;

    assert(battery_voltage_valid(voltage) == true);
}

static void test_attitude_valid_roll_deg_with_invalid_negative_value() {
    Attitude attitude_with_invalid_negative_value = {
        .roll_deg = -190,
        .pitch_deg = 0,
        .yaw_deg = 0
    };

    assert(attitude_valid(attitude_with_invalid_negative_value) == false);
}

static void test_attitude_valid_roll_deg_with_invalid_positive_value() {
    Attitude attitude_with_invalid_positive_value = {
        .roll_deg = 190,
        .pitch_deg = 0,
        .yaw_deg = 0
    };

    assert(attitude_valid(attitude_with_invalid_positive_value) == false);
}

static void test_attitude_valid_pitch_deg_with_invalid_negative_value() {
    Attitude attitude_with_invalid_negative_value = {
        .roll_deg = 0,
        .pitch_deg = -190,
        .yaw_deg = 0
    };

    assert(attitude_valid(attitude_with_invalid_negative_value) == false);
}

static void test_attitude_valid_pitch_deg_with_invalid_positive_value() {
    Attitude attitude_with_invalid_positive_value = {
        .roll_deg = 0,
        .pitch_deg = 190,
        .yaw_deg = 0
    };

    assert(attitude_valid(attitude_with_invalid_positive_value) == false);
}

int main(void) {
    // gps_coordinates_valid
    test_gps_coordinates_valid_with_latitude_deg_lower_that_negative_90();
    test_gps_coordinates_valid_with_latitude_deg_greater_that_90();
    test_gps_coordinates_valid_with_latitude_deg_valid();

    // rc_value_valid
    test_rc_value_valid_with_value_lower_than_1000();
    test_rc_value_valid_with_value_greater_than_2000();
    test_rc_value_valid_with_value_between_1000_and_2000();

    // gps_satelites_valid
    test_gps_satelites_valid_with_negative_value();
    test_gps_satelites_valid_with_value_greater_than_32();
    test_gps_satelites_valid_with_correct_value();

    // attitude_valid tests
    test_attitude_valid_roll_deg_with_invalid_negative_value();
    test_attitude_valid_roll_deg_with_invalid_positive_value();
    test_attitude_valid_pitch_deg_with_invalid_negative_value();
    test_attitude_valid_pitch_deg_with_invalid_positive_value();

    // battery_voltage_valid
    test_battery_voltage_valid_with_negative_value();
    test_battery_voltage_valid_with_value_greater_than_30();
    test_battery_voltage_valid_with_correct_value();

    printf("All tests passed!\n");

    return 0;
}