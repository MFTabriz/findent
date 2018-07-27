#ifndef FINDENT_TYPES_H
#define FINDENT_TYPES_H
#include <list>
#include <deque>
#include "fortranline.h"
using lines_t      = std::list<fortranline>;
using linebuffer_t = std::deque<fortranline>;
#endif
