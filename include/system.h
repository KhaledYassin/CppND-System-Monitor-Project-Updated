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

  CPU& Cpu();                         // TODO: See src/system.cpp
  std::vector<Process*>& Processes();  // TODO: See src/system.cpp
  SystemMemory& Memory();
  OperatingSystem& Os();
  void Run();
  void UpdateUptimes(double totalUptime, double idleUptime);

  float MemoryUtilization();      // TODO: See src/system.cpp
  long UpTime();                  // TODO: See src/system.cpp
  int TotalProcesses();           // TODO: See src/system.cpp
  int RunningProcesses();         // TODO: See src/system.cpp
  std::string Kernel();           // TODO: See src/system.cpp
  std::string GetOsPrettyName();  // TODO: See src/system.cpp

  // TODO: Define any necessary private members
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