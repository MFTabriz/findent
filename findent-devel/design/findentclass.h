#ifndef FINDENTCLASS_H
#define FINDENTCLASS_H
#include <iostream>
#include <string>
#include "nfortranline.h"
class Findent
{
   public:
      Findent()
      {
	 curlines = 123;
	 nbseen = -123;
      }
      void run();
      Fortranline getnext()
      {
	 return mygetline();
      }
      int getcurlines()
      {
	 return curlines;
      }
   protected:
      int nbseen;
      int curlines;
      int end_of_file;

      Fortranline mygetline();
      int determine_fix_or_free();


};
#endif
