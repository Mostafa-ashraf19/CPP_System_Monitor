#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"


using std::string;
using std::to_string;
using std::vector;

Process::Process()
{
  this->pid=0;
  this->username="";
  this->command="";
  this->cpUtilization=0;                  
  this->upTime=0; 
}
Process::Process(int pid):pid(pid),ram(atoi(LinuxParser::Ram(pid).c_str())){}
   
// this process's ID
int Process::Pid() { 
    return this->pid;
 }

//  process's CPU utilization
float Process::CpuUtilization() { 
    auto Values = LinuxParser::PrcoessCpuUtilization(this->pid);
    float SysUpTime = static_cast<float>(LinuxParser::UpTime());
    float TotalTime = atof(Values[0].c_str()) + atof(Values[1].c_str()) + atof(Values[2].c_str())+atof(Values[3].c_str()); 
    float secondes = SysUpTime - atof(Values[4].c_str());
    auto result = (TotalTime)/(secondes*static_cast<float>(sysconf(_SC_CLK_TCK)));
    return result;
 }

//  command that generated this process
string Process::Command() { 
   return LinuxParser::Command(this->pid);
 }

//  process's memory utilization
string Process::Ram() { 
   return to_string(this->ram);
 }

//  user (name) that generated this process
string Process::User() { 
   return LinuxParser::User(this->pid);
 }

//  age of this process (in seconds)
long int Process::UpTime() {   
    return LinuxParser::UpTime(this->pid);
}

//  Overload the "less than" comparison operator for Process objects
//  [[maybe_unused]] id 
bool Process::operator<(Process const& a) const { 
    return this->ram > a.ram;
 }