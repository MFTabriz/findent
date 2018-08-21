#ifndef FORTRAN_H
#define FORTRAN_H

#include "nfortranline.h"
#include "findentclass.h"

class Fortran
{
   public:
      virtual ~Fortran(){}
      Fortran(Findent* f)
      {
	 fi = f;
      }
      std::string statement()
      {
	 return full_statement;
      }
      int getcurlines()
      {
	 return fi->getcurlines();
      }
      void get_full_statement();
   protected:
      virtual void build_statement(Fortranline &line, bool &f_more, bool &pushback) = 0;

      int g_format;
      Findent *fi;
      std::string full_statement;

};

#endif
