#include <iostream>

#include "docs.h"
#include "fixed.h"
#include "fortran.h"
#include "free.h"
#include "findent.h"

int main(int argc, char*argv[])
{
   Flags flags;

   int todo = flags.get_flags(argc, argv);

   Docs docs;
   if (docs.print(todo))
      return 0;

   Findent *findent ;
   findent = new Findent(flags);

   Fortran* a;
   Fortran *b;
   a = new Fixed(findent);
   b = new Free(findent);

   findent->run();
   delete b;
   delete a;
   delete findent;
}
