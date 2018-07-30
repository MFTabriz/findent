#include <iostream>
#include <string>

#include "findent_types.h"
#include "debug.h"

int ppp(const std::string &s)     // for ad-hoc debugging purposes
{
   //return 0;
   std::cout<< "ppp:["+s+"]" << std::endl;
   return 0;
}
void ppp(const std::string &s, lines_t &lines)
{
   lines_t::iterator it = lines.begin();
   while(it != lines.end()) 
   {
      std::cout << s << it->orig() << std::endl;
      it++;
   }
}

