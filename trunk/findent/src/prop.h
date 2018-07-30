#ifndef PROP_H
#define PROP_H
struct propstruct
{
   int         kind;
   std::string name;
   std::string label;
   std::string dolabel;
} ;

const struct propstruct empty_rprop={0,"","",""};

propstruct parseline(class line_prep p);
#endif
