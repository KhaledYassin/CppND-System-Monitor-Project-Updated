#ifndef METRIC_H
#define METRIC_H

#include <string>

#include "field.h"

class Metric : public Field<unsigned long> {
 public:
  Metric() {}
  Metric(std::string name, unsigned long value, std::string unit);
  std::string& GetUnit();

 private:
  std::string unit_;
};

#endif