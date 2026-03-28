#ifndef ESP8266WIFI_H
#define ESP8266WIFI_H

#include "Arduino.h"

struct WiFiEventStationModeGotIP {};
struct WiFiEventStationModeDisconnected {};

typedef void (*WiFiEventHandler)(const WiFiEventStationModeGotIP&);
typedef void (*WiFiDisconnectHandler)(const WiFiEventStationModeDisconnected&);

class MockESP8266WiFi : public MockWiFi {
public:
    WiFiEventHandler onStationModeGotIP(void (*handler)(const WiFiEventStationModeGotIP&)) { return handler; }
    WiFiDisconnectHandler onStationModeDisconnected(void (*handler)(const WiFiEventStationModeDisconnected&)) { return (WiFiDisconnectHandler)handler; }
};

#ifdef USE_ESP8266
extern MockESP8266WiFi WiFi;
#else
extern MockWiFi WiFi;
#endif

#endif
