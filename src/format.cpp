#include <string>

#include "format.h"

using std::string;

string Format::ElapsedTime(long seconds) {

    float AllHours = static_cast<float>(seconds)/static_cast<float>(3600);
   
    float Allmin = (AllHours - static_cast<int>(AllHours))*60;
    float Allsec = (Allmin - static_cast<int>(Allmin))*60;
    return std::to_string(static_cast<int>(AllHours))+':'+
            std::to_string(static_cast<int>(Allmin))+':'+
            std::to_string(static_cast<int>(Allsec));    
 }