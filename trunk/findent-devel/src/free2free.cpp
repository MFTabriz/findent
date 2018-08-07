#include <algorithm>
#include <string>

#include "debug.h"
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

   bool continuation = 0;
   ppp<<"free2free lines"<<lines<<endchar;
   ppp<<"free2free fs"<<fs_store<<endchar;

   if (lines.empty())
      return;

   //
   // if 'lines' starts with preprocessor lines, we assume that
   // these are already taken care of in terms of adjusting
   // various stacks, so the only thing to do is output them here.
   // (If we would take care of them here, we would be too late:
   //  at this point the indentation has already be computed)
   //


   output_pre(lines);
   if (lines.empty())
      return;

   continuation = lines.front().con();
   ppp<<"free2free continuation" << continuation<< endchar;
   if (!continuation)
   {
      std::string firstline  = lines.front().trimmed_line();
      mycout.reset();
      if (firstline != "" || lines.size() > 1)
      {
	 int l;
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

	 if (l < 0)
	    l = 0;
	 mycout << std::string(l,' '); 
      }
      mycout << firstline << endline;
      lines.pop_front();
   }

   // handle continuation lines:

   while (!lines.empty())
   {
      ppp<<"free2free next lines"<<lines<<endchar;
      mycout.reset();


      output_pre(lines);
	 if (lines.empty())
	    return;

      std::string fc  = lines.front().firstchar();
      ppp<<"free2free2 next fs"<<fs_store<<endchar;
      std::string s ;
      std::string ofc = lines.front().orig().substr(0,1);
      if (flags.indent_cont || fc == "&")
      {
	 int l;
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
