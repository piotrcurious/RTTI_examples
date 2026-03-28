#ifndef RTTI_H
#define RTTI_H

#include <cstring>

namespace RTTI {
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
}

#endif
