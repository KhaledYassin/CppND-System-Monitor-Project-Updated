#include <string>

#include "metric.h"

Metric::Metric(std::string name, unsigned long value, std::string unit) {
    name_ = name;
    value_ = value;
    unit_ = unit;
}

std::string& Metric::GetUnit() { return unit_; }

