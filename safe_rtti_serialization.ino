#include <RTTI.h>
#include <Arduino.h>

// This example demonstrates how to use the improved RTTI library
// to serialize fixed-width types in a portable way.

struct DeviceStatus {
    int32_t uptime;
    int16_t temperature;
    uint8_t flags;
} __attribute__((packed));

void serializeDeviceStatus(byte* buffer, const DeviceStatus& status) {
    int offset = 0;
    offset += RTTI::serializeInt32(buffer + offset, status.uptime);
    offset += RTTI::serializeInt16(buffer + offset, status.temperature);
    buffer[offset++] = status.flags;
}

void deserializeDeviceStatus(const byte* buffer, DeviceStatus& status) {
    int offset = 0;
    RTTI_DESERIALIZE_INT32(buffer + offset, status.uptime);
    offset += 4;
    RTTI_DESERIALIZE_INT16(buffer + offset, status.temperature);
    offset += 2;
    status.flags = buffer[offset++];
}

void setup() {
    Serial.begin(9600);

    DeviceStatus myStatus = {86400, 42, 0xAB};
    byte buffer[7]; // 4 + 2 + 1 = 7

    Serial.println("--- Safe RTTI Serialization ---");

    serializeDeviceStatus(buffer, myStatus);

    Serial.print("Buffer: ");
    for (int i = 0; i < 7; i++) {
        Serial.print(buffer[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    DeviceStatus received;
    deserializeDeviceStatus(buffer, received);

    Serial.print("Uptime: ");
    Serial.println((int)received.uptime);
    Serial.print("Temperature: ");
    Serial.println((int)received.temperature);
    Serial.print("Flags: ");
    Serial.println((int)received.flags, HEX);
}

void loop() {}
