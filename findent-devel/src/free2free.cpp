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
   static bool p_more = 0;
   ppp("free2free lines",lines);
   ppp("free2free fs",fs_store);

   continuation = lines.front().orig() == "C";
   lines.pop_front();
   if (lines.empty())
      return;

   if (!continuation)
   {
      //
      // if 'lines' starts with preprocessor lines, we assume that
      // these are already taken care of in terms of adjusting
      // various stacks, so the only thing to do is output them here.
      // (If we would take care of them here, we would be too late:
      //  at this point the indentation has already be computed)
      //

      if (lines.front().pre())
      {
	 bool p_more = 0;
	 while(1)
	 {
	    handle_pre_light1(lines.front(),p_more);
	    if (lines.front().pre())
	       mycout << lines.front().ltrim() << endline;
	    else
	       mycout << lines.front().orig() << endline;
	    lines.pop_front();
	    if (lines.empty() || !p_more)
	       break;
	 }
	 if (lines.empty())
	    return;
      }


      std::string firstline  = lines.front().trimmed_line();
      if(!iscon)
      {
	 mycout.reset();
	 if (firstline != "" || lines.size() > 1)
	 {
	    int l;
	    continuation = (lastchar(firstline) == '&');
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
   }

   // handle continuation lines:

   while (!lines.empty())
   {
      mycout.reset();

      std::string fc  = lines.front().firstchar();

      //
      // here we have a preprocessor line in the middle of a continuation.
      // I was not able to solve this adequately, alas. 
      //
      if (lines.front().pre())
      {
	 ppps("nextline pre",lines.front().orig());
	 while(1)
	 {
	    handle_pre_light1(lines.front(), p_more);
	    if (lines.front().pre())
	       mycout << lines.front().ltrim() << endline;
	    else
	       mycout << lines.front().orig() << endline;
	    lines.pop_front();
	    if (lines.empty() || !p_more)
	       break;
	 }
	 if (lines.empty())
	    return;
      }

      ppp("free2free2 fs",fs_store);
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
	    if(continuation)
	    {
	       if (fc == "&")
		  l = std::max(cur_indent,0);
	       else
		  l = std::max(cur_indent+flags.cont_indent,0);
	    }
	    else
	       l = cur_indent;
	 }
	 //
	 // if this is a comment line, and the original line did not start
	 // with '!', and cur_indent == 0: put a at least one space before this line, 
	 // to make sure that re-indenting will give the same result
	 //
	 if (ofc != "!" && fc == "!" && cur_indent == 0)
	    l=std::max(1,flags.cont_indent);
	 if (!lines.front().blank_or_comment_or_pre())
	    continuation = continuation || (lines.front().lastchar() == "&");
	 mycout << std::string(l,' ');
	 mycout << lines.front().trimmed_line() << endline;
      }
      else
	 mycout << lines.front().orig() << endline;
      lines.pop_front();
   }
}
