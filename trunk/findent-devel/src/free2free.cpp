#include <algorithm>
#include <string>
#include <sstream>

#include "debug.h"
#include "findent.h"
#include "findent_functions.h"
#include "findent_types.h"
#include "free2free.h"

std::string rm_last_amp(const std::string &s);

void free2free(lines_t &lines, lines_t *fixedlines)
{
   //
   // output lines input: free format, output: free format
   //

   bool to_mycout = (fixedlines == 0);
   std::ostringstream os;
   bool isfirst = 1;
   const char conchar = '&';
   std::string constring;

   if (flags.indent_cont)
      constring = std::string(1,conchar)+blanks(flags.cont_indent);
   else
      constring = std::string(1,conchar);
   constring = std::string(1,conchar);

   while (!lines.empty())
   {
      mycout.reset();

      // TODO: combine output of pre and blank and comments
      if(output_pre(lines,fixedlines))
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
	    fixedlines->push_back(fortranline(""));
	    os.str("");
	 }
	 lines.pop_front();
	 continue;
      }

      if (lines.front().comment())
      {
	 if (lines.front()[0] != '!')
	 {
	    //
	    // take care of the situation that cur_indent == 0
	    // but the comment does not start in column 1
	    //
	    if(to_mycout)
	       mycout << blanks(std::max(cur_indent,1));
	    else
	       os << blanks(std::max(cur_indent,1));
	 }

	 if(to_mycout)
	    mycout << lines.front().trim() << endline;
	 else
	 {
	    os << lines.front().trim();
	    fixedlines->push_back(rtrim(os.str()));
	    os.str("");
	 }
	 lines.pop_front();
	 continue;
      }

      //
      // this is a line with (part of) a fortran statement
      // possibly a continuation line
      //

      if(isfirst)
      {
	 //
	 // found the first statement line
	 // if label: handle it
	 //
	 isfirst = 0;
	 if (flags.label_left && labellength > 0)
	 {
	    //
	    // put label at start of line
	    //
	    std::string firstline = lines.front().trim();
	    std::string label     = firstline.substr(0,labellength);
	    firstline             = trim(firstline.substr(labellength));

	    int l = std::max(cur_indent - labellength,1);  // put at least one space after label
	    if(to_mycout)
	       mycout << label << blanks(l) << firstline << endline;
	    else
	    {
	       os << label << blanks(6) << firstline;
	       fixedlines->push_back(rm_last_amp(os.str()));
	       os.str("");
	    }

	    lines.pop_front();
	    continue;
	 }
	 //
	 // this is the first code line without label. Always indent
	 // (even if it starts with '&')
	 //
	 if(to_mycout)
	    mycout << blanks(std::max(cur_indent,0)) << lines.front().trim() << endline;
	 else
	 {
	    if(lines.front().firstchar() == '&')
	       os << blanks(5) << constring << lines.front().rtrim().substr(1);
	    else
	       os << blanks(5) << ' ' <<lines.front().rtrim();
	    fixedlines->push_back(rm_last_amp(os.str()));
	    os.str("");
	 }
	 lines.pop_front();
	 continue;
      }

      //
      // handle next lines, these should be continuation lines
      //
      //
      // if continuation starts with '&', use current indentation
      // else use current indentation + flags.cont_indent 
      //

      if (lines.front().firstchar() == '&')
      {
	 if(to_mycout)
	    mycout << blanks(std::max(cur_indent,0)) << lines.front().trim() << endline;
	 else
	 {
	    os << blanks(5) << constring << lines.front().trim().substr(1);
	    fixedlines->push_back(rm_last_amp(os.str()));
	    os.str("");
	 }
	 lines.pop_front();
	 continue;
      }

      if (flags.indent_cont)    // indentation of continuation lines is requested
      {
	 int l = std::max(cur_indent+flags.cont_indent,0);
	 if(to_mycout)
	    mycout << blanks(l) << lines.front().trim() << endline;
	 else
	 {
	    os << blanks(5) << constring << lines.front().rtrim();
	    fixedlines->push_back(rm_last_amp(os.str()));
	    os.str("");
	 }
	 lines.pop_front();
	 continue;
      }
      //
      // this line is a continuation line, without preceding '&'
      // and it has been requested that no indentation is done for 
      // continuation lines
      //
      if(to_mycout)
	 mycout << lines.front().rtrim() << endline;
      else
      {
	 os << blanks(5) << constring << lines.front().rtrim();
	 fixedlines->push_back(rm_last_amp(os.str()));
	 os.str("");
      }
      lines.pop_front();
   }
}

std::string rm_last_amp(const std::string &s)
{
   //
   // removes trailing &, also as in
   // x = 10 & ! comment
   // also removes trailing space in result
   //

   std::string slt = rtrim(remove_trailing_comment(s));
   std::string so = rtrim(slt);
   if (*so.rbegin() == '&')
      return  rtrim(so.erase(so.length() -1)+s.substr(slt.length()));
   else
      return rtrim(s);
}
