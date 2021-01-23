#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "cpu.h"
#include "operating_system.h"
#include "process.h"
#include "processor.h"
#include "system_memory.h"

class System {
 public:
  static const std::string kProcUtime;
  static const std::string kProcStime;
  static const std::string kProcCutime;
  static const std::string kProcCstime;
  static const std::string kProcStarttime;

  CPU& Cpu();
  std::vector<Process*>& Processes();
  SystemMemory& Memory();
  OperatingSystem& Os();
  void Run();
  void UpdateUptimes(double totalUptime, double idleUptime);

  float MemoryUtilization();
  long UpTime();
  int TotalProcesses();
  int RunningProcesses();
  std::string Kernel();
  std::string GetOsPrettyName();

 private:
  CPU cpu_;
  std::vector<Process*> processes_ = {};
  SystemMemory memory_;
  OperatingSystem os_;
  std::string kernel_;
  long total_uptime_;
  long idle_uptime_;
};

#endif