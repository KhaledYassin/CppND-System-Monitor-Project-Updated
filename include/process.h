#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "system_property.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process : public SystemProperty {
 public:
  static const std::string kPidName;
  static const std::string kUidName;
  static const std::string kVmName;
  static const std::string kUserName;
  static const std::string kCmdName;
  static const std::string kProcUtime;
  static const std::string kProcStime;
  static const std::string kProcCutime;
  static const std::string kProcCstime;
  static const std::string kProcStarttime;

  int Pid() const;                         // TODO: See src/process.cpp
  std::string User() const;                // TODO: See src/process.cpp
  std::string Command() const;             // TODO: See src/process.cpp
  float CpuUtilization() const;            // TODO: See src/process.cpp
  std::string Ram() const;                 // TODO: See src/process.cpp
  long int UpTime() const;                 // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  void UpdateStatistics() override;
  void SetSystemUptime(long system_uptime);

  // TODO: Declare any necessary private members
 private:
  int pid_;
  float cpu_utilization_;
  long int uptime_;
  std::string user_;
  std::string command_;
  float ram_;
  long system_uptime_;
};

#endif