
// Include the RTTI library
#include <RTTI.h>

// Define a struct example
struct example {
  int a;
  float b;
  char c;
};

// Create an instance of the struct
example e = {1, 2.5, 'x'};

// Create a buffer to store the serialized data
byte buffer[256];

// Create a WiFiUDP object
WiFiUDP udp;

// Define the UDP port and broadcast address
const int UDP_PORT = 2390;
const IPAddress UDP_BROADCAST = IPAddress(255, 255, 255, 255);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Connect to WiFi network
  WiFi.begin("yourNetwork", "secretPassword");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print the IP address
  Serial.println(WiFi.localIP());

  // Start the UDP socket
  udp.begin(UDP_PORT);
}

void loop() {
  // Serialize the struct using RTTI library
  int size = RTTI::serialize(buffer, e);

  // Send the serialized data as a UDP broadcast packet
  udp.beginPacket(UDP_BROADCAST, UDP_PORT);
  udp.write(buffer, size);
  udp.endPacket();

  // Print the serialized data for debugging
  Serial.print("Sent: ");
  for (int i = 0; i < size; i++) {
    Serial.print(buffer[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Wait for a second
  delay(1000);
}


//Source: Conversation with Bing, 4/12/2023(1) Using Wifi module ESP8266 to send UDP broadcast message. https://stackoverflow.com/questions/30625557/using-wifi-module-esp8266-to-send-udp-broadcast-message Accessed 4/12/2023.
//(2) Send and Receive UDP String | Arduino Documentation. https://docs.arduino.cc/library-examples/wifi-library/WiFiUdpSendReceiveString/ Accessed 4/12/2023.
//(3) serial - Is there a practical way to broadcast and receive ascii .... https://arduino.stackexchange.com/questions/20910/is-there-a-practical-way-to-broadcast-and-receive-ascii-payloads-over-ethernet-o Accessed 4/12/2023.
