

// Include the RTTI and WiFi libraries
#include <RTTI.h>
#include <ESP8266WiFi.h>

// Define a struct example
struct example {
  int a;
  float b;
  char c;
};

// Create an instance of the struct
example e;

// Create a buffer to store the received data
byte buffer[256];

// Create a WiFiUDP object
WiFiUDP udp;

// Define the UDP port to listen on
const int UDP_PORT = 2390;

// Define your WiFi network credentials
const char* ssid = "yourNetwork";
const char* password = "secretPassword";

// Define a WiFi event handler for connection status change
WiFiEventHandler wifiConnectHandler;

// Define a flag to indicate if WiFi is connected
bool wifiConnected = false;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Connect to WiFi network using event handler
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  WiFi.begin(ssid, password);

  // Start the UDP socket
  udp.begin(UDP_PORT);
}

void loop() {
  // Check if WiFi is connected
  if (wifiConnected) {
    // Check if there is any UDP packet available
    int packetSize = udp.parsePacket();
    if (packetSize) {
      // Read the packet into the buffer
      udp.read(buffer, packetSize);

      // Print the received data for debugging
      Serial.print("Received: ");
      for (int i = 0; i < packetSize; i++) {
        Serial.print(buffer[i], HEX);
        Serial.print(" ");
      }
      Serial.println();

      // Deserialize the buffer into the struct using RTTI library
      RTTI::deserialize(buffer, e);

      // Print the struct fields for debugging
      Serial.print("Struct fields: ");
      Serial.print(e.a);
      Serial.print(", ");
      Serial.print(e.b);
      Serial.print(", ");
      Serial.println(e.c);
    }
  } else {
    // Try to reconnect to WiFi network
    WiFi.begin(ssid, password);
  }

  // Wait for a second
  delay(1000);
}

// This function is called when WiFi connects successfully
void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  // Set the flag to true
  wifiConnected = true;

  // Print the IP address
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// This function is called when WiFi disconnects
void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  // Set the flag to false
  wifiConnected = false;

  // Print a message
  Serial.println("Disconnected from Wi-Fi.");
}

//Source: Conversation with Bing, 4/12/2023(1) broadcasting UDP packets - Programming Questions - Arduino Forum. https://forum.arduino.cc/t/broadcasting-udp-packets/444640 Accessed 4/12/2023.
//(2) Receiving a UDP broadcast - Arduino Forum. https://forum.arduino.cc/t/receiving-a-udp-broadcast/300160 Accessed 4/12/2023.
//(3) Ethernet Shield Sending and Receiving String via UDP - Arduino. https://www.arduino.cc/en/Tutorial/LibraryExamples/UDPSendReceiveString Accessed 4/12/2023.
//(4) Receive UDP broadcast message using ESP32 - Arduino Forum. https://forum.arduino.cc/t/receive-udp-broadcast-message-using-esp32/661017 Accessed 4/12/2023.
