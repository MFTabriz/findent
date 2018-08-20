#ifndef FIXED_H
#define FIXED_H

#include "fortran.h"

class Fixed : public Fortran
{
   public:
      void build_statement(Fortranline &line, bool &f_more, bool &pushback);
      void output(lines_t &lines,lines_t *freelines = 0);
      void output_converted(lines_t &lines);

   private:
      bool wizard();
      bool wizard(lines_t lines);
      std::string add_amp(const std::string s,const char prevquote);
};

#endif
