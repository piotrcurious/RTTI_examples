
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
example e = {1, 2.5, 'x'};

// Create a buffer to store the serialized data
byte buffer[256];

// Create a WiFiUDP object
WiFiUDP udp;

// Define the UDP port and broadcast address
const int UDP_PORT = 2390;
const IPAddress UDP_BROADCAST = IPAddress(255, 255, 255, 255);

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


//Source: Conversation with Bing, 4/12/2023(1) ESP8266WiFi library — ESP8266 Arduino Core 3.1.2-7-g65579d29 documentation. http://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html Accessed 4/12/2023.
//(2) ESP8266 WIFI_AP_STA mode - Stack Overflow. https://stackoverflow.com/questions/47345141/esp8266-wifi-ap-sta-mode Accessed 4/12/2023.
//(3) [SOLVED] Reconnect ESP8266 NodeMCU to Wi-Fi Network After Lost .... https://randomnerdtutorials.com/solved-reconnect-esp8266-nodemcu-to-wifi/ Accessed 4/12/2023.
//(4) ESP8266 AP & STA Mode Together (FREE Guide For Dummies) - Siytek. https://siytek.com/esp8266-ap-and-station-mode/ Accessed 4/12/2023.
