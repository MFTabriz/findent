#ifndef FINDENT_FUNCTIONS_H
#define FINDENT_FUNCTIONS_H

#include "findent_types.h"

int               determine_fix_or_free();
std::string       handle_dos(const std::string s);
void              handle_pre_light(fortranline &fs, int &p, bool &more);
void              handle_refactor();
int               pop_dolabel();
int               top_dolabel();
void              push_dolabel(int l);
void              empty_dolabels();
int               guess_fixedfree(const std::string s);
void              push_all(void);
void              top_all(void);
void              pop_all(void);
int               what_to_return(void);
int               pop_indent();
struct propstruct pop_rprops();
bool              handle_pre(const bool output, lines_t &ci, lines_t &co);
struct            propstruct top_rprops();
std::string       whatrprop(struct propstruct p);
int               guess_indent(const std::string str);
void              handle_reading_from_tty();
void              init_indent();
void              mygetline();
int               top_indent();
void              push_indent(int p);
void              push_rprops(struct propstruct p);
#endif
