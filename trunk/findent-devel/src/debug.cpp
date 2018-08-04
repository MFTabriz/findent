#include <iostream>
#include <string>

#include "findent_types.h"
#include "debug.h"

bool ppp_on;

int ppps(const std::string &s,const std::string &t)     // for ad-hoc debugging purposes
{
   if(ppp_on)
      std::cout << "! ppp:" << s << ":[" << t << "]" << std::endl;
   return 0;
}
