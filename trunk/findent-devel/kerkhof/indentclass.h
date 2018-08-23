#ifndef INDENTCLASS_H
#define INDENTCLASS_H

#include <iostream>
#include <string>

#include "fortranline.h"
#include "flags.h"
#include "findent_types.h"

class Indent
{
   public:
      void set(int i)
      {
	 testint = i;
      }

      int get()
      {
	 return testint;
      }
   protected:

      void        init_indent();
      void        push_indent(int p);
      std::string handle_dos(const std::string &s);
      int         guess_indent(Fortranline line);

      static int          all_indent;
      static int          cur_indent;
      static std::string  endline;
      static bool         endline_set;
      static bool         end_of_file;
      static Flags        flags;
      static bool         indent_handled;
      static indent_t     indent;          // to store indents
      static int          input_format;
      static bool         nbseen;
      static int          start_indent;


      static int testint;
};

#endif
