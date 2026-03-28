// Include the TSType library
#include <TSType.h>

// Define a struct with some fields
struct Person {
  int32_t age;
  char name[20];
  bool married;
} __attribute__((packed));

// Create a TSType object for the struct
TSType<Person> personType;

// Create a struct instance
Person person = {25, "Alice", true};

// A function to serialize the struct into a buffer (Portability improved)
void serializeStruct(TSType<Person> type, Person* data, byte* buffer, int* size) {
  // Initialize the buffer size to zero
  *size = 0;
  // Loop through the fields
  for (int i = 0; i < type.numFields(); i++) {
    // Get the i-th field
    TSTypeField field = type.getField(i);
    // Get the address of the field value
    void* value = type.getFieldValue(data, i);

    // For integers, handle byte order explicitly (e.g. Little Endian)
    if (field.type == TS_INT && field.size == 4) {
      int32_t val = *((int32_t*)value);
      buffer[*size + 0] = (val >> 0) & 0xFF;
      buffer[*size + 1] = (val >> 8) & 0xFF;
      buffer[*size + 2] = (val >> 16) & 0xFF;
      buffer[*size + 3] = (val >> 24) & 0xFF;
    } else {
      // For other types, copy byte-by-byte
      for (int j = 0; j < field.size; j++) {
        buffer[*size + j] = ((byte*)value)[j];
      }
    }
    // Increment the buffer size by the field size
    *size += field.size;
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  // Wait for the serial port to connect
  while (!Serial) {}
  // Create a buffer to store the serialized data
  byte buffer[100];
  // Create a variable to store the buffer size
  int size;
  // Serialize the struct into the buffer
  serializeStruct(personType, &person, buffer, &size);
  // Print the buffer size
  Serial.print("Buffer size: ");
  Serial.println(size);
  // Print the buffer contents in hexadecimal format
  Serial.print("Buffer contents: ");
  for (int i = 0; i < size; i++) {
    // Print a leading zero if the byte is less than 16
    if (buffer[i] < 16) {
      Serial.print("0");
    }
    // Print the byte in hexadecimal
    Serial.print(buffer[i], HEX);
    // Print a space after each byte
    Serial.print(" ");
  }
  // Print a new line
  Serial.println();
}

void loop() {
  // Do nothing
}
