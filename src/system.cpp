#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::unordered_map;
using std::vector;

// TODO: Return the system's CPU
CPU& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process*>& System::Processes() { return processes_; }

SystemMemory& System::Memory() { return memory_; }

OperatingSystem& System::Os() { return os_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return kernel_; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return memory_.MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::GetOsPrettyName() { return os_.GetPrettyName(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return cpu_.GetRunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return processes_.size(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return total_uptime_; }

void System::UpdateUptimes(double totalUptime, double idleUptime) {
  total_uptime_ = (long)totalUptime;
  idle_uptime_ = (long)idleUptime;
}

void System::Run() {
  if (kernel_.empty()) {
    kernel_ = LinuxParser::Kernel();
  }

  if (!os_.IsInitialized()) {
    LinuxParser::UpdateOperatingSystem(os_);
    os_.SetInitialized(true);
  }

  LinuxParser::UpdateSystemUptime(*this);

  LinuxParser::UpdateSystemMemory(memory_);
  memory_.UpdateStatistics();

  LinuxParser::UpdateCPU(cpu_);
  cpu_.UpdateStatistics();

  processes_.clear();
  vector<int> pids = LinuxParser::Pids();

  for (int& pid : pids) {
    // TODO: Check if we need to allocate 'new' data
    Process* process = new Process();
    processes_.push_back(process);
    LinuxParser::UpdateProcess(pid, *process);
    process->SetSystemUptime(this->UpTime());
    process->UpdateStatistics();
  }

  std::sort(processes_.begin(), processes_.end(),
            [](const Process* a, const Process* b) {
              return a->CpuUtilization() > b->CpuUtilization();
            });
}