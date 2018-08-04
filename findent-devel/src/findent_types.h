#ifndef FINDENT_TYPES_H
#define FINDENT_TYPES_H

#include <deque>

#include "fortranline.h"
#include "prop.h"

typedef std::deque<int>               dolabels_t;
typedef std::deque<dolabels_t>        dolabels_store_t;
typedef std::deque<int>               indent_t;
typedef std::deque<indent_t>          indent_store_t;
typedef std::deque<std::string>       fs_store_t;
typedef std::deque<fortranline>       lines_t;
typedef std::deque<fortranline>       linebuffer_t;
typedef std::deque<bool>              nbseen_store_t;
typedef std::deque<bool>              iscon_t;
typedef std::deque<struct propstruct> rprops_t;
typedef std::deque<rprops_t>          rprops_store_t;

#endif
