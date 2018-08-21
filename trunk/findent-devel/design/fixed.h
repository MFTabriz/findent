#ifndef FIXED_H
#define FIXED_H
#include "fortran.h"
class Fixed : public Fortran
{
   public:
      Fixed(Findent *f) : Fortran(f) {}
      void build_statement(Fortranline &line, bool &f_more, bool &pushback);
};

#endif
