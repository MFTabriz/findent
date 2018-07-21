#include "fixed2fixed.h"
#include "findent.h"
#include "findent_functions.h"
void fixed2fixed()
{
   unsigned int old_indent   = 0;
   unsigned int first_indent = 0;
   char prevquote            = ' ';

   //while(!lines.empty())
   while(!curlines.empty())
   {
      mycout.reset();
      std::string s  = lines.front();
      std::string os = olines.front();
      char ofc       = firstchar(os);
      char ftc       = firstchar(trim(s));
      lines.pop_front();
      olines.pop_front();
      curlines.pop_front();
      lexer_set(s,SCANFIXPRE);
      int pretype = yylex();
      if (handle_pre(s,pretype))
	 continue;
      if(isfixedcmtp(s))
      {
	 //
	 // this is an empty line or comment line
	 //
	 if (ofc == '!')                   // do not change lines starting with !
	    mycout << rtrim(os) << endline;
	 else if ( ftc == '!')             // indent indented comments
	    mycout << std::string(6+cur_indent,' ') << trim(s) << endline;
	 else
	    mycout << trim(s) << endline;
      }
      else if(!cleanfive(os)) // check for valid label field
      {
	 mycout << os << endline;  // garbage in, garbage out
      }
      else
      {
	 if (output_format == FIXED)
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
      }
   }
}
