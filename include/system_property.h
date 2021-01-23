#ifndef SYSTEM_PROPERTY_H
#define SYSTEM_PROPERTY_H

#include <string>
#include <unordered_map>

#include "metric.h"

/**
 * This is the mother class of various system properties such as CPU, Memory and
 * Kernel... Each stores information about statistics which we are interested in
 * monitoring through the system monitor application.
 * */

class SystemProperty {
 public:
  std::string GetName();
  std::unordered_map<std::string, Metric>& GetMetrics() const;
  std::unordered_map<std::string, Field<std::string>>& GetFields();
  void UpdateField(Field<std::string> new_value);
  void UpdateMetric(Metric new_value);
  virtual void UpdateStatistics() = 0;

 protected:
  /**
   * Naming is good for identifying the various system properties
   * if they get cast as the SystemProperty base class...
   * */
  std::string name_;

  /**
   * Some properties will have metrics that are simply large unsigned integers
   * others are just 'fields' of text.
   * */
  std::unordered_map<std::string, Metric> metrics_ = {};
  std::unordered_map<std::string, Field<std::string>> fields_ = {};
};

#endif