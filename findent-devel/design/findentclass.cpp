#include <stdio.h>
#include "findentclass.h"
#include "fortran.h"
#include "free.h"
#include "nfortranline.h"

Fortranline Findent::mygetline()
{
   curlines += 1;
   nbseen = 456;
   end_of_file = 0;
   return Fortranline("mygetline");
}

int Findent::determine_fix_or_free()
{
   mygetline();
   return 1;
}

void Findent::run()
{
   int ff = determine_fix_or_free();
   Fortran *source;
   if (ff == 1)
      source = new Free(this);
   std::cout << "RUN" << std::endl;
   std::cout << ff << std::endl;
   std::cout << "source curlines:" << source->getcurlines() << std::endl;
   source->get_full_statement();
   std::cout << "source full_statement:" << source->statement() << std::endl;
   delete source;
}
