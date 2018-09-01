#ifndef FREE_H
#define FREE_H

#include "fortran.h"
#include "debug.h"

class Free : public Fortran
{
   public:
      Free(Findent *f) : Fortran(f) { }

      void build_statement(Fortranline &line, bool &f_more, bool &pushback);

      void output(lines_t &lines, lines_t *freelines = 0);

      void output_converted(lines_t &lines);

   private:
      std::string rm_last_amp(const std::string &s);

      std::string insert_omp(const std::string s, std::string somp)
      {
	 if(is_omp)
	 {
	    std::string sl = s;
	    int l          = somp.length() - (sl+"x").find_first_not_of(' ');
	    sl             = blanks(l) + sl;
	    return sl.replace(0,somp.length(),somp);
	 }
	 else
	    return s;
      }

      bool        is_omp;
      std::string ompstr;
      std::string cmpstr;

};

#endif
