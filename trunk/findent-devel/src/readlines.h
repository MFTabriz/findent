#ifndef READLINES_H
#define READLINES_H

#include "findentclass.h"

class Readlines : public Findent
{
   public:
      fortranline getnext(bool &eof, bool use_wb = 1);
      fortranline mygetline(bool &eof);

      void init()
      {
	 num_lines        = 0;
	 reading_from_tty = 0;
	 indent_handled   = 0;
	 lines_read       = 0;
	 input_format     = fortranline::g_format();
	 endline_set      = 0;
      }

   private:
      linebuffer_t curlinebuffer;   // deque for source lines
      bool         endline_set;
      bool         indent_handled;
      int          input_format;
      int          lines_read;
      int          num_lines;
      bool         reading_from_tty;
      linebuffer_t wizardbuffer;    // to store wizard lines and push back lines from handle_fortran

      int          guess_indent(fortranline line);
      std::string  handle_dos(const std::string &s);
      void         handle_reading_from_tty();
};

#endif
