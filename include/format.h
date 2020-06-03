#ifndef FORMAT_H
#define FORMAT_H

#include <string>
#include "linux_parser.h"

namespace Format {
std::string Pad(std::string s, char c); 
std::string ElapsedTime(long times);
 
};                                    

#endif