#ifndef PROP_H
#define PROP_H
struct propstruct
{
   int kind;
   std::string name;
   std::string label;
   std::string dolabel;
} ;

propstruct parseline(class line_prep p);
#endif
