#include "findent.h"
#include "findent_functions.h"
#include "free2fixed.h"
#include "fixed2fixed.h"
#include "findent_types.h"
void free2fixed(lines_t curlines)
{
   std::list<fortranline> localcurlines;
   std::string s  = curlines.front().trimmed_line();
   std::string os = curlines.front().orig();
   std::string outputline;
   std::string lc = curlines.front().lastchar();

   std::string ofc = std::string(1,firstchar(os));
   std::string fc = curlines.front().firstchar();
   bool iscontinuation = 0;
   curlines.pop_front();
   if(!handle_pre(0, curlines, localcurlines))
   {
      if (flags.label_left && labellength > 0)  // this is a line starting with a label
      {
	 //
	 // put label at start of line
	 //
	 std::string label = s.substr(0,labellength);
	 s         = trim(s.substr(labellength));
	 outputline        = label + "       " + s;
      }
      else if (ofc == "!")    // this is a comment line with "!" in column 1
	 outputline = os;
      else if(fc == "!")    //  this is a comment line with "!" after column 1
	 outputline = "      "+s;
      else if (fc == "&")  // line like '  &  x+10', output: '     &  x+10'
	 // BTW: this should not happen for the first line
      {
	 iscontinuation = 1;
	 outputline     = "      " + ltrim(os).substr(1);    
      }
      else
	 outputline = "      " + os;
      if (lastchar(outputline) == '&')    // a continuation line will follow
      {
	 needcon    = 1;
	 outputline = outputline.substr(0,outputline.length()-1); // remove trailing &
      }
      if (iscontinuation)   // again, this should not happen
      {
	 outputline = outputline.substr(0,5) + "&" + outputline.substr(6);
      }
      localcurlines.push_back(outputline);
   }

   while (!curlines.empty())
   {
      //
      // sometimes, there are preprocessor statements within a continuation ...
      //
      fc  = curlines.front().firstchar();
      ofc = curlines.front().orig().substr(0,1);
      s   = curlines.front().trimmed_line();
      os  = curlines.front().orig();
      lc = curlines.front().lastchar();
      curlines.pop_front();
      if(!handle_pre(0,curlines, localcurlines))
      {
	 iscontinuation = needcon;
	 if (ofc == "!")    // this is a comment line with "!" in column 1
	    outputline = os;
	 else if (fc == "!")    //  this is a comment line with "!" after column 1
	    outputline = "      "+s;
	 else if (fc == "&")  // line like '  &  x+10', output: '     &  x+10'
	 {
	    iscontinuation = 1;
	    outputline     = "      " + ltrim(os).substr(1);    
	 }
	 else
	    outputline = "      " + os;
	 if (lastchar(outputline) == '&')    // a continuation line will follow
	 {
	    needcon    = 1;
	    outputline = outputline.substr(0,outputline.length()-1); // remove trailing &
	 }
	 if (iscontinuation)   
	 {
	    outputline = outputline.substr(0,5) + "&" + outputline.substr(6);
	 }
	 localcurlines.push_back(outputline);
      }
   }
   curlines = localcurlines;

#if 0
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
