#include <algorithm>
#include <string>

#include "debug.h"
#include "findent.h"
#include "findent_functions.h"
#include "findent_types.h"

void free2free(lines_t &lines)
{
   //
   // output lines input: free format, output: free format
   //

   ppp<<"free2free lines"<<lines<<endchar;
   bool isfirst = 1;
   while (!lines.empty())
   {
      mycout.reset();

      // TODO: combine output of pre and blank and comments
      if(output_pre(lines))
	 continue;
      if (lines.empty())
	 return;

      if (lines.front().blank())    
      {
	 //
	 // a completely blank line, that is simple:
	 //
	 mycout << endline;
	 lines.pop_front();
	 continue;
      }

      if (lines.front().comment())
      {
	 if (lines.front()[0] != '!')
	    //
	    // take care of the situation that cur_indent == 0
	    // but the comment does not start in column 1
	    //
	    mycout << blanks(std::max(cur_indent,1));

	 mycout << lines.front().trim() << endline;
	 lines.pop_front();
	 continue;
      }

      //
      // this is a line with (part of) a fortran statement
      // possibly a continuation line
      //

      if(isfirst)
      {
	 //
	 // found the first statement line
	 // if label: handle it
	 //
	 isfirst = 0;
	 if (flags.label_left && labellength > 0)
	 {
	    //
	    // put label at start of line
	    //
	    std::string firstline  = lines.front().trim();
	    std::string label = firstline.substr(0,labellength);
	    firstline         = trim(firstline.substr(labellength));
	    int l = std::max(cur_indent - labellength,1);  // put at least one space after label
	    mycout << label << blanks(l) << firstline << endline;
	    lines.pop_front();
	    continue;
	 }
	 //
	 // this is the first code line without label. Always indent
	 // (even if it starts with '&')
	 //
	 mycout << blanks(std::max(cur_indent,0)) << lines.front().trim() << endline;
	 lines.pop_front();
	 continue;
      }

      //
      // handle next lines, these should be continuation lines
      //
      //
      // if continuation starts with '&', use current indentation
      // else use current indentation + flags.cont_indent 
      //

      if (lines.front().firstchar() == "&")
      {
	 mycout << blanks(std::max(cur_indent,0)) << lines.front().trim() << endline;
	 lines.pop_front();
	 continue;
      }

      if (flags.indent_cont)    // indentation of continuation lines is requested
      {
	 int l = std::max(cur_indent+flags.cont_indent,0);
	 mycout << blanks(l) << lines.front().trim() << endline;
	 lines.pop_front();
	 continue;
      }
      //
      // this line is a continuation line, without preceding '&'
      // and it has been requested that no indentation is done for 
      // continuation lines
      //
      mycout << lines.front().rtrim() << endline;
      lines.pop_front();
   }
}
