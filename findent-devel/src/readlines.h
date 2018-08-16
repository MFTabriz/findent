#ifndef READLINES_H
#define READLINES_H

#include "findent_types.h"
#include "flags.h"

class Readlines
{
   public:
      static fortranline getnext(bool &eof, bool use_wb = 1);
      static fortranline mygetline(bool &eof);

      void init(Flags f, int *s_indent, int *c_indent)
      {
	 flags = f;
	 num_lines        = 0;
	 reading_from_tty = 0;
	 nbseen = 0;
	 p_start_indent = s_indent;
	 p_cur_indent   = c_indent;
	 indent_handled = 0;
	 lines_read = 0;
	 input_format = fortranline::g_format();
      }

   private:
      static linebuffer_t curlinebuffer;   // deque for source lines
      static int          num_lines;
      static bool         reading_from_tty;
      static linebuffer_t wizardbuffer;    // to store wizard lines and push back lines from handle_fortran
      static bool nbseen;
      static Flags flags;
      static int *p_start_indent;
      static int *p_cur_indent;

      static void handle_reading_from_tty();
      static int guess_indent(fortranline line);

static void init_indent(){};
static bool indent_handled;
static int lines_read;
static std::string handle_dos(std::string &s){return s;};
static int input_format;
};

#endif
