#include "system_property.h"

#include <string>
#include <unordered_map>

void SystemProperty::UpdateField(Field<std::string> new_field) {
  if (fields_.find(new_field.GetName()) == fields_.end())
    fields_.insert(std::make_pair(new_field.GetName(), new_field));
  else
    fields_[new_field.GetName()].UpdateValue(new_field.GetValue());
}

void SystemProperty::UpdateMetric(Metric metric) {
  if (metrics_.find(metric.GetName()) == metrics_.end())
    metrics_.insert(std::make_pair(metric.GetName(), metric));
  else
    metrics_[metric.GetName()].UpdateValue(metric.GetValue());
}

std::string SystemProperty::GetName() { return name_; }