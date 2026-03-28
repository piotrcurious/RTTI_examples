import os
import subprocess

def run_test(ino_file):
    print(f"--- Testing {ino_file} ---")
    mock_main = "mock_arduino/src/mock_main.cpp"
    include_path = "mock_arduino/include"

    # Read the .ino file and merge it with mock_main
    with open(ino_file, 'r') as f:
        ino_content = f.read()

    with open(mock_main, 'r') as f:
        main_content = f.read()

    # Simple merge: ino first then main
    temp_cpp = "temp_test.cpp"
    with open(temp_cpp, 'w') as f:
        # Prepend Arduino.h if not there
        if "#include <Arduino.h>" not in ino_content and "#include \"Arduino.h\"" not in ino_content:
             f.write("#include \"Arduino.h\"\n")

        # Define MockESP8266WiFi if it's an ESP8266 example
        if "ESP8266WiFi" in ino_content:
            f.write("#define USE_ESP8266\n")

        f.write(ino_content)
        f.write("\n")
        f.write(main_content)

    # Compile
    cmd = ["g++", "-I" + include_path, "-o", "test_bin", temp_cpp]
    try:
        subprocess.run(cmd, check=True, stderr=subprocess.PIPE)
    except subprocess.CalledProcessError as e:
        print(f"Compilation FAILED for {ino_file}")
        print(e.stderr.decode())
        return False

    # Run
    try:
        subprocess.run(["./test_bin"], check=True)
        print(f"SUCCESS for {ino_file}")
        return True
    except subprocess.CalledProcessError as e:
        print(f"Runtime FAILED for {ino_file}")
        return False

def main():
    examples = [
        "pragma_enabled_rtti_serialize.ino",
        "pragma_enabled_deserialize_esp8266.ino",
        "pragma_enabled_rtti_deserialize.ino",
        "pragma_enabled_serialize_esp8266.ino",
        "struct_over_udp_arduino.ino",
        "struct_over_udp_esp8266.ino",
        "udp_to_struct_esp8266.ino",
        "tstype/basic_example.ino",
        "tstype/serialize_struct.ino",
        "tstype/serialize_to_JSON_neat.ino",
        "generic_serialization.ino",
        "command_processor.ino"
    ]

    for example in examples:
        run_test(example)

if __name__ == "__main__":
    main()
