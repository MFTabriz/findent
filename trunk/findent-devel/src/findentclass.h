#ifndef FINDENTCLASS_H
#define FINDENTCLASS_H

#include <deque>
#include "nflags.h"
#include "prop.h"
#include "nfindent_types.h"
#include "parser.h"
#include "ndebug.h"

class Fortranline;

typedef std::deque<Fortranline>       lines_t;
typedef std::deque<Fortranline>       linebuffer_t;

class Findent
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

      input_format = flags.input_format;
      ppp.on();
      ppp<<"Findent()"<<endchar;
   }

   int run();

   Fortranline getnext(bool &eof, bool use_wb = 1);
   Fortranline mygetline(bool &eof, bool buffer = 0);

   void set(int what){ testint = what;}
   int  get()        { return testint;} //testing
   int testint;

   int get_num_lines()       { return num_lines; }

   Flags* get_flags()        { return &flags; }

   indent_t get_indent()     { return indent; }

   bool get_nbseen()         { return nbseen; }
   std::string get_endline() { return endline; }
   int get_cur_indent()      { return cur_indent; }
   bool get_end_of_file()    { return end_of_file; }

   void set_nbseen(bool what)      { nbseen = what; }
   void set_indent(indent_t what)  { indent = what; }
   void set_end_of_file(bool what)  { end_of_file = what; }
   void set_indent_handled(bool what)  { indent_handled = what; }


   void          init_indent();

   private:

   int          all_indent;
   int          cur_indent;
   linebuffer_t curlinebuffer;   // deque for source lines
   prop_t       cur_rprop;
   std::string  endline;
   bool         endline_set;
   bool         end_of_file;
   Flags        flags;
   int          global_format;
   bool         global_gnu_format;
   int          global_line_length;
   bool         indent_handled;
   indent_t     indent;          // to store indents
   int          input_format;
   int          labellength;
   int          lines_read;
   bool         nbseen;
   int          num_lines;
   int          output_format;
   bool         reading_from_tty;
   int          start_indent;
   linebuffer_t wizardbuffer;    // to store wizard lines and push back lines from handle_fortran



   int           determine_fix_or_free();
   int           guess_fixedfree(Fortranline &line);
   int           guess_indent(Fortranline line);
   std::string   handle_dos(const std::string &s);
   void          handle_pre_light(Fortranline &line, bool &p_more);
   void          handle_reading_from_tty();
   void          push_indent(int p);
   int           what_to_return();

};

#endif
