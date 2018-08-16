#include "fixed.h"
#include "flags.h"
#include "fortran.h"
#include "free.h"
#include "newfindent.h"

void newfindent()
{
   Flags flags;
   Fortran *a, *b;
   a = new Fixed(flags);
   b = new Free(flags);

   delete a;
   delete b;
}
