#include <stdio.h>
#include <string.h>

typedef enum {
    COMMAND_INVALID = -1,
    COMMAND_DISARM = 0,
    COMMAND_ARM = 1,
    COMMAND_TAKEOFF = 2,
    COMMAND_LOITER = 3,
    COMMAND_LAND = 4,
    COMMAND_EXIT = 5
} Command;

typedef enum {
    FLIGHT_MODE_INVALID = -1,
    FLIGHT_MODE_DISARMED = 0,
    FLIGHT_MODE_ARMED = 1,
    FLIGHT_MODE_TAKEOFF = 2,
    FLIGHT_MODE_LOITER = 3,
    FLIGHT_MODE_LAND = 4,
    FLIGHT_MODE_EXITING = 5,
} FlightMode;

int validateInput(char *input);

Command getCurrentCommand(char *inputText);
char *commandToString(Command command);

FlightMode getCurrentMode(char *inputText);
char *modeToString(FlightMode mode);

int validateCommand(Command command);

int main() {
    Command currentCommand = COMMAND_DISARM;
    FlightMode currentMode = FLIGHT_MODE_DISARMED;
    char inputText[10] = {"asd"};

    while(currentCommand != COMMAND_EXIT) {
        printf("Command: ");
        scanf("%s", inputText);
        printf("Your command %s\n", inputText);

        int result = validateInput(inputText);

        if(result == 1) {
            printf("Invalid command %s, try again\n", inputText);
            continue;
        }

        currentCommand = getCurrentCommand(inputText);
        currentMode = getCurrentMode(inputText);

        printf("Let's go with %s, current mode is %s\n", commandToString(currentCommand), modeToString(currentMode));
    }
    return 0;
}

int validateInput(char *input) {
    if(strcmp(input, "DISARM") == 0 || strcmp(input, "disarm") == 0) {
        return 0;
    }
    if(strcmp(input, "ARM") == 0 || strcmp(input, "arm") == 0) {
        return 0;
    }
    if(strcmp(input, "TAKEOFF") == 0 || strcmp(input, "takeoff") == 0) {
        return 0;
    }
    if(strcmp(input, "LOITER") == 0 || strcmp(input, "loiter") == 0) {
        return 0;
    }
    if(strcmp(input, "LAND") == 0 || strcmp(input, "land") == 0) {
        return 0;
    }
    if(strcmp(input, "EXIT") == 0 || strcmp(input, "exit") == 0) {
        return 0;
    }

    return 1;
}

Command getCurrentCommand(char *inputText) {
    if(strcmp(inputText, "DISARM") == 0 || strcmp(inputText, "disarm") == 0) {
        return COMMAND_DISARM;
    }
    if(strcmp(inputText, "ARM") == 0 || strcmp(inputText, "arm") == 0) {
        return COMMAND_ARM;
    }
    if(strcmp(inputText, "TAKEOFF") == 0 || strcmp(inputText, "takeoff") == 0) {
        return COMMAND_TAKEOFF;
    }
    if(strcmp(inputText, "LOITER") == 0 || strcmp(inputText, "loiter") == 0) {
        return COMMAND_LOITER;
    }
    if(strcmp(inputText, "LAND") == 0 || strcmp(inputText, "land") == 0) {
        return COMMAND_LAND;
    }
    if(strcmp(inputText, "EXIT") == 0 || strcmp(inputText, "exit") == 0) {
        return COMMAND_EXIT;
    }

    return COMMAND_INVALID;
}

char *commandToString(Command command) {
    switch (command)
    {
        case COMMAND_DISARM:
            return "DISARM";
        case COMMAND_ARM:
            return "ARM";
        case COMMAND_TAKEOFF:
            return "TAKEOFF";
        case COMMAND_LOITER:
            return "LOITER";
        case COMMAND_LAND:
            return "LAND";
        case COMMAND_EXIT:
            return "EXIT";
        case COMMAND_INVALID:
            return "INVALID";
        
        default:
            return "INVALID";
    }
}

FlightMode getCurrentMode(char *inputText) {
    if(strcmp(inputText, "DISARM") == 0 || strcmp(inputText, "disarm") == 0) {
        return FLIGHT_MODE_DISARMED;
    }
    if(strcmp(inputText, "ARM") == 0 || strcmp(inputText, "arm") == 0) {
        return FLIGHT_MODE_ARMED;
    }
    if(strcmp(inputText, "TAKEOFF") == 0 || strcmp(inputText, "takeoff") == 0) {
        return FLIGHT_MODE_TAKEOFF;
    }
    if(strcmp(inputText, "LOITER") == 0 || strcmp(inputText, "loiter") == 0) {
        return FLIGHT_MODE_LOITER;
    }
    if(strcmp(inputText, "LAND") == 0 || strcmp(inputText, "land") == 0) {
        return FLIGHT_MODE_LAND;
    }
    if(strcmp(inputText, "EXIT") == 0 || strcmp(inputText, "exit") == 0) {
        return FLIGHT_MODE_EXITING;
    }

    return FLIGHT_MODE_INVALID;
}

char *modeToString(FlightMode mode) {
    switch (mode)
    {
        case FLIGHT_MODE_DISARMED:
            return "DISARMED";
        case FLIGHT_MODE_ARMED:
            return "ARMED";
        case FLIGHT_MODE_TAKEOFF:
            return "TAKEOFF";
        case FLIGHT_MODE_LOITER:
            return "LOITER";
        case FLIGHT_MODE_LAND:
            return "LAND";
        case FLIGHT_MODE_INVALID:
            return "INVALID";
        case FLIGHT_MODE_EXITING:
            return "EXITING";
        
        default:
            return "INVALID";
    }
}