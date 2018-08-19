#ifndef FINDENTCLASS_H
#define FINDENTCLASS_H

#include "findent_types.h"
#include "flags.h"
#include "pre_analyzer.h"

class Findent
{
   public:
      int run(Flags &f);

   protected:

      int           cur_indent;
      linebuffer_t  curlinebuffer;   // deque for source lines
      prop_t        cur_rprop;
      std::string   endline;
      bool          endline_set;
      int           end_of_file;
      Flags         flags;
      indent_t      indent;          // to store indents
      int           input_format;
      int           labellength;
      int           lines_read;
      bool          nbseen;
      int           num_lines;
      int           output_format;
      bool          reading_from_tty;
      int           start_indent;

      int           determine_fix_or_free();
      int           guess_fixedfree(fortranline &line);
      int           guess_indent(fortranline line);
      std::string   handle_dos(const std::string &s);
      void          handle_last_usable_only();
      void          handle_pre_light(fortranline &line, bool &p_more);
      void          handle_reading_from_tty();
      void          init(Flags &f);
      void          init_indent();
      fortranline   mygetline(bool &eof);
      void          push_indent(int p);
      int           what_to_return();
};

#endif
