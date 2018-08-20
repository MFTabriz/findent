#ifndef READLINES_H
#define READLINES_H

#include "findentclass.h"
#include "indentclass.h"

class Readlines : public Indent
{
   public:

      Fortranline getnext(bool &eof, bool use_wb = 1);
      Fortranline mygetline(bool &eof, bool buffer = 0);

      void init()
      {
	 num_lines        = 0;
	 reading_from_tty = 0;
	 indent_handled   = 0;
	 lines_read       = 0;
	 nbseen = 0;
      }

      bool nbseen;

   private:

      linebuffer_t curlinebuffer;   // deque for source lines
      int          lines_read;
      int          num_lines;
      bool         reading_from_tty;
      linebuffer_t wizardbuffer;    // to store wizard lines and push back lines from handle_fortran
      Flags        flags;

      int          guess_indent(Fortranline line);
      std::string  handle_dos(const std::string &s);
      void         handle_reading_from_tty();

};

#endif
