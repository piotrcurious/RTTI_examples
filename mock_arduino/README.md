# Mock Arduino Environment

This mock environment is designed to test Arduino sketches on a host machine using `g++`.

## Portability Assumptions

- **Architecture:** The host machine is assumed to be Little Endian, matching most common Arduino boards (AVR, SAMD, ESP32, ESP8266).
- **Data Type Sizes:**
    - `int`: 4 bytes (simulating 32-bit platforms like ESP32/ESP8266).
    - `float`: 4 bytes (IEEE 754).
    - `char`: 1 byte.
    - `bool`: 1 byte.

**Note:** When developing for 8-bit AVR boards (e.g., Arduino Uno), keep in mind that `int` is 2 bytes. Use fixed-width types like `int16_t` or `int32_t` from `<cstdint>` for portability across architectures.

## Mock Features

- **Serial:** Basic `print` and `println` support.
- **WiFi/UDP:** Minimal mock that simulates successful connection and packet handling.
- **RTTI/TSType:** Custom simplified implementations to support serialization examples.
- **Arduino_JSON:** A minimal `JSONVar` class for JSON-related examples.
