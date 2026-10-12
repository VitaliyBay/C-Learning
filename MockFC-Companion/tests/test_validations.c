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

int main(void) {
    test_gps_coordinates_valid_with_latitude_deg_lower_that_negative_90();
    test_gps_coordinates_valid_with_latitude_deg_greater_that_90();
    test_gps_coordinates_valid_with_latitude_deg_valid();

    printf("All tests passed!\n");

    return 0;
}