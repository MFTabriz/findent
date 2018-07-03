// $Id$
#ifndef FINDENT_H
#define FINDENT_H

#include "line_prep.h"

int yyparse();
void yyerror(const char *c);
extern "C" int yylex();
void lexer_set(class line_prep p);
void lexer_set(std::string s, const int state);
void lexer_set(std::string s);

std::string lexer_getname(void);
std::string lexer_getstlabel(void);
std::string lexer_geti_number(void);
std::string lexer_getrest(void);
void        lexer_push(std::string s, const int state);
void        lexer_pop(void);

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

int ppp(const std::string s);

#include "debug.h"
#endif

