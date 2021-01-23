#ifndef STATISTIC_H
#define STATISTIC_H

#include <string>

#include "field.h"

class Statistic : public Field<double> {
 public:
  Statistic(std::string name, double value, std::string unit);

 private:
  std::string unit_;
};

#endif