#include "findentclass.h"
#include <cstdio>
#include <unistd.h>

void Findent::init(Flags &f)
{
   cur_indent       = 0;
   endline          = "\n";
   endline_set      = 0;
   input_format     = UNKNOWN;
   lines_read       = 0;
   nbseen           = 0;
   output_format    = 0;
   reading_from_tty = 0;
   start_indent     = 0;
   num_lines        = 0;
   labellength      = 0;
   end_of_file      = 0;
   cur_rprop        = empty_rprop;

   flags        = f;

   fortranline::line_length(flags.input_line_length);
   fortranline::gnu_format(flags.input_format_gnu);

   input_format = flags.input_format;
}

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

void Findent::push_indent(int p)
{
   indent.push_back(p);
}        // end of push_indent

int Findent::guess_indent(fortranline line)
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

int Findent::determine_fix_or_free()
{
   int rc;
   int n = 0;
   const int nmax = 4000;
   fortranline line;
   std::string s;
   bool eof;
   bool p_more = 0;
   bool skip = 0;
   while ( n < nmax)
   {
      n++;
      line = mygetline(eof);
      if (eof)
      {
	 //
	 // to avoid to have to type twice a dot to
	 // end input from terminal:
	 //

	 if(reading_from_tty)
	    curlinebuffer.push_back(line);
	 break;
      }

      curlinebuffer.push_back(line);
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

fortranline Findent::mygetline(bool &eof)
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
      eof = (s == ".");

   s = handle_dos(s);
   return fortranline(s);
}              // end of mygetline

void Findent::handle_pre_light(fortranline &line, bool &p_more)
{
   //
   // handles preprocessor lines and their continuations:
   //
   // line (input):   line to handle
   // p    (inout):   input:  type of line: CPP or COCO. 
   //                 output: if no continuation is expected, p = 0
   // p_more (output):  true if a continuation is expected
   //
   static int pregentype;

   if (!p_more)   // this is the first line of a preprocessor sequence
      pregentype = line.getpregentype();

   if(pregentype == COCO)
      p_more = (line.lastchar() == '&');
   else
      p_more = (line.lastchar() == '\\');

}         // end of handle_pre_light

int Findent::guess_fixedfree(fortranline &line)
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

#if 0
void Findent::handle_last_usable_only()
{
   //
   // search for the last line that is usable to start indenting
   // using findent.
   //
   int usable_line = 1;
   std::deque<int> usables;     // to store usable lines
   std::deque<int> prevs;       // to store prev-usable lines
   pre_analyzer preb;

   init_indent();
   while(1)
   {
      int prev         = num_lines;
      bool usable      = 0;
      get_full_statement();
      line_prep p(full_statement);
      propstruct props = parseline(p);
      switch (props.kind)
      {
	 case BLANK:
	 case CASE:
	 case CONTAINS:
	 case ENTRY:
	 case ELSE:
	 case ELSEIF:
	 case ELSEWHERE:
	    break;
	 default: 
	    usable = 1;
	    break;
      }
      if (usable)
	 usable_line = prev+1;
      if (end_of_file)
      {
	 std::cout << usable_line << endline;
	 return;
      }
   }
}             // end of last_usable_only
#endif
