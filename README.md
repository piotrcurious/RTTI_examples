# RTTI_examples

This repository contains examples of using RTTI (Run-Time Type Information) and serialization techniques in Arduino and ESP8266 environments.

## Examples

- `generic_serialization.ino`: (New) Showcases a generic template function to serialize various struct types.
- `command_processor.ino`: (New) Simulates a command processing system using RTTI for deserializing incoming packets.
- `pragma_enabled_*.ino`: Examples of using pragma directives to enable RTTI and manual serialization/deserialization.
- `struct_over_udp_*.ino`: Sending structs over UDP using RTTI.
- `tstype/*.ino`: Using the `TSType` library for struct introspection and JSON serialization.

## Testing with Mock Environment

A mock Arduino environment is provided for testing these examples on a host machine.

To run the tests:
1. Ensure you have `g++` and `python3` installed.
2. Run `python3 run_tests.py`.

The mock environment files are located in `mock_arduino/`.

## Fixes Applied

- Fixed invalid `dynamic_cast` usage in several examples.
- Added missing include directives.
- Added forward declarations for event handlers.
- Corrected various compilation errors found during testing.
