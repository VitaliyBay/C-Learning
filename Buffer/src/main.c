#include <stdio.h>
#include <string.h>

char* buffer[7] = {"_", "_", "_", "_", "_", "_", "_"};

void printBuffer();
int pointer = 0;
char byte[] = "";

int main() {
    printBuffer();

    while (pointer != -1)
    {
        printf("Byte in position %i: ", pointer);
        scanf("%s", byte);

        if(strcmp(byte, "0") == 0) {
            pointer = -1;
            printf("\nExit");
            return 0;
        }
        
        buffer[pointer] = byte;

        pointer += 1;

        if(pointer > 7) {
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
        printf(" %s", buffer[i]);
    }
    printf("\n");
}