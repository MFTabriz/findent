#ifndef FORTRAN_H
#define FORTRAN_H

#include "findent_types.h"
#include "flags.h"
#include "fortranline.h"
#include "simpleostream.h"

class Fortran
{
   //friend class Fixed;

   public:
      Fortran(Flags &f) { flags = f; }
      virtual ~Fortran(){}

      virtual void build_statement(fortranline &line, bool &f_more, bool &pushback) = 0;
      // replaces handle_free, handle_fixed
      virtual void output(lines_t &lines,lines_t *freelines = 0) = 0;
      // replaces fixed2fixed/free2free
      virtual void output_converted(lines_t &lines) = 0;
      // replaces fixed2free and free2fixed

      std::string statement() 
      { 
	 return full_statement; 
      }

      lines_t lines()
      {
	 return curlines;
      }

   protected:
      Flags flags;
      std::string full_statement;
      lines_t curlines;
};

#endif
