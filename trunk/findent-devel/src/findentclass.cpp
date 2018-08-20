#include "findentclass.h"
#include <cstdio>
#include <unistd.h>


int Findent::determine_fix_or_free()
{
   int rc;
   int n = 0;
   const int nmax = 4000;
   Fortranline line;
   std::string s;
   bool eof;
   bool p_more = 0;
   bool skip = 0;
   while ( n < nmax)
   {
      n++;
      line = rl->mygetline(eof,1);
      if (eof)
      {
	 //
	 // to avoid to have to type twice a dot to
	 // end input from terminal:
	 //

//	 if(reading_from_tty)
//	    rl->curlinebuffer.push_back(line);
	 break;
      }

      //rl->curlinebuffer.push_back(line);
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
   static int pregentype;

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

