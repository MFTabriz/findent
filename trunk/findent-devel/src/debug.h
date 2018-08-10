// $Id$
#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <typeinfo>

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

extern  char endchar;

class debugostream 

{
   private:
      bool output;
   public:
      debugostream()
      {
	 output = 0;
      }
      void off()
      {
	 output = 0;
      }
      void on()
      {
	 output = 1;
      }
      template< typename T > debugostream& operator<<( T val )
      { 
	 if (output)
	 {
	    std::string name = typeid(val).name();
	    bool b = (typeid(val) == typeid(std::string));
	    if (name.length() > 2)
		  b = b || (name.substr(name.length()-1)=="c");

	    if (b)
	       std::cout << "[";
	    std::cout << val; 
	    if (b)
	       std::cout << "]";
	 }
	 return *this; 
      }
};

#endif
