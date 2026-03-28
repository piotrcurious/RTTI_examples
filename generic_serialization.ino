#include <RTTI.h>
#include <Arduino.h>

// A generic function to serialize any struct and print its hex
template <typename T>
void serializeAndPrint(const T& data) {
    byte buffer[sizeof(T)];
    int size = RTTI::serialize(buffer, data);

    Serial.print("Serialized size: ");
    Serial.println(size);
    Serial.print("Data: ");
    for (int i = 0; i < size; i++) {
        Serial.print(buffer[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}

struct SensorData {
    uint32_t timestamp;
    float temperature;
    float humidity;
};

struct Config {
    char deviceID[10];
    uint16_t interval;
    bool enabled;
};

void setup() {
    Serial.begin(9600);

    SensorData s = {1618234567, 22.5, 45.0};
    Config c = {"NODE-01", 60, true};

    Serial.println("--- Generic Serialization Example ---");

    Serial.println("Serializing SensorData:");
    serializeAndPrint(s);

    Serial.println("Serializing Config:");
    serializeAndPrint(c);
}

void loop() {
    // Empty
}
