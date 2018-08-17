#ifndef FINDENTCLASS_H
#define FINDENTCLASS_H

#include "flags.h"
#include "findent_types.h"

class Findent
{
   public:
      void init(Flags f)
      {
	 cur_indent   = 0;
	 start_indent = 0;
	 nbseen       = 0;
	 endline      = "\n";

	 flags        = f;
      }

   protected:

      Flags       flags;
      int         cur_indent;
      int         start_indent;
      bool        nbseen;
      indent_t    indent;          // to store indents
      std::string endline;

      void        init_indent();
      void        push_indent(int p);
      int         guess_indent(fortranline line);
};

#endif
