#include <iostream>
#include <string>
#include <sstream>

#include "debug.h"
#include "findent.h"
#include "findent_functions.h"
#include "free2fixed.h"
#include "fixed2fixed.h"
#include "findent_types.h"
#include "functions.h"

void free2fixed(lines_t &lines)
{
   lines_t nlines;
   std::ostringstream os;
   //
   // because continuation lines are handled slightly different
   // (user can choose between indent or original), the first
   // line is treated separately
   //
   std::string firstline  = lines.front().trimmed_line();
   if(!handle_pre(lines,0,&nlines))
   {
      os.str("");
      int l=6;
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
	    os << label << "      ";
	 }
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
	 os << std::string(l,' ');
      }
      //
      // if last char is '&', discard it
      // take care of trailing comment
      //
      std::string f1 = rtrim(remove_trailing_comment(firstline));

      if (f1.length() > 0)
	 if(f1[f1.length()-1] == '&')
	    firstline = f1.substr(0,f1.length()-1)+firstline.substr(f1.length());
      os << firstline;
      nlines.push_back(os.str());
      lines.pop_front();
   }

   while (!lines.empty())
   {
      os.str("");
      //
      // sometimes, there are preprocessor statements within a continuation ...
      //
      std::string fc  = lines.front().firstchar();
      std::string s ;
      if(!handle_pre(lines,0,&nlines))
      {
	 //
	 // this must be a continuation or a comment line
	 //

	 std::string ofc = lines.front().orig().substr(0,1);
	 if (ofc == "!")
	    os << lines.front().orig();
	 else if (fc == "!")
	    os << " " << lines.front().orig();
	 else
	 {
	    s = lines.front().trimmed_line();
	    //
	    // this must be a continuation line
	    //
	    if (flags.indent_cont || fc == "&")
	    {
	       //
	       // if continuation starts with '&', chop off '&'
	       //
	       if (fc == "&")
		  s = s.substr(1);
	       os << "     &";
	       //
	       // if last char is '&', discard it
	       // take care of trailing comment
	       //
	       std::string s1 = rtrim(remove_trailing_comment(s));

	       if (s1.length() > 0)
		  if(s1[s1.length()-1] == '&')
		     s = s1.substr(0,s1.length()-1)+s.substr(s1.length());
	       os << s;
	    }
	    else
	    {
	       std::string s = lines.front().rtrim();
	       if (s.length() > 0)
		  if(s[s.length()-1] == '&')
		     s = s.substr(0,s.length() - 1);
	       os << "     &" + s;
	    }
	 }
	 nlines.push_back(os.str());
	 lines.pop_front();
      }
   }
   fortranline::setformat(FIXED);
   fixed2fixed(nlines);
   fortranline::setformat(FREE);
}
