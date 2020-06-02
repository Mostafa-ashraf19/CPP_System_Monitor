#include "processor.h"
#include "linux_parser.h"
Processor::Processor()
{
        prevuser= 0;
        prevnice= 0;
        prevsystem= 0;
        previdle= 0;
        previowait= 0;
        previrq = 0;
        prevsoftirq = 0;
        prevsteal= 0;

        PrevIdleTotal = previdle + previowait; // prev calculation
        PrevNonIdleTotal = prevuser + prevnice+ prevsystem+previrq+prevsoftirq+prevsteal;
        PrevTotal = PrevIdleTotal + PrevNonIdleTotal;
}

float Processor::Utilization() {  
    auto res = LinuxParser::CpuUtilization();
    float  Currentuser = std::stof(res[0]),
           Currentnice= std::stof(res[1]),
           Currentsystem = std::stof(res[2]),
           Currentidle = std::stof(res[3]),
           Currentiowait = std::stof(res[4]),
           Currentirq = std::stof(res[5]),
           Currentsoftirq = std::stof(res[6]),
           Currentsteal = std::stof(res[7]);

    
    auto Idle =  Currentidle + Currentiowait;
    auto NonIdle = Currentuser + Currentnice + Currentsystem + Currentirq 
                    + Currentsoftirq + Currentsteal;
    auto Total = Idle + NonIdle;

    auto totald = Total - PrevTotal;
    auto idled = Idle - PrevIdleTotal;  


    CPU_Percentage = (totald - idled)/totald;

    prevuser = Currentuser;
    prevnice = Currentnice;
    prevsystem = Currentsystem;
    previdle = Currentidle;
    previowait = Currentiowait;
    previrq = Currentirq;
    prevsoftirq = Currentsoftirq;
    prevsteal = Currentsteal;

    PrevIdleTotal = previdle + previowait; // prev calculation
    PrevNonIdleTotal = prevuser + prevnice+ prevsystem+previrq+prevsoftirq+prevsteal;
    PrevTotal = PrevIdleTotal + PrevNonIdleTotal;

    return CPU_Percentage;   
}
