#include "Arduino.h"
#ifdef USE_ESP8266
#include "ESP8266WiFi.h"
#endif
#include <unistd.h>

#ifdef USE_ESP8266
MockESP8266WiFi WiFi;
#else
MockWiFi WiFi;
#endif

MockSerial Serial;

void delay(unsigned long ms) {
    usleep(ms * 1000);
}

int main() {
    setup();
    for (int i = 0; i < 2; ++i) { // Run loop twice for mock test
        loop();
    }
    return 0;
}
