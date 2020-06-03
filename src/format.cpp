#include <string>

#include "format.h"

using std::string;
using std::to_string;

/*string Format::ElapsedTime(long seconds) {

    float AllHours = static_cast<float>(seconds)/static_cast<float>(3600);
   
    float Allmin = (AllHours - static_cast<int>(AllHours))*60;
    float Allsec = (Allmin - static_cast<int>(Allmin))*60;
    return std::to_string(static_cast<int>(AllHours))+':'+
            std::to_string(static_cast<int>(Allmin))+':'+
            std::to_string(static_cast<int>(Allsec));    
 }*/

 std::string Format::Pad(std::string s, char c) {
  s.insert(s.begin(), 2 - s.size(), c);
  return s;
}
string Format::ElapsedTime(long  time) {
  int hours = time / (60 * 60);
  int minutes = (time / 60) % 60;
  long seconds = time % 60;
  return std::string(Format::Pad(to_string(hours), '0') + ":" +
                     Format::Pad(to_string(minutes), '0') + ":" +
                     Format::Pad(to_string(seconds), '0'));
}
