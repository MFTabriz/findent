#include <algorithm>
#include <string>
#include <sstream>

#include "debug.h"
#include "findent_types.h"
#include "fixed.h"
#include "free.h"
#include "simpleostream.h"

void Free::build_statement(Fortranline &line, bool &f_more, bool &pushback)
{
   //
   // adds line to curlines
   // adds line (stripped from comments, preprocessor stuff and 
   //    continuation stuff)  to full_statement
   // f_more 1: more lines are to expected
   //        0: this line is complete
   //

   pushback = 0;

   if (!line.blank_or_comment())
   {
      //
      // sl becomes the first input_line_length characters of line
      // and then trimmed left and right:
      //

      std::string sl = line.trimmed_line();

      if(line.firstchar() == '&')
      {
	 sl.erase(0,1);
	 sl = ltrim(sl);
      }

      full_statement = full_statement + sl;

      //
      // remove trailing comment and trailing white space
      //

      full_statement = rtrim(remove_trailing_comment(full_statement));

      // 
      // If the last character = '&', a continuation is expected.
      //

      f_more = ( lastchar(full_statement) == '&');
      if (f_more)            // chop off '&' from full_statement :
	 full_statement.erase(full_statement.length()-1);

   }
   curlines.push_back(line);
}           // end of build_statement


void Free::output(lines_t &lines, lines_t *fixedlines)
{
   //
   // output lines input: free format, output: free format
   //

   std::string endline = fi->endline;
   bool to_mycout = (fixedlines == 0);
   std::ostringstream os;
   bool isfirst = 1;
   const char conchar = '&';

   while (!lines.empty())
   {
      mycout.reset();

      is_omp = lines.front().omp();

      if(is_omp)
      {
	 ompstr = "!$ ";     // omp sentinel for free format
	 cmpstr = "!$";      // omp sentinel for fixed format
      }
      else
      {
	 ompstr = "";
	 cmpstr = "";
      }

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
	    mycout << ompstr << endline;
	 else
	 {
	    if (lines.front().omp())
	       fixedlines->push_back(F(cmpstr));
	    else
	       fixedlines->push_back(F(""));
	    os.str("");
	 }
	 lines.pop_front();
	 continue;
      }

      //
      // handle comment lines:
      //
      if (lines.front().comment())
      {
	 if (lines.front()[0] != '!' || lines.front().omp())
	 {
	    //
	    // take care of the situation that cur_indent == 0
	    // but the comment does not start in column 1
	    //
	    if(to_mycout)
	       mycout << insert_omp(blanks(M(std::max(fi->cur_indent,1))));
	    else
	       os << cmpstr << blanks(std::max(fi->cur_indent,1));
	 }

	 if(to_mycout)
	 {
	    mycout << lines.front().trim() << endline;
	 }
	 else
	 {
	    os << lines.front().trim();
	    fixedlines->push_back(F(rtrim(os.str())));
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
	 if (fi->flags.label_left && fi->labellength > 0)
	 {
	    //
	    // put label at start of line
	    //
	    std::string firstline = lines.front().trim();
	    std::string label     = firstline.substr(0,fi->labellength);
	    firstline             = trim(firstline.substr(fi->labellength));

	    int l = M(std::max(fi->cur_indent - fi->labellength,1));  // put at least one space after label
	    if(to_mycout)
	    {
	       if (lines.front().omp())
		  l = M(std::max((int)(l-ompstr.length()),1));
	       mycout << ompstr << label << blanks(l) << firstline << endline;
	    }
	    else
	    {
	       os << cmpstr << label << blanks(6) << rm_last_amp(firstline);
	       fixedlines->push_back(F(os.str()));
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
	 {
	    mycout << insert_omp(blanks(M(std::max(fi->cur_indent,0)))) <<
	       lines.front().trim() << endline;
	 }
	 else
	 {
	    os << insert_cmp(blanks(5));
	    if(lines.front().firstchar() == '&')
	       os << conchar << rm_last_amp(ltrim(lines.front().trim().substr(1)));
	    else
	       os << ' ' << rm_last_amp(lines.front().rtrim());
	    fixedlines->push_back(F(os.str()));
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

      if (lines.front().firstchar() == '&')  // continuation line starting with '&'
      {
	 if(to_mycout)
	    mycout << insert_omp(blanks(M(std::max(fi->cur_indent,0)))) <<
	       lines.front().trim() << endline;
	 else
	 {
	    os << insert_cmp(blanks(5)) << conchar << rm_last_amp(lines.front().trim().substr(1));
	    fixedlines->push_back(F(os.str()));
	    os.str("");
	 }
	 lines.pop_front();
	 continue;
      }

      //
      // continutation not starting with '&'
      //
      if (fi->flags.indent_cont)    // indentation of continuation lines is requested
      {
	 int l = M(std::max(fi->cur_indent+fi->flags.cont_indent,0));
	 if(to_mycout)
	    mycout << insert_omp(blanks(l)) << lines.front().trim() << endline;
	 else
	 {
	    if (lines.front().omp())
	       os << "!$" << blanks(3);
	    else
	       os << blanks(5);
	    os << conchar << rm_last_amp(lines.front().rtrim());
	    fixedlines->push_back(F(os.str()));
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
	 mycout << insert_omp(lines.front().rtrim()) << endline;
      else
      {
	 if (lines.front().omp())
	    os << "!$" << blanks(3);
	 else
	    os << blanks(5);
	 os << conchar << rm_last_amp(lines.front().rtrim());
	 fixedlines->push_back(F(os.str()));
	 os.str("");
      }
      lines.pop_front();
   }
}      // end of output

void Free::output_converted(lines_t &lines)
{
   lines_t fixedlines;

   output(lines, &fixedlines);

   Globals oldgl = *gl;
   gl->global_format      = FIXED;
   gl->global_line_length = 0;

   Fixed f(fi);
   
   lines_t::iterator it = fixedlines.begin();
   //
   // clean all fixedlines:
   //
   while(it != fixedlines.end()) 
   {
      it->clean(1);
      it++;
   }
   f.output(fixedlines);
   (*gl) = oldgl;

}   // end of output_converted

std::string Free::rm_last_amp(const std::string &s)
{
   //
   // removes trailing &, also as in
   // x = 10 & ! comment
   // also removes trailing space in result
   //

   std::string slt = rtrim(remove_trailing_comment(s));
   std::string so = rtrim(slt);
   ppp<<FL<<so<<endchar;
   if (*so.rbegin() == '&')
      return  rtrim(so.erase(so.length() -1)+s.substr(slt.length()));
   else
      return rtrim(s);
}   // end of rm_last_amp
