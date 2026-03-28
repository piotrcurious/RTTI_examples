#ifndef ARDUINO_JSON_H
#define ARDUINO_JSON_H

#include <string>
#include <map>
#include <iostream>

class JSONVar {
public:
    std::map<std::string, std::string> _values;

    class Element {
        std::string& _val;
    public:
        Element(std::string& val) : _val(val) {}
        Element& operator=(int v) { _val = std::to_string(v); return *this; }
        Element& operator=(long v) { _val = std::to_string(v); return *this; }
        Element& operator=(float v) { _val = std::to_string(v); return *this; }
        Element& operator=(bool v) { _val = v ? "true" : "false"; return *this; }
        Element& operator=(const char* v) { _val = v ? v : "null"; return *this; }
        Element& operator=(std::nullptr_t) { _val = "null"; return *this; }

        operator int() const { try { return std::stoi(_val); } catch(...) { return 0; } }
        operator char() const { try { return (char)std::stoi(_val); } catch(...) { return _val.length() > 0 ? _val[0] : 0; } }
        operator float() const { try { return std::stof(_val); } catch(...) { return 0.0f; } }
        operator bool() const { return _val == "true"; }
        operator const char*() const { return _val.c_str(); }
    };

    Element operator[](const std::string& key) {
        return Element(_values[key]);
    }

    Element operator[](const char* key) {
        return Element(_values[std::string(key)]);
    }

    operator std::string() const {
        std::string s = "{";
        for (auto const& [key, val] : _values) {
            s += "\"" + key + "\":\"" + val + "\",";
        }
        if (s.length() > 1) s.pop_back();
        s += "}";
        return s;
    }
};

inline std::ostream& operator<<(std::ostream& os, const JSONVar& json) {
    os << (std::string)json;
    return os;
}

#endif
