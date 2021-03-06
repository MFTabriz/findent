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

#define FL __func__<<__FILE__<<__LINE__<<':'
//
// ad-hoc debugging
// turn on by  !findentfix:p-on
// turn off by !findentfix:p-off
// or in the code: ppp.on() or ppp.off()
//
// a typical debug line would be:
// ppp<<FL<<full_statement<<endchar;
//

extern  char endchar;

class Debugostream 

{
   private:
      bool output;
   public:
      Debugostream()
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
      template< typename T > Debugostream& operator<<( T val )
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

extern Debugostream ppp;
#endif
