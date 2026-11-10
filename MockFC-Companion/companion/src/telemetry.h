#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>

void create_attitude_request(uint8_t *buffer, size_t capacity, size_t *length);
void process_attitude_response(); // TODO: Add parameters

#endif // TELEMENTRY_H