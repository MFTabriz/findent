#ifndef FINDENTCLASS_H
#define FINDENTCLASS_H

#include <stack>
#include <string>

#include "flags.h"
#include "prop.h"
#include "findent_types.h"
#include "debug.h"
#include "fortranline.h"
#include "globals.h"

class Findent
{

   public:
      Findent() {}

      Findent(Flags &f)
      {
	 //
	 // public
	 //
	 gl                 = new Globals;
	 cur_indent         = 0;
	 cur_rprop          = empty_rprop;
	 end_of_file        = 0;
	 endline            = "\n";
	 flags              = f;
	 indent_handled     = 0;
	 labellength        = 0;
	 nbseen             = 0;
	 num_lines          = 0;
	 start_indent       = 0;

	 gl->global_format      = UNKNOWN;
	 gl->global_gnu_format  = flags.input_format_gnu;;
	 gl->global_line_length = flags.input_line_length;
	 gl->global_omp         = flags.honour_omp;

	 //
	 // private
	 //
	 all_indent         = 0;
	 endline_set        = 0;
	 input_format       = flags.input_format;
	 lines_read         = 0;
	 output_format      = 0;
	 reading_from_tty   = 0;
	 //
	 // for getnext:
	 //
	 prevlastchar       = 0;
      }

      ~Findent() { delete gl; }

      Fortranline getnext(bool &eof, bool use_wb = 1);
      Fortranline mygetline(bool &eof, bool buffer = 0);

      void         handle_pre_light(Fortranline &line, bool &p_more);
      void         init_indent();
      int          run();

      int          cur_indent;
      std::string  endline;
      bool         end_of_file;
      Flags        flags;
      Globals*     gl;
      bool         indent_handled;
      indent_t     indent;          // to store indents
      int          input_format;
      int          labellength;
      bool         nbseen;
      int          num_lines;
      int          output_format;
      int          start_indent;

      std::stack <struct twostrings> includes;

   private:

      int          all_indent;
      linebuffer_t curlinebuffer;   // deque for source lines
      prop_t       cur_rprop;
      bool         endline_set;
      int          lines_read;
      bool         reading_from_tty;
      linebuffer_t wizardbuffer;    // to store wizard lines and push back lines from handle_fortran

      int          determine_fix_or_free();
      int          guess_fixedfree(Fortranline &line);
      int          guess_indent(Fortranline line);
      std::string  handle_dos(const std::string &s);
      void         handle_reading_from_tty();
      void         output_deps();
      int          what_to_return();

      void push_indent(int p) { indent.push_back(p); }

      // for handle_pre_light:
      int pregentype;

      // for getnext:
      char prevlastchar;

};

#endif
