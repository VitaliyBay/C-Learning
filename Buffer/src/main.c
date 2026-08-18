#include <stdio.h>
#include <stdint.h>

uint8_t buffer[7] = {0};

void printBuffer();
int pointer = 0;

int main() {
    printBuffer();

    while (1)
    {
        unsigned int value;

        printf("Byte in position %d (hex, 0 to exit): 0x", pointer);
        
        if(scanf("%x", &value) != 1) {
            printf("Invalid input\n");
            return 1;
        }

        if(value == 0) {
            printf("\nExit");
            return 0;
        }

        if(value > 0xFF) {
            printf("Value must be between 0x00 and 0xFF\n");
            continue;
        }

        buffer[pointer] = (uint8_t)value;

        pointer += 1;
 
        if(pointer >= 7) {
            pointer = 0;
            printf("\nReset pinter %i to position 0\n", pointer);
        }

        printBuffer();
    }
    

    return 0;
}

void printBuffer() {
    printf("Buffer:");
    for (int i = 0; i < 7; i++)
    {
        printf(" 0x%02X", buffer[i]);
    }
    printf("\n");
}