
// Enable RTTI with a pragma directive
#pragma GCC diagnostic ignored "-fno-rtti"

// Include necessary libraries
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Define a struct example
struct example {
  int a;
  float b;
  char c;
};

// Declare an instance of the struct
example myVar;

// Declare a UDP object
WiFiUDP Udp;

// Declare a local port and a broadcast IP address
unsigned int localPort = 2000;
IPAddress broadcastIP(192,168,4,255);

// Define your WiFi credentials
const char* ssid = "yourNetwork";
const char* password = "yourPassword";

// Setup function
void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to wifi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start UDP communication
  Udp.begin(localPort);
}

// Loop function
void loop() {
  // Serialize the struct using RTTI and dynamic_cast
  byte buffer[sizeof(example)];
  byte* p = buffer;
  for (int i = 0; i < sizeof(example); i++) {
    void* v = static_cast<void*>(&myVar);
    byte* b = dynamic_cast<byte*>(v);
    *p++ = b[i];
  }

  // Send the buffer as a UDP broadcast packet
  Udp.beginPacket(broadcastIP, localPort);
  Udp.write(buffer, sizeof(example));
  Udp.endPacket();
}

 
