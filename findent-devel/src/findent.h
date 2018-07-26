#ifndef FINDENT_H
#define FINDENT_H

#include <deque>
#include <list>
#include <stack>
#include <string>

#include "flags.h"
#include "fortranline.h"
#include "pre_analyzer.h"
#include "prop.h"
#include "simpleostream.h"

void free2free();
void get_full_statement();
void handle_fixed(bool &more);
void handle_free(bool &more);
void handle_last_usable_only();
void handle_prc(int &pregentype, std::list<fortranline> &c, bool &more);
void handle_refactor();
void indent_and_output();
void output_line();
void set_default_indents();


extern int               cur_indent;
extern fortranline       curline;
extern bool              end_of_file;
extern std::string       endline;
extern bool              endline_set;
extern Flags             flags;
extern int               input_format;
extern int               labellength;
extern int               lines_read;
extern simpleostream     mycout;
extern bool              nbseen;                    // true if non-blank-line is seen 
extern bool              needcon;
extern int               output_format;
extern pre_analyzer      prea;
extern bool              reading_from_tty;
extern int               start_indent;

extern std::stack<bool>              needcon_stack;   // used with free2fixed, 1: next line is a continuation
extern std::stack<int>               dolabels;        // to store labels, necessary for labelled do
extern std::stack<std::stack <int> > dolabels_stack;  // to store dolabels stack
extern std::stack<int>               indent;          // to store indents
extern std::stack<std::stack <int> > indent_stack;    // to store indent stack
extern std::deque<fortranline>       curlinebuffer;   // deque for source lines
extern std::list<fortranline>        curlines;        // current line, one continuation line per item
extern std::stack<bool>              nbseen_stack;    // to store nbseen
extern std::stack<struct propstruct> rprops;          // to store routines (module, subroutine ...)
extern std::stack<std::stack 
<struct propstruct> >                rprops_stack;

#endif
