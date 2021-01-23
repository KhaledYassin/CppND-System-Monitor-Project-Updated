#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

#include "system.h"

using std::string;
using std::to_string;
using std::vector;

const std::string Process::kPidName = "Pid";
const std::string Process::kUidName = "Uid";
const std::string Process::kVmName = "VmSize";
const std::string Process::kUserName = "User";
const std::string Process::kCmdName = "Cmd";
const std::string Process::kProcUtime = "utime";
const std::string Process::kProcStime = "stime";
const std::string Process::kProcCutime = "cutime";
const std::string Process::kProcCstime = "cstime";
const std::string Process::kProcStarttime = "starttime";

// TODO: Return this process's ID
int Process::Pid() const { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { return cpu_utilization_; }

// TODO: Return the command that generated this process
string Process::Command() const { return command_; }

// TODO: Return this process's memory utilization
string Process::Ram() const { 
  std::stringstream stream; 
  stream << std::fixed << std::setprecision(2) << ram_; 
  return stream.str();
}

// TODO: Return the user (name) that generated this process
string Process::User() const { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() const { return uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return this->cpu_utilization_ < a.CpuUtilization();
}

void Process::SetSystemUptime(long system_uptime) {
  system_uptime_ = system_uptime;
}

void Process::UpdateStatistics() {
  string pid = fields_[kPidName].GetValue();
  pid_ = stoi(pid);
  user_ = fields_[kUserName].GetValue();
  command_ = fields_[kCmdName].GetValue();
  ram_ = (float)metrics_[kVmName].GetValue() / 1000.0;
  long starttime = metrics_[kProcStarttime].GetValue();
  long utime = metrics_[kProcUtime].GetValue();
  long stime = metrics_[kProcStime].GetValue();
  long uptime = (utime + stime);
  long hertz = sysconf(_SC_CLK_TCK);
  uptime_ = uptime / hertz;
  long seconds = system_uptime_ - (starttime / hertz);
  cpu_utilization_ = ((float)(uptime / hertz) / (float)seconds);
}
