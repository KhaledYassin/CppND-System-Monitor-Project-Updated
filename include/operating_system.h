#ifndef OPERATING_SYSTEM_H
#define OPERATING_SYSTEM_H

#include <string>

#include "system_property.h"

class OperatingSystem : public SystemProperty {
 public:
  void UpdateStatistics() override;
  std::string GetPrettyName();
  bool IsInitialized();
  void SetInitialized(bool initialized);

 private:
  bool initialized_ = false;
};

#endif