#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <map>
#include <string>

#include "system_property.h"

// CPU
enum ProcessorStates {
  kUser_ = 0,
  kNice_ = 1,
  kSystem_ = 2,
  kIdle_ = 3,
  kIOwait_ = 4,
  kIRQ_ = 5,
  kSoftIRQ_ = 6,
  kSteal_ = 7,
  kGuest_ = 8,
  kGuestNice_ = 9
};

class Processor : public SystemProperty {
 public:
  static const std::string EnumStrings[];
  Processor() {}
  Processor(std::string const name);
  long TotalIdle();
  long TotalNonIdle();
  void UpdateStatistics() override;

  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  long user_;
  long nice_;
  long system_;
  long idle_;
  long iowait_;
  long irq_;
  long softirq_;
  long steal_;
  long guest_;
  long guest_nice;
  float cpu_utilization_;
};

#endif