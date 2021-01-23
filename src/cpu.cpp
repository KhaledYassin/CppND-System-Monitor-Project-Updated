#include "cpu.h"

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "processor.h"

const std::string CPU::kProcessesName = "processes";
const std::string CPU::kRunningProcessesName = "procs_running";

CPU::CPU(const std::string name) { this->name_ = name; }

std::map<std::string, Processor>& CPU::GetCores() { return cores_; }

void CPU::AddCore(const std::string name) { cores_[name] = Processor(name); }

bool CPU::CoreExists(const std::string name) {
  return cores_.find(name) != cores_.end();
}

int CPU::GetTotalProcesses() { return total_processes_; }
int CPU::GetRunningProcesses() { return procs_running_; }

void CPU::UpdateStatistics() {
  Processor::UpdateStatistics();
  std::for_each(cores_.begin(), cores_.end(),
                [](auto& core) { core.second.UpdateStatistics(); });
  total_processes_ = metrics_[kProcessesName].GetValue();
  procs_running_ = metrics_[kRunningProcessesName].GetValue();
}