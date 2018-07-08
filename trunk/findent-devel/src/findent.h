// $Id$
#ifndef FINDENT_H
#define FINDENT_H

#include "line_prep.h"

int yyparse();
void yyerror(const char *c);
extern "C" int yylex();
void lexer_set(class line_prep p, const int state);
void lexer_set(std::string s, const int state);

std::string lexer_getname(void);
std::string lexer_getstlabel(void);
std::string lexer_geti_number(void);
std::string lexer_getrest(void);

struct propstruct
{
   int kind;
   std::string name;
   std::string label;
   std::string dolabel;
} ;

const struct propstruct empty_rprop={0,"","",""};

propstruct is_it    (class line_prep p, int what);
propstruct parseline(class line_prep p);

void lexer_enable(const int k);


#include "debug.h"
#endif

