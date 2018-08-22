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

   Findent *findent ;
   findent = new Findent(flags);
   findent->set(123);

   testje t;
   t.doit();
   std::cout << "MIES"<< findent->get() << std::endl;
   Fortran* a;
   Fortran *b;
   a = new Fixed(findent);
   b = new Free(findent);

   std::cout << "AAP"<< a->get() << std::endl;
   std::cout << "NOOT"<< b->get() << std::endl;
   findent->run();
   delete b;
   delete a;
   delete findent;
}
