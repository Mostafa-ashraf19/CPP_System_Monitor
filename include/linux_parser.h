#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

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
float MemoryUtilization(); // done
long UpTime(); // done but not used yet
std::vector<int> Pids();  // done lakn feha bonas
int TotalProcesses(); // done
int RunningProcesses();  // done
std::string OperatingSystem(); // done 
std::string Kernel(); // done

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
std::vector<std::string> CpuUtilization(); // done
long Jiffies();
long ActiveJiffies();
long ActiveJiffies(int pid);
long IdleJiffies();

// Processes
std::vector<std::string> PrcoessCpuUtilization(int pid);
std::string Command(int pid); // done
std::string Ram(int pid);//done
std::string Uid(int pid);//done
std::string User(int pid); //done
long int UpTime(int pid); // done
};  // namespace LinuxParser

#endif