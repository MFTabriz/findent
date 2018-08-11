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
   os.str("");

   while (!lines.empty())
   {
      os.str("");
      std::string fc  = lines.front().firstchar();
      std::string s ;
      //
      // this must be a continuation or a comment line
      //

      if (lines.front()[0] == '!')
	 os << lines.front().str();
      else if (fc == "!")
	 os << " " << lines.front().str();
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
   fortranline::g_format(FIXED);
   fixed2fixed(nlines);
   fortranline::g_format(FREE);
}
