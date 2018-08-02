#include <string>
#include <algorithm>

#include "fixed2fixed.h"
#include "findent.h"
#include "findent_functions.h"
#include "findent_types.h"

void fixed2fixed(lines_t &lines)
{
   unsigned int old_indent   = 0;
   unsigned int first_indent = 0;
   char prevquote            = ' ';

   while(!lines.empty())
   {
      mycout.reset();
      std::string s   = lines.front().line();
      if (!handle_pre(lines,0))
      {
	 if(lines.front().blank_or_comment())
	 {
	    //
	    // this is an empty line or comment line
	    //
	    if (firstchar(lines.front().orig()) == '!')                   // do not change lines starting with !
	       mycout << lines.front().rtrim() << endline;
	    else if ( lines.front().firstchar() == "!")             // indent indented comments
	       mycout << std::string(6+cur_indent,' ') << trim(s) << endline;
	    else
	       mycout << trim(s) << endline;
	 }
	 else if(!cleanfive(lines.front().orig())) // check for valid label field
	    mycout << lines.front().orig() << endline;  // garbage in, garbage out
	 else
	 {
	    mycout << s.substr(0,6);

	    if(s.length() > 6)
	    {
	       bool iscont = (s[5] != ' ' && s[5] != '0');
	       //
	       // try to honor current indentation
	       // if this is a continuation line, count the number
	       // of spaces after column 6.
	       //
	       if (iscont)
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
	    }
	    mycout << endline;
	 }
      lines.pop_front();
      }
   }
}
