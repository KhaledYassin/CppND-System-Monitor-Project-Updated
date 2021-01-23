#include "operating_system.h"

#include <string>

std::string OperatingSystem::GetPrettyName() {
  return fields_["PRETTY_NAME"].GetValue();
}

bool OperatingSystem::IsInitialized() { return initialized_; }

void OperatingSystem::SetInitialized(bool initialized) {
  initialized_ = initialized;
}

void OperatingSystem::UpdateStatistics() {}