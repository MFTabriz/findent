#include <iostream>

#include "docs.h"
#include "fixed.h"
#include "fortran.h"
#include "free.h"
#include "newfindent.h"

int main(int argc, char*argv[])
{
   Flags flags;

   int todo = flags.get_flags(argc, argv);

   Docs docs;
   if (docs.print(todo))
      return 0;

   Findent findent = Findent(flags);
   findent.set(123);

   Fortran *a, *b;
   a = new Fixed();
   b = new Free();

   std::cout << "AAP"<< a->get() << std::endl;
   std::cout << "NOOT"<< b->get() << std::endl;
   delete b;
   delete a;
   return findent.run();
}
