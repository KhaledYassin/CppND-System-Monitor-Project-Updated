#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "cpu.h"
#include "field.h"
#include "metric.h"
#include "system.h"
#include "system_memory.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

void LinuxParser::UpdateSystemMemory(SystemMemory& memory) {
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  string line;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      std::string name, value, unit;
      while (linestream >> name >> value >> unit) {
        Metric metric(name, std::stoul(value), unit);
        memory.UpdateMetric(metric);
      }
    }
  }
}

void LinuxParser::UpdateCPU(CPU& cpu) {
  std::ifstream stream(kProcDirectory + kStatFilename);
  string line, key, field;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key.find("cpu") != string::npos) {
        int position = 0;
        if (std::any_of(key.begin(), key.end(), ::isdigit)) {
          std::map<string, Processor>& cores = cpu.GetCores();
          if (!cpu.CoreExists(key)) {
            cpu.AddCore(key);
          }
          Processor& core = cores[key];
          while (linestream >> field) {
            Metric metric(core.EnumStrings[position], std::stoul(field),
                          "Milliseconds");
            core.UpdateMetric(metric);
            position++;
          }
        } else {
          while (linestream >> field) {
            Metric metric(cpu.EnumStrings[position], std::stoul(field),
                          "Milliseconds");
            cpu.UpdateMetric(metric);
            position++;
          }
        }
      } else if (key == CPU::kProcessesName ||
                 key == CPU::kRunningProcessesName) {
        linestream >> field;
        Metric metric(key, std::stoul(field), "count");
        cpu.UpdateMetric(metric);
      }
    }
  }
}

void LinuxParser::UpdateOperatingSystem(OperatingSystem& os) {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        Field<std::string> field(key, value);
        os.UpdateField(field);
      }
    }
  }
}

string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

void LinuxParser::UpdateProcess(int Pid, Process& process) {
  string pid = to_string(Pid);
  string path = kProcDirectory + pid + kStatusFilename;
  string line;
  string key;
  string value;
  string unit;
  std::ifstream filestream;
  string uid;
  filestream = std::ifstream(path);

  Field<string> field(Process::kPidName, to_string(Pid));
  process.UpdateField(field);

  while (filestream.is_open() && std::getline(filestream, line)) {
    std::replace(line.begin(), line.end(), ':', ' ');
    std::istringstream linestream(line);
    linestream >> key;
    if (key == Process::kUidName) {
      linestream >> value;
      uid = value;
      Field<string> field(Process::kUidName, value);
      process.UpdateField(field);
    } else if (key == Process::kVmName) {
      linestream >> value;
      linestream >> unit;
      Metric metric(Process::kVmName, stol(value), unit);
      process.UpdateMetric(metric);
      filestream.close();
    }
  }

  path = kPasswordPath;
  filestream = std::ifstream(path);

  while (filestream.is_open() && std::getline(filestream, line)) {
    std::replace(line.begin(), line.end(), ':', ' ');
    std::string x;  // x consumer
    std::istringstream linestream(line);
    linestream >> value >> x >> key;
    if (key == uid) {
      Field<string> field(Process::kUserName, value);
      process.UpdateField(field);
      filestream.close();
    }
  }

  path = kProcDirectory + pid + kStatFilename;
  filestream = std::ifstream(path);

  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    std::istream_iterator<string> begin(linestream);
    std::istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    string unit = "Clock Ticks";
    Metric utime(Process::kProcUtime, stol(vstrings[13]), unit);
    Metric stime(Process::kProcStime, stol(vstrings[14]), unit);
    Metric cutime(Process::kProcCutime, stol(vstrings[15]), unit);
    Metric cstime(Process::kProcCstime, stol(vstrings[16]), unit);
    Metric starttime(Process::kProcStarttime, stol(vstrings[21]), unit);
    process.UpdateMetric(utime);
    process.UpdateMetric(stime);
    process.UpdateMetric(cutime);
    process.UpdateMetric(cstime);
    process.UpdateMetric(starttime);
    filestream.close();
  }

  path = kProcDirectory + pid + kCmdlineFilename;
  filestream = std::ifstream(path);

  if (filestream.is_open()) {
    std::getline(filestream, line);
    Field<string> field(Process::kCmdName, line);
    process.UpdateField(field);
    filestream.close();
  }
}

void LinuxParser::UpdateSystemUptime(System& system) {
  string path = kProcDirectory + kUptimeFilename;
  string total_uptime;
  string idle_uptime;
  string line;
  std::ifstream stream(path);
  if (stream.is_open()) {
    if (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> total_uptime >> idle_uptime;
      system.UpdateUptimes(stod(total_uptime), stod(idle_uptime));
    }
  }
}