#ifndef FINDENT_H
#define FINDENT_H

#include <string>

#include "findent_types.h"
#include "flags.h"
#include "fortranline.h"
#include "pre_analyzer.h"
#include "prop.h"
#include "simpleostream.h"

void get_full_statement();
bool handle_findentfix(fortranline &line);
void handle_fixed(bool &more);
void handle_fortran(fortranline &line,bool &more, bool &pushback);
void handle_free(fortranline &curline, bool &more,bool &pushback);
void handle_last_usable_only();
void handle_refactor();
void indent_and_output();
bool ispre(const std::string &line);
void output_line();
void set_default_indents();


extern  int            cur_indent;
extern  fortranline    curline;
extern  std::string    endline;
extern  bool           endline_set;
extern  bool           end_of_file;
extern  Flags          flags;
extern  std::string    full_statement;
extern  bool           indent_handled;
extern  int            input_format;
extern  bool           iscon;
extern  int            labellength;
extern  int            lines_read;
extern  simpleostream  mycout;
extern  bool           nbseen;            //  true if non-blank-line is seen
extern  int            output_format;
extern  pre_analyzer   prea;
extern  bool           reading_from_tty;
extern  int            start_indent;


extern linebuffer_t     curlinebuffer;   // deque for source lines
extern lines_t          curlines;        // current line, one continuation line per item
extern dolabels_stack_t dolabels_stack;  // to store dolabels stack
extern dolabels_t       dolabels;        // to store labels, necessary for labelled do
extern fs_stack_t       fs_stack;        // to store full_statement
extern indent_stack_t   indent_stack;    // to store indent stack
extern indent_t         indent;          // to store indents
extern nbseen_stack_t   nbseen_stack;    // to store nbseen
extern iscon_t          iscon_stack;     // to store iscon
extern rprops_stack_t   rprops_stack;
extern rprops_t         rprops;          // to store routines (module, subroutine ...)

#endif
