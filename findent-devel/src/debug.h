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

//
// ad-hoc debugging
// turn on by  !findentfix:p-on
// turn off by !findentfix:p-off
//

extern bool p_on;

template <class S, class T> void ppp(S s, T l)
{
   //
   // output s, l with iterator
   //
   if (p_on)
   {
      typename T::iterator it = l.begin();
      int i = 0;
      if (l.empty())
	 std::cout << "! ppp:" << s << ":empty" << std::endl;
      else
	 while(it != l.end()) 
	    std::cout << "! ppp:" << ++i << ":" << s << ":[" << *it++ << "]" << std::endl;
   }
}

template <class S, class T> void ppps(S s,T t)
{
   if(p_on)
      std::cout << "! ppp:" << s << ":[" << t << "]" << std::endl;
}

template <class T> void ppp(T t)
{
   if(p_on)
      std::cout << "! ppp:[" << t << "]" << std::endl;
}

template <class T> void ppps(T t)
{
   ppp(t);
}

#endif
