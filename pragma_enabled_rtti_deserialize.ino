
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
  // Receive a UDP packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // Read the packet into a buffer
    byte buffer[sizeof(example)];
    Udp.read(buffer, sizeof(example));

    // Deserialize the buffer into a struct using RTTI and dynamic_cast
    byte* p = buffer;
    for (int i = 0; i < sizeof(example); i++) {
      byte* b = static_cast<byte*>(&myVar);
      void* v = dynamic_cast<void*>(b);
      b[i] = *p++;
    }

    // Print the struct fields
    Serial.print("a: ");
    Serial.println(myVar.a);
    Serial.print("b: ");
    Serial.println(myVar.b);
    Serial.print("c: ");
    Serial.println(myVar.c);
  }
}
```

//Source: Conversation with Bing, 4/12/2023(1) Ethernet Shield Sending and Receiving String via UDP - Arduino. https://www.arduino.cc/en/Tutorial/LibraryExamples/UDPSendReceiveString Accessed 4/12/2023.
//(2) Send and Receive UDP String | Arduino Documentation. https://docs.arduino.cc/library-examples/wifi-library/WiFiUdpSendReceiveString/ Accessed 4/12/2023.
//(3) Send UDP from Arduino - Stack Overflow. https://stackoverflow.com/questions/44022005/send-udp-from-arduino Accessed 4/12/2023.
