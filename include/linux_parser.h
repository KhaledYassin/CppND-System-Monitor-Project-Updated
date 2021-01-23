#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

#include "cpu.h"
#include "operating_system.h"
#include "system.h"
#include "system_memory.h"

namespace LinuxParser {

// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// System
void UpdateSystemMemory(SystemMemory& memory);
void UpdateCPU(CPU& cpu);
void UpdateOperatingSystem(OperatingSystem& os);
void UpdateProcess(int Pid, Process& process);
void UpdateSystemUptime(System& system);

long UpTime();
std::vector<int> Pids();

std::string GetOsPrettyName();
std::string Kernel();

std::vector<std::string> CpuUtilization();
};  // namespace LinuxParser

#endif