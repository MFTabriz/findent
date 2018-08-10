#include <algorithm>
#include <sstream>
#include <string>

#include "debug.h"
#include "fixed2fixed.h"
#include "findent.h"
#include "findent_functions.h"
#include "findent_types.h"

bool wizard(lines_t lines);
std::string add_amp(const std::string s,const char prevquote);

void fixed2fixed(lines_t &lines,lines_t *freelines)
{
   //
   // output lines input: fixed format, output: fixed format
   //
   // lines optionally start with comments and/or preprocessor lines
   // lines ends with a fortran line
   //
   bool to_mycout                   = freelines == 0;
   unsigned int old_indent          = 0;
   static unsigned int first_indent = 0;
   static char prevquote            = ' ';
   bool isfirst = 1;

   std::ostringstream os;

   ppp<<"fixed2fixed fs"<<full_statement << endchar;
   ppp<<"fixed2fixed lines"<<lines << endchar;

   while(!lines.empty())
   {
      mycout.reset();

      // TODO: combine output of pre and blank and comments
      if(output_pre(lines,freelines))
	 continue;
      if (lines.empty())
	 return;

      if (lines.front().blank())    
      {
	 //
	 // a completely blank line, that is simple:
	 //
	 if(to_mycout)
	    mycout << endline;
	 else
	 {
	    freelines->push_back(fortranline(""));
	    os.str("");
	 }
	 lines.pop_front();
	 continue;
      }

      if (lines.front().comment())
      {
	 if (lines.front().firstchar() == "!")
	 {
	    if (lines.front().orig().substr(0,1) != "!")
	       //
	       // take care of the situation that cur_indent == 0
	       // but the comment does not start in column 1
	       //
	    {
	       if(to_mycout)
		  mycout << blanks(std::max(cur_indent+6,1));
	       else
		  os << blanks(1);
	    }
	 }
	 if(to_mycout)
	    mycout << lines.front().trim() << endline;
	 else
	 {
	    int l = 1;
	    if (stoupper(lines.front().firstchar()) == "D")
	       l = 0;
	    os << "!" << lines.front().trim().substr(l);
	    freelines->push_back(os.str());
	    os.str("");
	 }
	 lines.pop_front();
	 continue;
      }

      //
      // this is a line with (part of) a fortran statement
      // possibly a continuation line
      //

      std::string s = lines.front().line(); // see fortranline.h for an explanation

      //
      // if this is not the first line, and label field is not empty:
      // garbage in, garbage out
      //

      if(!cleanfive(s))
      {
	 //
	 // garbage in, garbage out
	 //
	 if(to_mycout)
	    mycout << lines.front().rtrim() << endline;
	 else
	 {
	    os << lines.front().rtrim();
	    freelines->push_back(os.str());
	    os.str("");
	 }

	 lines.pop_front();
	 continue;
      }

      if(s.length() > 6)
      {
	 isfirst = 0;
	 //
	 // output label field including possible continuation character
	 //
	 if(to_mycout)
	    mycout << s.substr(0,6);
	 else
	    os << s.substr(0,5);

	 bool iscontinuation = (s[5] != ' ' && s[5] != '0');
	 //
	 // try to honor current indentation
	 // if this is a continuation line, count the number
	 // of spaces after column 6.
	 //
	 if (iscontinuation)
	 {
	    std::string s6 = ltab2sp(s.substr(6))+'x';
	    old_indent = s6.find_first_not_of(' ');
	    if (!to_mycout)
	       os << "&";
	 }
	 else
	 {
	    //
	    // count the number of spaces after column 6 of the first line
	    //
	    std::string s6 = ltab2sp(s.substr(6))+'x';
	    first_indent = s6.find_first_not_of(' ');
	 }
	 int adjust_indent = old_indent - first_indent;
	 if (adjust_indent < 0)
	    adjust_indent = 0;

	 switch(prevquote)
	 {
	    case ' ' :   // no dangling strings, output with indent
	       if(to_mycout)
		  mycout << blanks(std::max(adjust_indent+cur_indent,0)) << trim(s.substr(6));
	       else
		  os << trim(s.substr(6));
	       break;
	    default:  // dangling string, output asis
	       if(to_mycout)
		  mycout << s.substr(6);
	       else
		  os << s.substr(6);
	       break;
	 }
	 //
	 // investigate if this line terminates a string
	 //
	 prevquote = fixedmissingquote(prevquote + s);
	 if(to_mycout)
	    mycout << endline;
	 else
	 {
	    char c;
	    if (wizard(lines))       // more fortran lines follow
	    {
	       c = ' ';
	       if(iscontinuation)
		  c = prevquote;
	       freelines->push_back(add_amp(os.str(),c));
	    }
	    else
	       freelines->push_back(os.str());
	    os.str("");
	 }
	 lines.pop_front();
	 continue;
      }
      //
      // output a line that does not fulfill above conditions
      //
      if(to_mycout)
	 mycout << s << endline;
      else
      {
	 os << s;
	 if (wizard(lines))       // more fortran lines follow
	    freelines->push_back(add_amp(os.str(),prevquote));
	 else
	    freelines->push_back(os.str());
	 os.str("");
      }
      lines.pop_front();
   }
}

bool wizard(lines_t lines)
{
   // finds out if lines.front() gets a continuation line

   if(lines.empty())
      return 0;

   lines_t::iterator it = lines.begin();
   it++;
   while(it != lines.end())
   {
      if(it->fortran())
      {
	 if (it->orig().length() < 6)
	    return 0;
	 if (it->orig()[5] != ' ' && it->orig()[5] != '0') 
	    return 1;
	 return 0;
      }
      it++;
   }
   return 0;
}

std::string add_amp(const std::string s,const char prevquote)
{
   std::string sl      = remove_trailing_comment(s,prevquote);
   std::string slt     = rtrim(sl);
   std::string so      = slt + "&" + s.substr(slt.length());
   return so;
}
