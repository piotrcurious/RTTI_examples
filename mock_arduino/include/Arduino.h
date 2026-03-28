#ifndef ARDUINO_H
#define ARDUINO_H

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdint>

typedef uint8_t byte;
typedef bool boolean;

#define HEX 16
#define DEC 10

void delay(unsigned long ms);

class IPAddress {
    uint8_t _addr[4];
public:
    IPAddress() { memset(_addr, 0, 4); }
    IPAddress(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
        _addr[0] = a; _addr[1] = b; _addr[2] = c; _addr[3] = d;
    }
    std::string toString() const {
        return std::to_string(_addr[0]) + "." + std::to_string(_addr[1]) + "." + std::to_string(_addr[2]) + "." + std::to_string(_addr[3]);
    }
};

class MockSerial {
public:
    void begin(unsigned long baud) {}
    void print(const char* s) { std::cout << s; }
    void print(std::string s) { std::cout << s; }
    void print(int n, int base = DEC) {
        if (base == HEX) printf("%02X", (unsigned int)(uint8_t)n);
        else std::cout << n;
    }
    void print(float f) { std::cout << f; }
    void println(const char* s = "") { std::cout << s << std::endl; }
    void println(std::string s) { std::cout << s << std::endl; }
    void println(int n, int base = DEC) {
        if (base == HEX) printf("%02X\n", (unsigned int)(uint8_t)n);
        else std::cout << n << std::endl;
    }
    void println(float f) { std::cout << f << std::endl; }
    void println(const IPAddress& ip) { std::cout << ip.toString() << std::endl; }
    operator bool() { return true; }
};

#define WL_CONNECTED 3

class MockWiFi {
public:
    void begin(const char* ssid, const char* password) {}
    int status() { return WL_CONNECTED; }
    IPAddress localIP() { return IPAddress(192, 168, 1, 100); }
};

extern MockSerial Serial;

class WiFiUDP {
public:
    void begin(uint16_t port) {}
    int beginPacket(IPAddress ip, uint16_t port) { return 1; }
    int endPacket() { return 1; }
    size_t write(const uint8_t *buffer, size_t size) { return size; }
    size_t write(const char* s) { return strlen(s); }
    int parsePacket() { return 0; }
    int read(unsigned char* buffer, size_t len) { return 0; }
    IPAddress remoteIP() { return IPAddress(192, 168, 1, 101); }
    uint16_t remotePort() { return 1234; }
};

#endif
