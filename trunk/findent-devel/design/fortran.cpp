#include "fortran.h"

void Fortran::get_full_statement()
{
   bool f_more,pushback;
   Fortranline line = fi->getnext();
   build_statement(line, f_more, pushback);
   full_statement = "full_statement"+line.str();
}
