#include <Arduino.h>
#include <RTTI.h>

struct Command {
    uint8_t cmd_id;
    int16_t arg1;
    int16_t arg2;
};

void processCommand(const Command& cmd) {
    Serial.print("Processing command ID: ");
    Serial.println(cmd.cmd_id);
    Serial.print("Arg1: ");
    Serial.println(cmd.arg1);
    Serial.print("Arg2: ");
    Serial.println(cmd.arg2);

    switch(cmd.cmd_id) {
        case 1: Serial.println("Executing: Move Motor"); break;
        case 2: Serial.println("Executing: Read Analog"); break;
        default: Serial.println("Unknown command");
    }
}

void setup() {
    Serial.begin(9600);

    // Simulate receiving a command over "serial" or "UDP"
    Command incoming;
    incoming.cmd_id = 1;
    incoming.arg1 = 100;
    incoming.arg2 = -50;

    byte packet[sizeof(Command)];
    RTTI::serialize(packet, incoming);

    Serial.println("--- Command Processor Simulation ---");
    Serial.print("Incoming packet bytes: ");
    for(int i=0; i<sizeof(Command); i++) {
        Serial.print(packet[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    // Deserialize and execute
    Command received;
    RTTI::deserialize(packet, received);
    processCommand(received);
}

void loop() {
}
