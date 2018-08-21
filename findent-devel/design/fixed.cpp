#include "fixed.h"
void Fixed::build_statement(Fortranline &line, bool &f_more, bool &pushback)
{
   f_more = 1;
   pushback = 1;
   fi->getnext();
   full_statement +=" FIXED";
}
