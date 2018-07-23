#include "findent.h"
#include "findent_functions.h"
void free2fixed()
{
   std::list<fortranline>   localcurlines;
   std::string              localline;
   fortranline              flocalline;
   std::string firstline  = curlines.front().trimmed_line();
   std::string ofirstline = curlines.front().orig();

   char ofc               = firstchar(ofirstline);
   int pretype = curlines.front().scanfixpre();
   curlines.pop_front();
   if(!handle_pre(firstline, pretype))
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
	    //mycout << label;
	    localline = label;
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
	 //mycout << std::string(l,' '); 
      }
      //mycout << firstline << endline;
      localline = localline + "       " + firstline;
      localcurlines.push_back(fortranline(localline));
   }

   while (!curlines.empty())
   {
      mycout.reset();
      //
      // sometimes, there are preprocessor statements within a continuation ...
      //
      std::string fc  = curlines.front().firstchar();
      std::string fc2 = curlines.front().first2chars();
      std::string ofc = curlines.front().orig().substr(0,1);
      std::string lc  = curlines.front().lastchar();
      int pretype     = curlines.front().scanfixpre();
      std::string s   = curlines.front().trimmed_line();
      std::string os  = curlines.front().orig();
      curlines.pop_front();
      std::string continuation = "\\";
      switch (pretype)
      {
	 case CPP:
	 case COCO:
	    if (pretype == COCO)
	       continuation = "&";
	    localcurlines.push_back(fortranline(os));
	    if (lc == continuation)
	    {
	       while
	    }
      }
      if(!handle_pre(s,pretype))
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
