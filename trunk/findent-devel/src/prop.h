#ifndef PROP_H
#define PROP_H

#include <deque>
#include <string>

struct propstruct
{
   int         kind;
   std::string name;
   std::string label;
   std::string dolabel;
} ;

const struct propstruct empty_rprop={0,"","",""};

propstruct parseline(class line_prep p);
std::string whatrprop(struct propstruct p);

typedef std::deque<struct propstruct> rprops_t;
typedef std::deque<rprops_t>          rprops_store_t;
typedef struct propstruct             prop_t;

#endif
