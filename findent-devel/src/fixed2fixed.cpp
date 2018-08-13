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

size_t cindex = 0;

void fixed2fixed(lines_t &lines,lines_t *freelines)
{
   //
   // output lines input: fixed format, output: fixed format
   //
   // lines optionally start with comments and/or preprocessor lines
   // lines ends with a fortran line
   //
   bool to_mycout            = (freelines == 0);
   unsigned int old_indent   = 0;
   unsigned int first_indent = 0;
   char prevquote            = ' ';

   std::ostringstream os;

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
	 if (lines.front().firstchar() == '!')
	 {
	    if (lines.front()[0] != '!')
	       //
	       // take care of the situation that cur_indent == 0
	       // but the comment does not start in column 1
	       //
	    {
	       if(to_mycout)
		  mycout << blanks(M(std::max(cur_indent+6,1)));
	       else
		  os << blanks(1);
	    }
	 }
	 if(to_mycout)
	    mycout << lines.front().trim() << endline;
	 else
	 {
	    int l = 1;
	    if (toupper(lines.front().firstchar()) == 'D')
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

      std::string s = lines.front().str();

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
	 bool iscontinuation = lines.front().fixedcontinuation();
	 if (iscontinuation)
	 {
	    const std::string cc = "123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	    if (flags.conchar != ' ')
	    {
	       if (flags.conchar == '0')
	       {
		  s.at(5) = cc[cindex];
		  cindex++;
		  if (cindex >= cc.length())
		     cindex = 0;
	       }
	       else
		  s.at(5) = flags.conchar;
	    }
	 }
	 //
	 // output label field including possible continuation character
	 //
	 if(to_mycout)
	    mycout << s.substr(0,6);
	 else
	    os << s.substr(0,5);

	 //
	 // try to honor current indentation
	 // if this is a continuation line, count the number
	 // of spaces after column 6.
	 //
	 if (iscontinuation)
	 {
	    std::string s6 = s.substr(6)+'x';
	    old_indent     = s6.find_first_not_of(' ');
	    if (!to_mycout)
	       os << "&";
	 }
	 else
	 {
	    //
	    // count the number of spaces after column 6 of the first line
	    //
	    std::string s6 = s.substr(6)+'x';
	    first_indent = s6.find_first_not_of(' ');
	    cindex = 0;
	 }
	 int adjust_indent = old_indent - first_indent;
	 if (adjust_indent < 0)
	    adjust_indent = 0;

	 switch(prevquote)
	 {
	    case ' ' :   // no dangling strings, output with indent
	       if(to_mycout)
		  mycout << blanks(M(std::max(adjust_indent+cur_indent,0))) 
		     << trim(s.substr(6));
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
      if (it-> fortran())
	 return it->fixedcontinuation();
      it++;
   }
   return 0;
}

std::string add_amp(const std::string s,const char p)
{
   //
   // examples:
   // s = "abc ! xyz",  p = ' '   :  result = "abc& ! xyz"
   // s = "ab'c ! xyz", p = ' '   :  result = "ab'c ! xyz&"
   // s = "abc ! xyz",  p = '\''  :  result = "abc ! xyz&"
   // s = "ab'c ! xyz", p = '\''  :  result = "ab'c& ! xyz"
   // p can be ' ', '\'', '"'
   //
   std::string slt = rtrim(remove_trailing_comment(s,p));
   return slt + "&" + s.substr(slt.length());
}

