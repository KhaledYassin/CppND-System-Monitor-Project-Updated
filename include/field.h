#ifndef FIELD_H
#define FIELD_H

#include <string>

template <typename T>
class Field {
 public:
  Field() {}
  Field(std::string name, T value) : name_(name), value_(value) {}
  T& GetValue() { return value_; };
  void UpdateValue(const T new_value) { value_ = new_value; }
  std::string& GetName() { return name_; };

 protected:
  std::string name_;
  T value_;
};

#endif