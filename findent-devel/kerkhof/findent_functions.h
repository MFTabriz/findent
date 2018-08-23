#ifndef FINDENT_FUNCTIONS_H
#define FINDENT_FUNCTIONS_H

#include "findent.h"
#include "findent_types.h"
#include "flags.h"

inline int M(const int k)
{
   //
   // used to delimit indentation
   //
   if (flags.max_indent <= 0)
      return k;
   else
      return std::min(flags.max_indent,k);
}

int               determine_fix_or_free();
void              empty_dolabels();
int               guess_fixedfree(fortranline &line);
int               guess_indent(fortranline line);
std::string       handle_dos(const std::string &s);
void              handle_pre(fortranline &line, const bool f_more, bool &p_more);
void              handle_pre_light(fortranline &line, bool &p_more);
void              handle_reading_from_tty();
void              handle_refactor();
void              init_indent();
fortranline       mygetline(bool &eof);
bool              output_pre(lines_t &lines, lines_t *outlines = 0);
void              pop_all(void);
int               pop_dolabel();
int               pop_indent();
struct propstruct pop_rprops();
struct            propstruct top_rprops();
void              push_all(void);
void              push_dolabel(int l);
void              push_indent(int p);
void              push_rprops(struct propstruct p);
void              top_all(void);
int               top_dolabel();
int               top_indent();
std::string       whatrprop(struct propstruct p);
int               what_to_return(void);

#endif