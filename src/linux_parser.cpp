#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
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
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel,version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> version;
  }
  return version;
}

//  Update this to use std::filesystem ( next version )
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

//  Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  // return 0.0;
  std::string key,line;
  float value;
  float MemUtiUsed{0};
  float memtot{0},memfree{0};
 std::ifstream MemInfoFile(kProcDirectory+kMeminfoFilename);
  if(MemInfoFile.is_open())
  {
    while (std::getline(MemInfoFile,line))
    {
      std::istringstream myStream(line);
      myStream >> key >> value;
      if(key == "MemTotal:")
      {
        memtot = value;
      }
      else if (key == "MemFree:")
      {
        memfree = value;
        return static_cast<float> (1-(memfree/memtot));
      }
    }
  }
  return MemUtiUsed;
 }

//  Read and return the system uptime
long LinuxParser::UpTime() { 
  std::ifstream UpTimeFile(kProcDirectory+kUptimeFilename);
  std::string line;
  long SysUpTime{0};
  if(UpTimeFile.is_open())
  {
    std::getline(UpTimeFile,line);
    std::istringstream MyStreaM(line);
    MyStreaM >> SysUpTime;
   return SysUpTime;
  
  }
  return SysUpTime;
 }

//  Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

//  Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

//  Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

//  Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// current cpu utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> CpuUtilizationVal;
  std::ifstream StatFile(kProcDirectory+kStatFilename);
  string line,key,value;
  if(StatFile.is_open())
  {
    std::getline(StatFile,line);
    std::istringstream MyStrem(line);
    MyStrem >> key;
    if(key == "cpu")
    {
      while(MyStrem >> value){CpuUtilizationVal.push_back(value);}
      return CpuUtilizationVal;
    }
  }
  return CpuUtilizationVal;
 }

// return current total processes
int LinuxParser::TotalProcesses() { 

  std::ifstream ProcessFile(kProcDirectory+kStatFilename);
  std::string line,key;
  int value{0};
  if(ProcessFile.is_open())
  {
    while(std::getline(ProcessFile,line))
    {
      std::istringstream MyStreaM(line);
      MyStreaM >> key >> value ; 
      if( key == "processes")
      {
        return value;
      }
    }
  }
return value;
 }

// return current running processes
int LinuxParser::RunningProcesses() { 
  std::ifstream ProcessFile(kProcDirectory+kStatFilename);
  std::string line,key;
  int value{0};
  if(ProcessFile.is_open())
  {
    while(std::getline(ProcessFile,line))
    {
      std::istringstream MyStreaM(line);
      MyStreaM >> key >> value ; 
      if( key == "procs_running")
      {
        return value;
      }
    }
  }
return value;
 }

// Read and return the command associated with a process
string LinuxParser::Command(int pid) { 

std::ifstream FileRead(kProcDirectory+to_string(pid)+kCmdlineFilename);
std::string line;
if(FileRead.is_open())
{
  getline(FileRead,line);
  return line;
}
return "";
 }

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 

  std::ifstream RmFile(kProcDirectory+to_string(pid)+kStatusFilename);
  string line,key,value; 
  while(std::getline(RmFile,line))
  {
  std::istringstream RMStream(line);
  RMStream >> key >> value;
  if(key == "VmSize:")
    return to_string( static_cast<int>(atoi(value.c_str()))/1024);
  }
  return "";

 }

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { /*return string();*/
  std::ifstream StatusFile(kProcDirectory+to_string(pid)+kStatusFilename);
  string line,key="",value="";
  if(StatusFile.is_open())
  {
    while(getline(StatusFile,line))
    {
      std::istringstream MyStream(line);
      MyStream >> key ;
      if(key == "Uid:")
      {
        MyStream >> value;
        return value;
      }
    }
  }
return "-1";
 }

// Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  
  std::string userid = Uid(pid);
  std::ifstream UserNameFile(kPasswordPath);
  std::string line;
   while (std::getline(UserNameFile,line))
  {
  auto index =  line.find_first_of(':')+3; 
  int i=index;
  int counter=0;
  for(;;i++) 
    if(line[i] == ':')  
       {break;}
    else 
      counter++;
  if(line.substr(index,counter) == userid)
    return line.substr(0,line.find_first_of(':'));
  }
  return "";
 }

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
  std::ifstream UPTimeFile(kProcDirectory+to_string(pid)+kStatFilename);
  std::string line,content;
  if(UPTimeFile.is_open())
  {
     std::getline(UPTimeFile,line);
    std::istringstream mystream(line);
    for(int i=1; i <= 22; i++)
         {
           mystream >> content;
            if(content[0] == '(' && content[content.length()-1] != ')') 
              i--;
         }
     return 
     static_cast<long>
    (static_cast<float>(std::atol(content.c_str()))/sysconf(_SC_CLK_TCK));         

  }
  return 0;
 }

// certin process cpu Utilization
std::vector<std::string>  LinuxParser::PrcoessCpuUtilization(int pid)
{
  std::vector<std::string> Values{};
  std::ifstream UPTimeFile(kProcDirectory+to_string(pid)+kStatFilename);
  std::string line,content;
  if(UPTimeFile.is_open())
  {
    std::getline(UPTimeFile,line);
    std::istringstream mystream(line);
    for(int i=1; i != 18; i++)
         {
           mystream >> content;
            if(content[0] == '(' && content[content.length()-1] != ')') 
              i--;
            if(i >= 14)
              Values.push_back(content);  
         }   
  }
  else 
    return  Values;
  Values.push_back(to_string(LinuxParser::UpTime(pid)));
  return Values;
}
