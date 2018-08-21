#ifndef FREE_H
#define FREE_H
#include "fortran.h"
class Free : public Fortran
{
   public:
      Free(Findent *f) : Fortran(f) {}
      void build_statement(Fortranline &line, bool &f_more, bool &pushback);
};

#endif
