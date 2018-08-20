#ifndef FREE_H
#define FREE_H

#include "fortran.h"

class Free : public Fortran
{
   public:
      void build_statement(Fortranline &line, bool &f_more, bool &pushback);
      void output(lines_t &lines, lines_t *freelines = 0);
      void output_converted(lines_t &lines);

   private:
      std::string rm_last_amp(const std::string &s);

};

#endif
