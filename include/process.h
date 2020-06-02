#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include "linux_parser.h"

class Process {
 public:
  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();   
  void SetPid(int pid_);                                                    
  bool operator<(Process const& a) const;  
  Process(); 
  Process(int pid);
private:
  int pid;
  std::string username;
  std::string command;
  float cpUtilization;                  
  int  ram;                       
  long int upTime; 
  
};

#endif