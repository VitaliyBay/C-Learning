#ifndef BIT_FLAGS_H
#define BIT_FLAGS_H

#include <stdint.h>
#include <stdbool.h>

#define FLAG_ARMED           (1u << 0)
#define FLAG_GPS_AVAILABLE   (1u << 1)
#define FLAG_BATTERY_LOW     (1u << 2)
#define FLAG_GPS_HOME_SET    (1u << 3)
#define FLAG_FAILSAFE        (1u << 4)
#define FLAG_MOTORS_ENABLED  (1u << 5)

void setFlag(uint32_t *flags, uint32_t flag);
void clearFlag(uint32_t *flags, uint32_t flag);
bool isFlagSet(uint32_t flags, uint32_t flag);

#endif