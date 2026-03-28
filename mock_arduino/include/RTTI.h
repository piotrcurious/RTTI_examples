#ifndef RTTI_H
#define RTTI_H

#include <cstring>
#include <cstdint>

namespace RTTI {
    // Basic serialize/deserialize (standard memory copy)
    template <typename T>
    int serialize(unsigned char* buffer, const T& value) {
        std::memcpy(buffer, &value, sizeof(T));
        return sizeof(T);
    }

    template <typename T>
    int deserialize(const unsigned char* buffer, T& value) {
        std::memcpy(&value, buffer, sizeof(T));
        return sizeof(T);
    }

    // Portability helpers for endianness (Little Endian by default)
    template <typename T>
    void writeLE(unsigned char* buf, T val) {
        for (size_t i = 0; i < sizeof(T); i++) {
            buf[i] = (val >> (i * 8)) & 0xFF;
        }
    }

    template <typename T>
    T readLE(const unsigned char* buf) {
        T val = 0;
        for (size_t i = 0; i < sizeof(T); i++) {
            val |= ((T)buf[i] << (i * 8));
        }
        return val;
    }

    // Specialized serializers for fixed-width types to ensure portability
    inline int serializeInt32(unsigned char* buffer, int32_t value) {
        writeLE(buffer, (uint32_t)value);
        return 4;
    }

    // Use a macro to avoid binding to references of packed fields
    #define RTTI_DESERIALIZE_INT32(buf, val) do { \
        uint32_t _tmp = 0; \
        for (size_t _i = 0; _i < 4; _i++) { \
            _tmp |= ((uint32_t)(buf)[_i] << (_i * 8)); \
        } \
        (val) = (int32_t)_tmp; \
    } while(0)

    #define RTTI_DESERIALIZE_INT16(buf, val) do { \
        uint16_t _tmp = 0; \
        for (size_t _i = 0; _i < 2; _i++) { \
            _tmp |= ((uint16_t)(buf)[_i] << (_i * 8)); \
        } \
        (val) = (int16_t)_tmp; \
    } while(0)

    inline int serializeInt16(unsigned char* buffer, int16_t value) {
        writeLE(buffer, (uint16_t)value);
        return 2;
    }
}

#endif
