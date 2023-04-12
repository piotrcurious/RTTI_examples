
// Enable RTTI with a pragma directive
#pragma GCC diagnostic ignored "-fno-rtti"

// Include necessary libraries
#include <SPI.h>
#include <WiFi.h>
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

// Setup function
void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Connect to WiFi network
  WiFi.begin("ssid", "password");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to wifi");

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


//Source: Conversation with Bing, 4/12/2023(1) Send and Receive UDP String | Arduino Documentation. https://docs.arduino.cc/library-examples/wifi-library/WiFiUdpSendReceiveString/ Accessed 4/12/2023.
//(2) arduino - Broadcasting messages via UDP over esp8266 - Stack Overflow. https://stackoverflow.com/questions/56438049/broadcasting-messages-via-udp-over-esp8266 Accessed 4/12/2023.
//(3) Simple code to send a struct between Arduinos using Serial. https://forum.arduino.cc/t/simple-code-to-send-a-struct-between-arduinos-using-serial/672196 Accessed 4/12/2023.
//(4) Arduino Zero: Enable RTTI - Arduino Stack Exchange. https://arduino.stackexchange.com/questions/37491/arduino-zero-enable-rtti Accessed 4/12/2023.
//(5) serial - How to retrieve the data type of a variable? - Arduino Stack .... https://arduino.stackexchange.com/questions/3079/how-to-retrieve-the-data-type-of-a-variable Accessed 4/12/2023.
//(6) Use of RTTI - Programming Questions - Arduino Forum. https://forum.arduino.cc/t/use-of-rtti/507226 Accessed 4/12/2023.
