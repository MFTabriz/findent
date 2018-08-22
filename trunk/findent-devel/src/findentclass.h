#ifndef FINDENTCLASS_H
#define FINDENTCLASS_H

#include "nflags.h"
#include "prop.h"
#include "nfindent_types.h"
#include "ndebug.h"
#include "nfortranline.h"
#include "globals.h"

class Findent
{

   public:
      Findent() {}

      Findent(Flags &f)
      {
	 // public
	 gl                 = new Globals;
	 cur_indent         = 0;
	 cur_rprop          = empty_rprop;
	 end_of_file        = 0;
	 end_of_file        = 0;
	 endline            = "\n";
	 flags              = f;
	 indent_handled     = 0;
	 nbseen             = 0;
	 num_lines          = 0;
	 gl->global_format      = UNKNOWN;
	 gl->global_gnu_format  = 0;
	 gl->global_line_length = 0;

	 // private
	 all_indent         = 0;
	 endline_set        = 0;
	 input_format       = UNKNOWN;
	 input_format       = flags.input_format;
	 labellength        = 0;
	 lines_read         = 0;
	 output_format      = 0;
	 reading_from_tty   = 0;
	 start_indent       = 0;
      }

      void set(int what){ testint = what;}
      int  get()        { return testint;} //testing

      Fortranline getnext(bool &eof, bool use_wb = 1);
      Fortranline mygetline(bool &eof, bool buffer = 0);

      void         init_indent();
      int          run();

      int          cur_indent;
      std::string  endline;
      bool         end_of_file;
      Flags        flags;
      Globals*     gl;
      bool         indent_handled;
      indent_t     indent;          // to store indents
      bool         nbseen;
      int          num_lines;

// testing
      int          testint;
      class testje;
      testje *ttt;
// /testing

   private:

      int          all_indent;
      linebuffer_t curlinebuffer;   // deque for source lines
      prop_t       cur_rprop;
      bool         endline_set;
      int          input_format;
      int          labellength;
      int          lines_read;
      int          output_format;
      bool         reading_from_tty;
      int          start_indent;
      linebuffer_t wizardbuffer;    // to store wizard lines and push back lines from handle_fortran

      int          determine_fix_or_free();
      int          guess_fixedfree(Fortranline &line);
      int          guess_indent(Fortranline line);
      std::string  handle_dos(const std::string &s);
      void         handle_pre_light(Fortranline &line, bool &p_more);
      void         handle_reading_from_tty();
      void         push_indent(int p);
      int          what_to_return();



};

class testje : public Findent
{
   public:
      void doit()        { i = num_lines; }
      void ttt_1();
      int i;
};

#endif
