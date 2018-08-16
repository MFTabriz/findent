#include "fixed.h"
#include "flags.h"
#include "fortran.h"
#include "free.h"
#include "newfindent.h"
#include "readlines.h"

int main()
{
   Findent findent;
   Flags flags;

   Fortran *a, *b;
   a = new Fixed();
   b = new Free();

   delete b;
   delete a;
}
