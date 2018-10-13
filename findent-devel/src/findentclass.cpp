#include <stdio.h>
#include <unistd.h>
#include "findentclass.h"
#include "fortranline.h"
#include "debug.h"

int Findent::determine_fix_or_free()
{
   int rc;
   int n = 0;
   const int nmax = 4000;
   Fortranline line(gl);
   std::string s;
   bool eof;
   bool p_more = 0;
   bool skip = 0;

   while ( n < nmax)
   {
      n++;
      line = mygetline(eof,1);
      if (eof)
      {
	 //
	 // to avoid to have to type twice a dot to
	 // end input from terminal:
	 //

	 break;
      }

      handle_pre_light(line,p_more);
      if(p_more)
      {
	 skip = 1;
	 continue;
      }
      if(skip)
      {
	 skip = 0;
	 continue;
      }

      rc = guess_fixedfree(line);
      switch(rc)
      {
	 case UNSURE : 
	    break;
	 case PROBFREE : 
	    break;
	 case FREE : 
	    return FREE;
	 case FIXED : 
	    return FIXED;
      }
   }
   return FIXED;
}          // end of determine_fix_or_free


void Findent::handle_pre_light(Fortranline &line, bool &p_more)
{
   //
   // handles preprocessor lines and their continuations:
   //
   // line (input):   line to handle
   // p    (inout):   input:  type of line: CPP or COCO. 
   //                 output: if no continuation is expected, p = 0
   // p_more (output):  true if a continuation is expected
   //

   if (!p_more)   // this is the first line of a preprocessor sequence
      pregentype = line.getpregentype();

   if(pregentype == COCO)
      p_more = (line.lastchar() == '&');
   else
      p_more = (line.lastchar() == '\\');

}         // end of handle_pre_light

int Findent::guess_fixedfree(Fortranline &line)
{
   //
   // sometimes, program sources contain carriage control characters
   // such as ^L
   // I cannot get the lexer to respond to [:cntrl:]
   // so I handle that here:
   //
   std::string s = line.str();

   if (firstchar(s) != '\t')
      if(firstchar(s) < 32)
	 return UNSURE;

   lexer_set(ltab2sp(s),FINDFORMAT);
   int rc = yylex();
   return rc;
}           // end of guess_fixedfree


void Findent::handle_reading_from_tty()
{
   reading_from_tty = isatty(fileno(stdin));
   if (reading_from_tty)
   {
      std::cerr << "! Warning: reading from terminal"                << std::endl;
      std::cerr << "! End this session by typing a single dot ('.')" << std::endl;
      std::cerr << "!     on a new line"                             << std::endl;
      std::cerr << "! "                                              << std::endl;
      std::cerr << "! Examples of typical usage:"                    << std::endl;
      std::cerr << "!   help:    findent -h"                         << std::endl;
      std::cerr << "!   indent:  findent < in.f > out.f"             << std::endl;
      std::cerr << "!   convert: findent -ofree < prog.f > prog.f90" << std::endl;
   }
}                // end of handle_reading_from_tty

int Findent::what_to_return()
{
   if (flags.return_format)
      switch(input_format)
      {
	 case FREE:
	    return 2;
	    break;
	 case FIXED:
	    return 4;
	    break;
      }
   return 0;
}              // end of what_to_return

void Findent::init_indent()
{
   //
   // fills the indent-stack until indent 0
   // if flags.all_indent <= 0: build indent_stack with a number of start_indent's
   //
   while(!indent.empty())
      indent.pop_back();
   int l=0;
   if(flags.all_indent > 0)
   {
      for (l = start_indent%flags.all_indent; l<start_indent; l+=flags.all_indent)
      {
	 push_indent(l);
      }
   }
   else
   {
      for (int i=0; i<100; i++)
	 push_indent(start_indent);
   }
   push_indent(start_indent);

}             // end of init_indent


std::string Findent::handle_dos(const std::string &s)
{
   //
   // determine if the input is dos format:
   // side effect: sets endline if not already been set
   //
   std::string sl;
   sl = s;
   if (!endline_set)
   {
      if (sl != "" && lastchar(sl) == '\r')
      {
	 endline = "\r\n";
      }
      endline_set = 1;
   }
   if (sl != "" && lastchar(sl) =='\r')
      sl.erase(sl.length()-1);
   return sl;
}         // end of handle_dos

int Findent::guess_indent(Fortranline line)
{
   //
   // count spaces at start of line, correct for tabs and & and label
   //
   int si         = 0;
   bool ready     = 0;
   const int tabl = 8;

   if (line.format() == FIXED)
   {
      std::string s = line.str();
      si             = s.find_first_not_of(' ') -6;
      if (si <0)
	 si = 0;
      return si;
   }

   std::string s = line.str();
   for (unsigned int j=0; j<s.length(); j++)
   {
      switch (s[j])
      {
	 case ' ' : case '0' : case '1' : case '2' : case '3' : case '4' : 
	 case '5' : case '6' : case '7' : case '8' : case '9' :
	    si ++;
	    break;
	 case '&' :
	    si++;
	    ready = 1;
	    break;
	 case '\t' :
	    si = (si/tabl)*tabl + tabl;
	    break;
	 default:
	    ready = 1;
	    break;
      }
      if(ready)
	 break;
   }
   return si;
}                // end of guess_indent

Fortranline Findent::getnext(bool &eof, bool use_wb)
{
   Fortranline line(gl);
   eof = 0;
   if (use_wb && !wizardbuffer.empty())
   {
      line = wizardbuffer.front();
      wizardbuffer.pop_front();
      if (reading_from_tty && line.str() == ".")
	 eof = 1;
   }
   else if (!curlinebuffer.empty())
   {
      line = curlinebuffer.front();
      curlinebuffer.pop_front();
      num_lines++;
      if (reading_from_tty && line.str() == ".")
	 eof = 1;
   }
   else
   {
      line = mygetline(eof);
      if (!eof)
	 num_lines++;
   }

   //
   // remove trailing white space
   // FIXED: convert leading tab to space
   //

   line.clean();

   if(!use_wb && !eof)
      wizardbuffer.push_back(line);

   if (!nbseen)
   {
      nbseen = !line.blank_or_comment() 
	 && (line.getpregentype() == 0)
	 && prevlastchar          != '\\'
	 && line.lastchar()       != '\\'; 

      if (flags.auto_firstindent && nbseen)
      {
	 start_indent = guess_indent(line);
	 cur_indent   = start_indent;
	 init_indent();
	 indent_handled = 1;
      }
      prevlastchar = line.lastchar();
   }

   return line;
}

Fortranline Findent::mygetline(bool &eof, bool buffer)
{
   //
   // reads next line from cin.
   // side effects:
   //   end_of_file is set if endoffile condition is met
   //   endline is set to \n or \r\n
   //   lines_read is incremented
   //

   std::string s;

   getline(std::cin,s);

   //
   // sometimes, files do not end with (cr)lf, hence the test for s=="":
   //
   eof = (std::cin.eof() && s == "");

   lines_read ++;

   if (!eof && reading_from_tty)
   {
      eof = (s == ".");
      if (eof)
	 curlinebuffer.push_back(Fortranline(gl,s));
   }

   s = handle_dos(s);

   if(buffer && !eof)
      curlinebuffer.push_back(Fortranline(gl,s));

   return Fortranline(gl,s);
}              // end of mygetline

void Findent::output_deps()
{
   std::cout << "f_include:" ;
   while (! f_includes.empty())
   {
      std::cout << " "+f_includes.top();
      f_includes.pop();
   }
   std::cout << endline;
}
