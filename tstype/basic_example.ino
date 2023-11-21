// Include the TSType library
#include <TSType.h>

// Define a struct with some fields
struct Person {
  int age;
  char name[20];
  bool married;
};

// Create a TSType object for the struct
TSType<Person> personType;

// Create a struct instance
Person person = {25, "Alice", true};

// A function to print the type and value of a field
void printField(TSTypeField field, void* value) {
  Serial.print(field.name); // Print the field name
  Serial.print(": ");
  Serial.print(field.type); // Print the field type
  Serial.print(" = ");
  // Print the field value based on the type
  switch (field.type) {
    case TS_INT:
      Serial.println(*((int*)value));
      break;
    case TS_CHAR:
      Serial.println(*((char*)value));
      break;
    case TS_BOOL:
      Serial.println(*((bool*)value) ? "true" : "false");
      break;
    case TS_CHAR_ARRAY:
      Serial.println((char*)value);
      break;
    default:
      Serial.println("Unknown type");
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  // Wait for the serial port to connect
  while (!Serial) {}
  // Print the struct type name
  Serial.print("Struct type: ");
  Serial.println(personType.name());
  // Print the number of fields
  Serial.print("Number of fields: ");
  Serial.println(personType.numFields());
  // Loop through the fields
  for (int i = 0; i < personType.numFields(); i++) {
    // Get the i-th field
    TSTypeField field = personType.getField(i);
    // Get the address of the field value
    void* value = personType.getFieldValue(&person, i);
    // Print the field information
    printField(field, value);
  }
}

void loop() {
  // Do nothing
}
