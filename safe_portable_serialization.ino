#include <Arduino.h>

// This example demonstrates manual byte-by-byte serialization
// which is the most portable way to handle data across different
// architectures (e.g., 8-bit AVR, 32-bit ESP32, 64-bit PC).
// It explicitly handles endianness (Little Endian in this case).

struct PortableData {
    uint32_t id;
    int16_t value;
    char label[8];
};

void serializePortable(byte* buf, const PortableData& data) {
    // uint32_t id
    buf[0] = (data.id >> 0) & 0xFF;
    buf[1] = (data.id >> 8) & 0xFF;
    buf[2] = (data.id >> 16) & 0xFF;
    buf[3] = (data.id >> 24) & 0xFF;

    // int16_t value
    buf[4] = (data.value >> 0) & 0xFF;
    buf[5] = (data.value >> 8) & 0xFF;

    // char label[8]
    for (int i = 0; i < 8; i++) {
        buf[6 + i] = data.label[i];
    }
}

void deserializePortable(const byte* buf, PortableData& data) {
    // uint32_t id
    data.id = ((uint32_t)buf[0] << 0) |
              ((uint32_t)buf[1] << 8) |
              ((uint32_t)buf[2] << 16) |
              ((uint32_t)buf[3] << 24);

    // int16_t value
    data.value = (int16_t)(((uint16_t)buf[4] << 0) |
                           ((uint16_t)buf[5] << 8));

    // char label[8]
    for (int i = 0; i < 8; i++) {
        data.label[i] = buf[6 + i];
    }
}

void setup() {
    Serial.begin(9600);

    PortableData original = {0x12345678, -100, "Hello"};
    byte buffer[14]; // 4 + 2 + 8 = 14

    Serial.println("--- Safe Portable Serialization ---");

    serializePortable(buffer, original);

    Serial.print("Serialized Bytes: ");
    for (int i = 0; i < 14; i++) {
        Serial.print(buffer[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    PortableData received;
    deserializePortable(buffer, received);

    Serial.print("Deserialized ID: ");
    Serial.println((int)received.id, HEX);
    Serial.print("Deserialized Value: ");
    Serial.println(received.value);
    Serial.print("Deserialized Label: ");
    Serial.println(received.label);
}

void loop() {}
