#ifndef FINDENT_H
#define FINDENT_H
#include "fortranline.h"
#include "flags.h"
#include "simpleostream.h"
#include "pre_analyzer.h"

int               determine_fix_or_free(const bool store);
void              empty_dolabels();
void              free2free();
void              get_full_statement();
int               guess_indent(const std::string str);
int               guess_fixedfree(const std::string s);
std::string       handle_dos(const std::string s);
void              handle_fixed(bool &more);
void              handle_free(bool &more);
void              handle_last_usable_only();
void              handle_prc(std::string s, const int pregentype, bool &more);
bool              handle_pre(const std::string s, const int pretype);
void              handle_reading_from_tty();
void              indent_and_output();
void              init_indent();
void              mygetline();
void              output_line();
void              pop_all(void);
int               pop_dolabel();
int               pop_indent();
struct propstruct pop_rprops();
void              push_all(void);
void              push_indent(int p);
void              push_dolabel(int l);
void              push_rprops(struct propstruct p);
void              set_default_indents();
void              top_all(void);
int               top_dolabel();
int               top_indent();
struct            propstruct top_rprops();
int               what_to_return(void);
std::string       whatrprop(struct propstruct p);


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
