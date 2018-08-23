#include <algorithm>
#include <cstdio>
#include <unistd.h>

#include "findent.h"
#include "findent_functions.h"
#include "debug.h"

int determine_fix_or_free()
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

//
// #if, #ifdef, #ifndef, #else, #elif and #endif

// after an #if{,def,ndef} the indent stack is pushed
// on indent_stack, and the current indent stack is used.
// after an #elif the indent stack is made equal to indent_stack.top()
// after an #else, the indent stack is popped from indent_stack.
// after an #endif:
//     if the index stack was not already popped from index_stack (after
//        #else), it is popped
// the stack pre_stack is used to note if the index stack was already
//      popped by #else
//
// So, after #endif, the indentation is taken from the code after #else
//     or, if there is no #else, from the code before the #if{,def,ndef}
//

void handle_pre(fortranline &line, const bool f_more, bool &p_more)
{
   int ifelse;
   static int pretype;
   static int pregentype;

   pregentype = line.getpregentype();
   if(pregentype == CPP || pregentype == COCO)
   {
      pretype    = line.scanfixpre();
      switch(pretype)
      {
	 case CPP:
	 case COCO:
	 case FINDENTFIX:
	    break;
	 default:
	    ifelse = prea.analyze(line.trimmed_line(), pretype);
	    switch(ifelse)
	    {
	       case pre_analyzer::IF:
		  push_all();
		  break;

	       case pre_analyzer::ELIF:
		  top_all();
		  break;

	       case pre_analyzer::ELSE:
		  top_all();
	       case pre_analyzer::ENDIF:
		  pop_all();
		  break;

	       case pre_analyzer::ENDIFE:
		  break;

	       default:
		  return;
		  break;
	    }

	    switch(ifelse) // full_statement needs apart treatment:
	    {
	       case pre_analyzer::IF:
		  fs_store.push_back(full_statement);
		  break;

	       case pre_analyzer::ELIF:
		  if(fs_store.empty())
		     full_statement = "";
		  else
		     full_statement = fs_store.back();
		  break;

	       case pre_analyzer::ELSE:
		  if(fs_store.empty())
		     full_statement = "";
		  else
		     full_statement = fs_store.back();
		  break;

	       case pre_analyzer::ENDIF:
	       case pre_analyzer::ENDIFE:
		  if(!fs_store.empty())
		     fs_store.pop_back();
		  break;

		  break;
	    }
	    break;
      }
   }
   if(pregentype == CPP)
      p_more = (line.lastchar() == '\\');
   else if(pregentype == COCO)
      p_more = (line.lastchar() == '&');
   else
      p_more = 0;

}       // end of handle_pre


void handle_pre_light(fortranline &line, bool &p_more)
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

int guess_indent(fortranline line)
{
   //
   // count spaces at start of line, correct for tabs and & and label
   //
   int si         = 0;
   bool ready     = 0;
   const int tabl = 8;

   if (input_format == FIXED)
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

void handle_reading_from_tty()
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

void init_indent()
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

fortranline mygetline(bool &eof)
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

int pop_indent()
{
   if (indent.empty())
      return 0;
   indent.pop_back();
   return top_indent();
}         // end of pop_indent

int top_indent()
{
   if (indent.empty())
      return 0;
   return indent.back();
}         // end of top_indent

void push_indent(int p)
{
   indent.push_back(p);
}        // end of push_indent

void push_rprops(struct propstruct p)
{
   rprops.push_back(p);
}        // end of push_rprops

struct propstruct pop_rprops()
{
   if (rprops.empty())
      return empty_rprop;
   rprops.pop_back();
   return top_rprops();
}       // end of pop_rprops

struct propstruct top_rprops()
{
   if (rprops.empty())
      return empty_rprop;
   return rprops.back();
}       // end of top_rprops

std::string whatrprop(struct propstruct p)
{
   switch(p.kind)
   { 
      case SUBROUTINE:
      case MODULESUBROUTINE: return("subroutine");
      case PROGRAM:          return("program");
      case BLOCKDATA:        return("block data");
      case FUNCTION:
      case MODULEFUNCTION:   return("function");
      case MODULE:           return("module");
      case SUBMODULE:        return("submodule");
      case PROCEDURE:        return("procedure");
      default:               return("");
   }
}         // end of whatrprop

int pop_dolabel()
{
   if (dolabels.empty())
      return -1;
   dolabels.pop_back();
   return top_dolabel();
}        // end of pop_dolabel

int top_dolabel()
{
   if (dolabels.empty())
      return -1;
   return dolabels.back();
}        // end of top_dolabel

void push_dolabel(int p)
{
   dolabels.push_back(p);
}       // end of push_dolabel

void empty_dolabels()
{
   while(!dolabels.empty())
      dolabels.pop_back();
}       // end of empty_dolabels

int guess_fixedfree(fortranline &line)
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

void push_all()
{
   dolabels_store.push_back(dolabels);
   indent_store.push_back(indent);
   nbseen_store.push_back(nbseen);
   rprops_store.push_back(rprops);

}         // end of push_all

void top_all()
{
   if (!dolabels_store.empty())
      dolabels = dolabels_store.back();
   if (!indent_store.empty())
      indent = indent_store.back();
   if (!nbseen_store.empty())
      nbseen = nbseen_store.back();
   if (!rprops_store.empty())
      rprops = rprops_store.back();
}         // end of top_all

void pop_all()
{
   if (!dolabels_store.empty())
      dolabels_store.pop_back();
   if (!indent_store.empty())
      indent_store.pop_back();
   if (!nbseen_store.empty())
      nbseen_store.pop_back();
   if (!rprops_store.empty())
      rprops_store.pop_back();

}        // end of pop_all

int what_to_return()
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

std::string handle_dos(const std::string &s)
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

bool output_pre(lines_t &lines, lines_t *outlines)
{
   //
   // if the first line of lines is a preprocessor line
   // output this line and the continuation lines
   // popping lines
   //

   bool to_mycout = outlines == 0;

   if(lines.empty())
      return 0;
   if (lines.front().pre())
   {
      bool p_more = 0;
      while(1)
      {
	 handle_pre_light(lines.front(),p_more);
	 if (lines.front().pre())
	    if (to_mycout)
	       mycout << lines.front().trim() << endline;
	    else
	       outlines->push_back(lines.front().trim());
	 else
	    if (to_mycout)
	       mycout << lines.front().str() << endline;
	    else
	       outlines->push_back(lines.front().str());
	 lines.pop_front();
	 if (lines.empty() || !p_more)
	    break;
      }
      return 1;
   }
   else
      return 0;
}     // end of output_pre