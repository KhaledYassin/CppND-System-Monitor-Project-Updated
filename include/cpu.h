#ifndef CPU_H
#define CPU_H

#include <map>
#include <string>
#include <vector>

#include "processor.h"

/***
 * The CPU class resembles a Processor type, but at a meta-level.
 * @see processor.h
 *
 ***/
class CPU : virtual public Processor {
 public:
  static const std::string kProcessesName;
  static const std::string kRunningProcessesName;
  CPU() { name_ = "cpu"; }
  CPU(std::string name);
  void UpdateStatistics() override;
  std::map<std::string, Processor>& GetCores();
  void AddCore(const std::string name);
  bool CoreExists(const std::string name);
  int GetTotalProcesses();
  int GetRunningProcesses();

 private:
  std::map<std::string, Processor> cores_ = {};
  int total_processes_ = 0;
  int procs_running_ = 0;
};

#endif