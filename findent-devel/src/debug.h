// $Id$
#include <iostream>
#include <string>

#include "findent_types.h"

#ifndef DEBUG_H
#define DEBUG_H
#define O(x) {std::cerr << " [" << x << "] ";}
#define Y O(yytext);O(YY_START)
// macro to activate or deactivate debug output:
#ifdef DEBUG
#define D(x) {std::cerr << "WD: "<< __FILE__ <<":"<<__LINE__<<" "; x; std::cerr << std::endl; }
#else
#define D(x)
#endif
#endif

int  ppp(const std::string &s);
void ppp(const std::string &s,lines_t &lines);

