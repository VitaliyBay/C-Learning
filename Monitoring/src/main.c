 #include <stdio.h>

typedef struct {
    float battery_voltage;
    int gps_satellites;
    float altitude;
    float roll;
    float pitch;
    int throttle;
    int armed;
} DroneTelemetry;

int main() {
    printf("Hello, World!\n");
    DroneTelemetry telemetry[] = {
        {24.6f, 12, 0.0f, 0.0f, 0.0f, 0, 0},
        {24.3f, 12, 2.5f, 1.2f, -0.5f, 30, 1},
        {23.8f, 11, 45.0f, 4.2f, -2.1f, 55, 1},
        {20.7f, 10, 50.0f, 5.0f, 1.0f, 60, 1},
        {22.1f, 5, 48.0f, 38.0f, 5.0f, 70, 1}
    };
    int length = sizeof(telemetry) / sizeof(telemetry[0]);
    for(int i = 1; i <= length; i++) {
        printf("---- Telementry #%d ----\n", i);
    }

    return 0;
}