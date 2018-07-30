#ifndef FINDENT_TYPES_H
#define FINDENT_TYPES_H

#include <deque>
#include <list>
#include <stack>

#include "fortranline.h"
#include "prop.h"

typedef std::stack<int>               dolabels_t;
typedef std::stack<dolabels_t>        dolabels_stack_t;
typedef std::stack<int>               indent_t;
typedef std::stack<indent_t>          indent_stack_t;
typedef std::list<fortranline>        lines_t;
typedef std::deque<fortranline>       linebuffer_t;
typedef std::stack<bool>              nbseen_stack_t;
typedef std::stack<struct propstruct> rprops_t;
typedef std::stack<rprops_t>          rprops_stack_t;

#endif
