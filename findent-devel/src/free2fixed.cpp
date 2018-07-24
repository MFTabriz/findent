#include "findent.h"
#include "findent_functions.h"
#include "free2fixed.h"
#include "fixed2fixed.h"
void free2fixed(void)
{
   std::list<fortranline> localcurlines;
   std::string firstline  = curlines.front().trimmed_line();
   std::string ofirstline = curlines.front().orig();
   std::string outputline;
   std::string lc = curlines.front().lastchar();

   std::string ofc               = std::string(firstchar(ofirstline),1);
   std::string fc = curlines.front().firstchar();
   int pretype = curlines.front().scanfixpre();
   curlines.pop_front();
   if(!handle_pre(firstline, pretype, 0, localcurlines))
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
	    firstline         = trim(firstline.substr(labellength));
	    outputline        = label;
	    //mycout << label;
	    l = cur_indent - labellength;
	    if ( l <= 0 )
	       l=1;
	 }
	 else
	    l = cur_indent;
	 //
	 // if this is a comment line, and the original line did not start
	 // with '!', and cur_indent == 0: put a space before this line, 
	 // to make sure that re-indenting will give the same result
	 //
	 if (ofc != "!" && fc == "!" && cur_indent == 0)
	    l=1;

	 if (l<0)
	    l=0;
	 if(ofc == "!")
	    outputline = "";
	 else
	 {
	    l = l+6-labellength;
	    //mycout << std::string(l,' '); 
	    outputline += std::string(l,' ');
	 }
      }
      //mycout << firstline << endline;
      if (lc == "&" && fc != "!")
      {
	 needcon = 1;
	 firstline=firstline.substr(0,firstline.length()-1);
      }
      localcurlines.push_back(outputline+firstline);
   }

   while (!curlines.empty())
   {
      //mycout.reset();
      outputline = "";
      //
      // sometimes, there are preprocessor statements within a continuation ...
      //
      std::string fc  = curlines.front().firstchar();
      std::string ofc = curlines.front().orig().substr(0,1);
      int pretype     = curlines.front().scanfixpre();
      std::string s   = curlines.front().trimmed_line();
      std::string os  = curlines.front().orig();
      std::string lc = curlines.front().lastchar();
      curlines.pop_front();
      if(!handle_pre(s,pretype,0,localcurlines))
      {
	 if (flags.indent_cont || fc == "&")
	 {
	    int l = 0;
	    if (ofc == "!")
	       localcurlines.push_back(os);
	    else
	    {
	       if (fc == "!")
		  localcurlines.push_back(s);
	       else
	       {
		  if (needcon)
		     outputline = "     &";
		  else
		     outputline = "      ";
		  if (lc == "&")
		  {
		     needcon = 1;
		     s = s.substr(0,s.length()-1);
		  }
		  if (fc == "&")
		     s = s.substr(1);
		  localcurlines.push_back(outputline + s);
	       }
	    }

	    //mycout << std::string(l,' ');
	    //mycout << s <<endline;
	 }
	 else
	    //mycout << os << endline;
	    localcurlines.push_back(fortranline(os));
      }
   }
   curlines = localcurlines;
#if 1
   fixed2fixed();
#else
   std::cout << "----------------------" << needcon <<std::endl;
   while (!curlines.empty())
   {
      std::cout << curlines.front().orig()<<std::endl;
      curlines.pop_front();
   }
#endif
   fortranline::setformat(FREE);
}
