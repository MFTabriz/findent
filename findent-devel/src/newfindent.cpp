#include <iostream>

#include "docs.h"
#include "fixed.h"
#include "flags.h"
#include "fortran.h"
#include "free.h"
#include "newfindent.h"
#include "readlines.h"

int main(int argc, char*argv[])
{
   Flags flags;

   int todo = flags.get_flags(argc, argv);

   Docs docs;
   if (docs.print(todo))
      return 0;

   Findent findent;
   findent.init(flags);

   std::cout << "aan het werk!" << std::endl;
   Fortran *a, *b;
   a = new Fixed();
   b = new Free();

   delete b;
   delete a;
}
