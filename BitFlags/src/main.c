#include <stdio.h>
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

static void printBinary(uint32_t flags) {
    for(int i = 31; i >= 0; i--) {
        printf("%d", (flags >> i) & 1);

        if(i % 8 == 0 && i != 0) {
            printf(" ");
        }
    }

    printf("\n");
}

static void printStatus(uint32_t flags) {
    printf("Flags: ");
    printBinary(flags);

    printf("Armed %s\n", isFlagSet(flags, FLAG_ARMED) ? "true" : "false");
    
    printf("GPS_AVAILABLE %s\n", isFlagSet(flags, FLAG_GPS_AVAILABLE) ? "true" : "false");
    
    printf("BATTERY_LOW %s\n", isFlagSet(flags, FLAG_BATTERY_LOW) ? "true" : "false");
    
    printf("GPS_HOME_SET %s\n", isFlagSet(flags, FLAG_GPS_HOME_SET) ? "true" : "false");
    
    printf("FAILSAFE %s\n", isFlagSet(flags, FLAG_FAILSAFE) ? "true" : "false");
    
    printf("MOTORS_ENABLED %s\n", isFlagSet(flags, FLAG_MOTORS_ENABLED) ? "true" : "false");
}

int main() {

    uint32_t flags = 0;

    printf("\nStart\n");
    printStatus(flags);

    printf("\n\nArming UAV....\n");
    setFlag(&flags, FLAG_ARMED);
    printStatus(flags);

    printf("\n\nGPS available...\n");
    setFlag(&flags, FLAG_GPS_AVAILABLE);
    printStatus(flags);

    printf("\n\nBattery low...\n");
    setFlag(&flags, FLAG_BATTERY_LOW);
    printStatus(flags);

    printf("\n\nDisarming UAV...\n");
    clearFlag(&flags, FLAG_ARMED);
    printStatus(flags);

    return 0;
}

void setFlag(uint32_t *flags, uint32_t flag) {
    *flags |= flag;
}

void clearFlag(uint32_t *flags, uint32_t flag) {
    *flags &= ~flag;
}

bool isFlagSet(uint32_t flags, uint32_t flag) {
    return (flags & flag) != 0;
}