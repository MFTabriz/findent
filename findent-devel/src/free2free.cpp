#include "findent.h"
#include "findent_functions.h"
void free2free()
{
   std::string firstline  = curlines.front().trimmed_line();
   std::string ofirstline = curlines.front().orig();

   std::list<fortranline> dummy;
   char ofc               = firstchar(ofirstline);
   int pretype = curlines.front().scanfixpre();
   curlines.pop_front();
   if(!handle_pre(firstline, pretype, 1, dummy))
   {
      int l;
      if (firstline != "" || curlines.size() > 1)
      {
	 if (flags.label_left && labellength > 0)
	 {
	    //
	    // put label at start of line
	    //
	    std::string label = firstline.substr(0,labellength);
	    firstline    = trim(firstline.substr(labellength));
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
	 if(ofc == '!')
	    l=0;
	 //
	 // if this is a comment line, and the original line did not start
	 // with '!', and cur_indent == 0: put a space before this line, 
	 // to make sure that re-indenting will give the same result
	 //
	 if (ofc != '!' && firstchar(firstline) == '!' && cur_indent == 0)
	    l=1;

	 if (l<0)
	    l=0;
	 mycout << std::string(l,' '); 
      }
      mycout << firstline << endline;
   }

   while (!curlines.empty())
   {
      mycout.reset();
      //
      // sometimes, there are preprocessor statements within a continuation ...
      //
      std::string fc  = curlines.front().firstchar();
      std::string ofc = curlines.front().orig().substr(0,1);
      int pretype     = curlines.front().scanfixpre();
      std::string s   = curlines.front().trimmed_line();
      std::string os  = curlines.front().orig();
      curlines.pop_front();
      if(!handle_pre(s,pretype,1,dummy))
      {
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
	       if (fc == "&")
	       {
		  //
		  // if continuation starts with '&', use current indentation
		  // else use current indentation + flags.cont_indent 
		  //
		  l = std::max(cur_indent,0);
	       }
	       else
	       {
		  l = std::max(cur_indent+flags.cont_indent,0);
	       }
	    }
	    //
	    // if this is a comment line, and the original line did not start
	    // with '!', and cur_indent == 0: put a at least one space before this line, 
	    // to make sure that re-indenting will give the same result
	    //
	    if (ofc != "!" && fc == "!" && cur_indent == 0)
	       l=std::max(1,flags.cont_indent);
	    mycout << std::string(l,' ');
	    mycout << s <<endline;
	 }
	 else
	    mycout << os << endline;
      }
   }
}
