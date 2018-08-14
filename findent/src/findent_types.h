#ifndef FINDENT_TYPES_H
#define FINDENT_TYPES_H

#include <deque>

#include "fortranline.h"
#include "prop.h"

template <class C> std::ostream& operator <<(std::ostream &os, std::deque<C> &obj)
{
   if (obj.empty())
   {
      os << ":empty";
      return os;
   }

   os << std::endl;

   typename std::deque<C>::iterator it = obj.begin();
   int i = 0;
   while (it != obj.end())
      os << ++i << ":" << *it++ << std::endl;
   return os;
}

typedef std::deque<int>               dolabels_t;
typedef std::deque<dolabels_t>        dolabels_store_t;
typedef std::deque<int>               indent_t;
typedef std::deque<indent_t>          indent_store_t;
typedef std::deque<std::string>       fs_store_t;
typedef std::deque<fortranline>       lines_t;
typedef std::deque<fortranline>       linebuffer_t;
typedef std::deque<bool>              nbseen_store_t;
typedef std::deque<struct propstruct> rprops_t;
typedef std::deque<rprops_t>          rprops_store_t;

#endif
