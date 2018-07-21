#ifndef FINDENT_H
#define FINDENT_H

#include "flags.h"
#include "fortranline.h"
#include "pre_analyzer.h"
#include "prop.h"
#include "simpleostream.h"

void              free2free();
void              get_full_statement();
void              handle_fixed(bool &more);
void              handle_free(bool &more);
void              handle_last_usable_only();
void              handle_prc(std::string s, const int pregentype, bool &more);
void              indent_and_output();
void              output_line();
void              set_default_indents();


extern int               cur_indent;
extern struct propstruct cur_rprop;
extern fortranline       curline;
extern bool              end_of_file;
extern std::string       endline;
extern bool              endline_set;
extern Flags             flags;
extern std::string       full_statement;             // current statement, including continuation lines, &'s removed
extern bool              indent_handled;
extern int               input_format;
extern int               labellength;
extern int               lines_read;
extern simpleostream     mycout;
extern bool              nbseen;                    // true if non-blank-line is seen 
extern int               num_lines;                 // number of lines read sofar
extern int               output_format;
extern pre_analyzer      prea;
extern struct propstruct prev_props;
extern bool              reading_from_tty;
extern bool              refactor_end_found;
extern int               start_indent;
extern int               stlabel;

extern std::stack<int>                             dolabels;        // to store labels, necessary for labelled do
extern std::stack<std::stack <int> >               dolabels_stack;  // to store dolabels stack
extern std::stack<int>                             indent;          // to store indents
extern std::stack<std::stack <int> >               indent_stack;    // to store indent stack
extern std::deque <fortranline>                    curlinebuffer;   // deque for source lines
extern std::deque <std::string>                    lines;           // current line, one continuation line per item
extern std::stack<bool>                            nbseen_stack;    // to store nbseen
extern std::deque <std::string>                    olines;          // the original line
extern std::stack<struct propstruct>               rprops;          // to store routines (module, subroutine ...)
extern std::stack<std::stack <struct propstruct> > rprops_stack;
#endif
