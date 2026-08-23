#include <Arduino.h>

#define FC_RX_PIN 16
#define FC_TX_PIN 17
#define MSP_STATUS 101
#define MSP_ANALOG 110

HardwareSerial FCSerial(2);

void sendMCP(uint8_t command) {
  uint8_t checksum = command;

  // MCP v1 package:
  // $ M < data_length command checksum

  FCSerial.write('$');
  FCSerial.write('M');
  FCSerial.write('<');

  // Payload length = 0
  FCSerial.write((uint8_t)0);

  // Command
  FCSerial.write(command);

  // Checksum
  FCSerial.write(checksum);
}

bool readMSP(uint8_t &command, uint8_t *payload, uint8_t &payloadSize) {
  // Find '$'
  if (FCSerial.read() != '$') {
    return false;
  }

  if (FCSerial.read() != 'M') {
    return false;
  }

  if (FCSerial.read() != '>') {
    return false;
  }

  uint8_t size = FCSerial.read();
  uint8_t cmd = FCSerial.read();

  uint8_t checkSum = size ^ cmd;

  for (uint8_t i = 0; i < size; i++) {
    payload[i] = FCSerial.read();
    checkSum ^= payload[i];
  }

  uint8_t receivedChecksum = FCSerial.read();

  if (checkSum != receivedChecksum) {
    Serial.println("Checksum error!");
    return false;
  }

  command = cmd;
  payloadSize = size;

  return true;
}

void setup() {
  Serial.begin(115200);

  FCSerial.begin(115200, SERIAL_8N1, FC_RX_PIN, FC_TX_PIN);

  Serial.println("ESP32 started!");
  Serial.println("FC UART initialized 2");
}

void loop() {
  
  Serial.println("Init loop");
  //Ask FC for battery/status information
  sendMCP(MSP_ANALOG);

  delay(100);

  uint8_t command;
  uint8_t payload[64];
  uint8_t payloadSize;

  if (readMSP(command, payload, payloadSize)) {
    Serial.print("Received MSP command: ");
    Serial.println(command);

    Serial.print("Payload size: ");
    Serial.println(payloadSize);

    Serial.print("Data: ");

    for (uint8_t i = 0; i < payloadSize; i++) {
      Serial.printf("%02X ", payload[i]);
    }

    Serial.println();

    // MSP_ANALOG:
    // first byte = battery voltage / 10

    if(command == MSP_ANALOG && payloadSize >= 1) {
      float voltage = payload[0] / 10.0f;

      Serial.print("Battery voltage: ");
      Serial.print(voltage);
      Serial.println(" V");
    }
  }

  delay(1000);
}