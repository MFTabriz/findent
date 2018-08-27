#ifndef LEXER_H
#define LEXER_H

#include "line_prep.h"

void yyerror(const char *c);

extern "C" int yylex();

void lexer_enable(const int k);

void lexer_set(Line_prep p, const int state);

void lexer_set(const std::string &s, const int state);

std::string lexer_getname(void);

std::string lexer_getstlabel(void);

std::string lexer_geti_number(void);

std::string lexer_getrest(void);

#endif
