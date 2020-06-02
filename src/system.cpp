#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include<algorithm>
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
System::System()
{}

// system's CPU
Processor& System::Cpu() { 
    return cpu_; 
}

// container composed of the system's current working processes
vector<Process>& System::Processes() { 
    processes_.clear(); 
    auto vec  = LinuxParser::Pids();
    for(auto id: vec)
    {
        Process p(id);       
        processes_.push_back(p);
    }
    //  sort in order of memory 
    std::sort(processes_.begin(),processes_.end(),[](Process x,Process y ){
        return x < y;
    });
    return this->processes_;
 }

// system kernel identifier
std::string System::Kernel() { // kernel name (done)
    return LinuxParser::Kernel();
 }  

// Memory consumption
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization();
 }

// operating system name (done)
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem();
 }
// current processes running 
int System::RunningProcesses() {
    return LinuxParser::RunningProcesses();
 }
// total number of processes 
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses();
 }

// number of seconds since the system started running
long System::UpTime() { 
  return LinuxParser::UpTime();
 }