#ifndef FINDENTCLASS_H
#define FINDENTCLASS_H

class Readlines;

#include "readlines.h"
#include "indentclass.h"

class Findent : public Indent
{
   public:
      Findent() {}

      Findent(Flags &f)
      {
	 cur_indent       = 0;
	 endline          = "\n";
	 endline_set      = 0;
	 flags            = f;
	 input_format     = UNKNOWN;
	 lines_read       = 0;
	 nbseen           = 0;
	 output_format    = 0;
	 reading_from_tty = 0;
	 start_indent     = 0;
	 num_lines        = 0;
	 labellength      = 0;
	 end_of_file      = 0;
	 cur_rprop        = empty_rprop;

	 Fortranline::line_length(flags.input_line_length);
	 Fortranline::gnu_format(flags.input_format_gnu);

	 input_format = flags.input_format;
      }

      int run();

   protected:

      Readlines     *rl;
      prop_t        cur_rprop;
      int           end_of_file;
      int           input_format;
      int           labellength;
      int           lines_read;
      int           num_lines;
      int           output_format;
      bool          reading_from_tty;
      int           start_indent;

      int           determine_fix_or_free();
      int           guess_fixedfree(Fortranline &line);
      void          handle_pre_light(Fortranline &line, bool &p_more);
      void          handle_reading_from_tty();
      int           what_to_return();
};

#endif
