#ifndef FORTRAN_H
#define FORTRAN_H

#include "findent_types.h"
#include "findentclass.h"
#include "flags.h"
#include "fortranline.h"
#include "readlines.h"
#include "simpleostream.h"

class Fortran : public Findent
{
   public:
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

      std::string full_statement;
      lines_t     curlines;
      int         labellength;
      bool        output_pre(lines_t &lines, lines_t *outlines);
      void        handle_pre_light(fortranline &line, bool &p_more);
      Readlines   readlines;

      int M(const int k)
      {
	 //
	 // used to delimit indentation
	 //
	 if (flags.max_indent <= 0)
	    return k;
	 else
	    return std::min(flags.max_indent,k);
      }
};

#endif
