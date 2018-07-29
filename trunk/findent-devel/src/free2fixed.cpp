#include <iostream>
#include <string>
#include <sstream>

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
   ppp("1:",lines);
   if(!handle_pre(lines,&nlines))
   {
      ppp("2:",lines);
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
	    //mycout << label;
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
	 //mycout << std::string(l,' '); 
	 os << std::string(l,' ');
      }
      //mycout << firstline << endline;
      if(firstline.length() > 0)
	 if(firstline[firstline.length()-1] == '&')
	    firstline = firstline.substr(0,firstline.length()-1);
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
      ppp("3:",lines);
      if(!handle_pre(lines,&nlines))
      {
	 ppp("4:",lines);
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
	       os << "     a";
	       //
	       // if last char is '&', discard it
	       //
	       if (s.length() > 0)
		  if(s[s.length()-1] == '&')
		     s = s.substr(0,s.length() - 1);
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
   ppp("result:",nlines);
}
