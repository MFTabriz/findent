#include <algorithm>
#include <string>
#include "findent.h"
#include "findent_functions.h"
#include "findent_types.h"
void free2free(lines_t &lines)
{
   //
   // because continuation lines are handled slightly different
   // (user can choose between indent or original), the first
   // line is treated separately
   //
   std::string firstline  = lines.front().trimmed_line();
   if(!handle_pre(lines))
   {
      int l=0;
      if (firstline != "" || lines.size() > 1)
      {
	 std::string ofc = lines.front().orig().substr(0,1);
	 if (flags.label_left && labellength > 0)
	 {
	    //
	    // put label at start of line
	    //
	    std::string label = firstline.substr(0,labellength);
	    firstline         = trim(firstline.substr(labellength));
	    mycout << label;
	    l = cur_indent - labellength;
	    if ( l <= 0 )
	       l=1;
	 }
	 else
	    l = cur_indent;
	 //
	 // If first character of original line is '!', do not indent
	 // Do not use start_indent: on the next run the first char could
	 // be space and not '!'
	 //
	 if(ofc == "!")
	    l=0;
	 //
	 // if this is a comment line, and the original line did not start
	 // with '!', and cur_indent == 0: put a space before this line, 
	 // to make sure that re-indenting will give the same result
	 //
	 if (ofc != "!" && firstchar(firstline) == '!' && cur_indent == 0)
	    l=1;

	 if (l<0)
	    l=0;
	 mycout << std::string(l,' '); 
      }
      mycout << firstline << endline;
      lines.pop_front();
   }

   while (!lines.empty())
   {
      mycout.reset();
      //
      // sometimes, there are preprocessor statements within a continuation ...
      //
      std::string fc  = lines.front().firstchar();
      std::string s ;
      if(!handle_pre(lines))
      {
	 std::string ofc = lines.front().orig().substr(0,1);
	 if (flags.indent_cont || fc == "&")
	 {
	    int l = 0;
	    //
	    // if first character of original line == '!', do not indent
	    // Do not use start_indent: on the next run the first char could
	    // be space and not '!'
	    //
	    if (ofc == "!")
	       l = 0;
	    else
	    {
	       //
	       // if continuation starts with '&', use current indentation
	       // else use current indentation + flags.cont_indent 
	       //
	       if (fc == "&")
		  l = std::max(cur_indent,0);
	       else
		  l = std::max(cur_indent+flags.cont_indent,0);
	    }
	    //
	    // if this is a comment line, and the original line did not start
	    // with '!', and cur_indent == 0: put a at least one space before this line, 
	    // to make sure that re-indenting will give the same result
	    //
	    if (ofc != "!" && fc == "!" && cur_indent == 0)
	       l=std::max(1,flags.cont_indent);
	    mycout << std::string(l,' ');
	    mycout << lines.front().trimmed_line() << endline;
	 }
	 else
	    mycout << lines.front().orig() << endline;
	 lines.pop_front();
      }
   }
}
