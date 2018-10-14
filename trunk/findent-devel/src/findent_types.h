#ifndef NFINDENT_TYPES_H
#define NFINDENT_TYPES_H

#include <deque>
#include <iostream>
#include <string>

typedef std::deque<int>               dolabels_t;
typedef std::deque<dolabels_t>        dolabels_store_t;
typedef std::deque<int>               indent_t;
typedef std::deque<indent_t>          indent_store_t;
typedef std::deque<std::string>       fs_store_t;
typedef std::deque<bool>              nbseen_store_t;

struct twostrings{std::string type; std::string element;};

template <class C> std::ostream& operator <<(std::ostream &os, std::deque<C> &obj)
{
   //
   // to print a deque
   //
   if (obj.empty())
   {
      os << ":empty"<<std::endl;
      return os;
   }

   os << std::endl;

   typename std::deque<C>::iterator it = obj.begin();
   int i = 0;
   while (it != obj.end())
      os << ++i << ":" << *it++ << std::endl;
   return os;
}


#endif
