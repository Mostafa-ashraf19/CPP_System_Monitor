#ifndef PROCESSOR_H
#define PROCESSOR_H
#include<vector>
#include<string>

using std::vector;
using std::string;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  Processor();
  // TODO: Declare any necessary private members
 private:
    
   vector<string> cpuValues;   
    float   previdle,
            previowait,
            prevuser,
            prevnice,
            prevsystem,
            previrq,
            prevsoftirq,
            prevsteal;
    
    float   PrevIdleTotal,
            PrevNonIdleTotal,
            PrevTotal;

    float   CPU_Percentage{0};                        
};

#endif