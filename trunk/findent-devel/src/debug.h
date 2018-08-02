// $Id$
#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>

#include "findent_types.h"

#define O(x) {std::cerr << " [" << x << "] ";}
#define Y O(yytext);O(YY_START)
// macro to activate or deactivate debug output:
#ifdef DEBUG
#define D(x) {std::cerr << "WD: "<< __FILE__ <<":"<<__LINE__<<" "; x; std::cerr << std::endl; }
#else
#define D(x)
#endif

int  ppp(const std::string &s);
template <class T> void ppp(const std::string &s, T &l)
{
   typename T::iterator it = l.begin();
   int i = 0;
   if (l.empty())
      std::cout << s << " empty" << std::endl;
   else
   while(it != l.end()) 
      std::cout << ++i << " " << s << *it++ << std::endl;
   return;
}
#endif
