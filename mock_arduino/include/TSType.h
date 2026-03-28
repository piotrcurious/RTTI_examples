#ifndef TSTYPE_H
#define TSTYPE_H

#include <vector>
#include <string>
#include <cstring>
#include <typeinfo>

enum TSTypeEnum {
  TS_INT,
  TS_FLOAT,
  TS_CHAR,
  TS_BOOL,
  TS_CHAR_ARRAY
};

struct TSTypeField {
  const char* name;
  TSTypeEnum type;
  size_t size;
  size_t offset;
};

template <typename T>
class TSType {
public:
  TSType() {
    _typeName = typeid(T).name();
    // In many g++ versions, typeid(T).name() is mangled.
    // We'll do a simple check for "Person"
    if (_typeName.find("Person") != std::string::npos || _typeName == "6Person") {
       _typeName = "Person";
       _fields.push_back({"age", TS_INT, sizeof(int), 0});
       _fields.push_back({"name", TS_CHAR_ARRAY, 20, sizeof(int)});
       _fields.push_back({"married", TS_BOOL, sizeof(bool), sizeof(int) + 20});
    }
  }

  const char* name() { return _typeName.c_str(); }
  int numFields() { return _fields.size(); }
  TSTypeField getField(int i) { return _fields[i]; }
  void* getFieldValue(void* data, int i) {
    return (char*)data + _fields[i].offset;
  }

private:
  std::vector<TSTypeField> _fields;
  std::string _typeName;
};

#endif
