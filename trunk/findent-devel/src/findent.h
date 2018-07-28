#ifndef FINDENT_H
#define FINDENT_H

#include <deque>
#include <list>
#include <stack>
#include <string>

#include "findent_types.h"
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
void handle_refactor();
void indent_and_output();
void output_line();
void set_default_indents();


extern  int            cur_indent;
extern  fortranline    curline;
extern  bool           end_of_file;
extern  std::string    endline;
extern  bool           endline_set;
extern  Flags          flags;
extern  int            input_format;
extern  int            labellength;
extern  int            lines_read;
extern  simpleostream  mycout;
extern  bool           nbseen;            //  true if non-blank-line is seen
extern  bool           needcon;
extern  int            output_format;
extern  pre_analyzer   prea;
extern  bool           reading_from_tty;
extern  int            start_indent;

extern std::stack<bool> needcon_stack;   // used with free2fixed, 1: next line is a continuation

extern linebuffer_t     curlinebuffer;   // deque for source lines
extern lines_t          curlines;        // current line, one continuation line per item
extern dolabels_stack_t dolabels_stack;  // to store dolabels stack
extern dolabels_t       dolabels;        // to store labels, necessary for labelled do
extern indent_stack_t   indent_stack;    // to store indent stack
extern indent_t         indent;          // to store indents
extern nbseen_stack_t   nbseen_stack;    // to store nbseen
extern rprops_stack_t   rprops_stack;
extern rprops_t         rprops;          // to store routines (module, subroutine ...)

#endif
