#ifndef SYSTEM_MEMORY_H
#define SYSTEM_MEMORY_H

#include <string>
#include <unordered_map>

#include "system_property.h"

class SystemMemory : public SystemProperty {
 public:
  SystemMemory() { name_ = "system_memory"; }
  SystemMemory(const std::string name);

  void UpdateStatistics() override;

  float MemoryUtilization();

 private:
  unsigned long memTotal_ = 0L;
  unsigned long memFree_ = 0L;
  unsigned long buffers_ = 0L;
  unsigned long cached_ = 0L;
  unsigned long swapTotal_ = 0L;
  unsigned long swapFree_ = 0L;
};

#endif