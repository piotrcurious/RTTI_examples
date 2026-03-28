// Include the TSType and Arduino_JSON libraries
#include <TSType.h>
#include <Arduino_JSON.h>

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

// A function to serialize the struct into a JSON object using TSType
JSONVar serializeToJson(TSType<Person> type, Person* data) {
  // Create a JSON object
  JSONVar json;
  // Loop through the fields
  for (int i = 0; i < type.numFields(); i++) {
    // Get the i-th field
    TSTypeField field = type.getField(i);
    // Get the address of the field value
    void* value = type.getFieldValue(data, i);
    // Set the field name and value in the JSON object based on the type
    switch (field.type) {
      case TS_INT:
        json[field.name] = *((int32_t*)value);
        break;
      case TS_FLOAT:
        json[field.name] = *((float*)value);
        break;
      case TS_CHAR:
        json[field.name] = *((char*)value);
        break;
      case TS_BOOL:
        json[field.name] = *((bool*)value);
        break;
      case TS_CHAR_ARRAY:
        json[field.name] = (char*)value;
        break;
      default:
        json[field.name] = "null";
    }
  }
  // Return the JSON object
  return json;
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  // Wait for the serial port to connect
  while (!Serial) {}

  // Serialize the struct into a JSON object using TSType
  JSONVar json = serializeToJson(personType, &person);

  // Print the JSON object
  Serial.print("JSON: ");
  Serial.println(json);
}

void loop() {
  // Do nothing
}
