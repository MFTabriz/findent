#include <algorithm>
#include <string>

#include "debug.h"
#include "fixed2fixed.h"
#include "findent.h"
#include "findent_functions.h"
#include "findent_types.h"

void fixed2fixed(lines_t &lines)
{
   //
   // output lines input: fixed format, output: fixed format
   //
   //
   unsigned int old_indent          = 0;
   static unsigned int first_indent = 0;
   static char prevquote            = ' ';

   bool isfirst = 1;

   ppp<<"fixed2fixed fs"<<full_statement << endchar;
   ppp<<"fixed2fixed lines"<<lines << endchar;

   while(!lines.empty())
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
	 if (lines.front().firstchar() == "!")
	 {
	 if (lines.front().orig().substr(0,1) != "!")
	    //
	    // take care of the situation that cur_indent == 0
	    // but the comment does not start in column 1
	    //
	    mycout << blanks(std::max(cur_indent+6,1));
	 }

	 mycout << lines.front().trim() << endline;
	 lines.pop_front();
	 continue;
      }

      //
      // this is a line with (part of) a fortran statement
      // possibly a continuation line
      //

      std::string s = lines.front().line(); // see fortranline.h for an explanation

      //
      // if this is not the first line, and label field is not empty:
      // garbage in, garbage out
      //

      if(!cleanfive(s))
      {
	 mycout << lines.front().rtrim() << endline;  // garbage in, garbage out
	 lines.pop_front();
	 continue;
      }

      if(s.length() > 6)
      {
	 isfirst = 0;
	 //
	 // output label field including possible continuation character
	 //
	 mycout << s.substr(0,6);

	 bool iscontinuation = (s[5] != ' ' && s[5] != '0');
	 //
	 // try to honor current indentation
	 // if this is a continuation line, count the number
	 // of spaces after column 6.
	 //
	 if (iscontinuation)
	 {
	    std::string s6 = ltab2sp(s.substr(6))+'x';
	    old_indent = s6.find_first_not_of(' ');
	 }
	 else
	 {
	    //
	    // count the number of spaces after column 6 of the first line
	    //
	    std::string s6 = ltab2sp(s.substr(6))+'x';
	    first_indent = s6.find_first_not_of(' ');
	 }
	 int adjust_indent = old_indent - first_indent;
	 if (adjust_indent < 0)
	    adjust_indent = 0;

	 switch(prevquote)
	 {
	    case ' ' :   // no dangling strings, output with indent
	       mycout << std::string(std::max(adjust_indent+cur_indent,0),' ') << trim(s.substr(6));
	       break;
	    default:  // dangling string, output asis
	       mycout << s.substr(6);
	       break;
	 }
	 //
	 // investigate if this line terminates a string
	 //
	 prevquote = fixedmissingquote(prevquote + s);
	 mycout << endline;
	 lines.pop_front();
	 continue;
      }
      //
      // output a line that does not fulfill above conditions
      //
      mycout << s << endline;
      lines.pop_front();
   }
}
