
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
    
    // Send an acknowledgement packet back to the sender
    char replyPacket[] = "Received your packet!";
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyPacket);
    Udp.endPacket();
    
  }
}

//Source: Conversation with Bing, 4/12/2023(1) ESP8266 UDP Send & Receive Example (Step-by-Step Tutorial). https://siytek.com/esp8266-udp-send-receive/ Accessed 4/12/2023.
//(2) UDP — ESP8266 Arduino Core 3.1.2-7-g65579d29 documentation. https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/udp-examples.html Accessed 4/12/2023.
//(3) Arduino ESP8266 WiFi UDP Plotting - Wireless - MegunoLink. https://www.megunolink.com/articles/wireless/esp8266-wifi-udp-plotting/ Accessed 4/12/2023.
//(4) Arduino/WiFiUdp.h at master · esp8266/Arduino · GitHub. https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/WiFiUdp.h Accessed 4/12/2023.
