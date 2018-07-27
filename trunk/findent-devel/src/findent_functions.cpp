#include <cstdio>
#include <unistd.h>

#include "findent.h"
#include "findent_functions.h"

int determine_fix_or_free()
{
   int rc;
   std::string s;
   int n = 0;
   const int nmax = 4000;
   while ( n < nmax)
   {
      n++;
      mygetline();
      s = curline.orig();
      if (end_of_file)
      {
	 //
	 // to avoid to have to type twice a dot to
	 // end input from terminal:
	 //

	 if(reading_from_tty)
	    curlinebuffer.push_back(curline);
	 break;
      }

      curlinebuffer.push_back(curline);

      rc = guess_fixedfree(s);
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

bool handle_pre(const std::string s, const int pretype, 
      const bool output, std::list<fortranline> &c)
{
   //
   // NOTE: handle_pre can pop curlines
   //
   int ifelse;
   switch(pretype)
   {
      case CPP:
      case COCO:
	 break;
      default:
	 ifelse = prea.analyze(s, pretype);
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
	       return 0;
	       break;
	 }
	 break;
   }

   int pregentype = 0;

   switch(pretype)
   {
      case CPP_IF: case CPP_ENDIF: case CPP_ELSE: case CPP_ELIF: case CPP: 
	 pregentype = CPP;
	 break;
      case COCO_IF: case COCO_ENDIF: case COCO_ELSE: case COCO_ELIF: case COCO: 
	 pregentype = COCO;
	 break;
   }

   if(output)
      mycout << trim(s) << endline;
   else
      c.push_back(trim(s));

   std::string lchar = std::string(1,lastchar(s));
   while (!curlines.empty())
   {
      if (pregentype == CPP && lchar != "\\")
	 return 1;
      // coco continuation lines must start with ??, but we ignore that

      if (pregentype == COCO && lchar != "&")
	 return 1;

      if(pregentype == COCO)                            // TODO 
	 if(output)
	    mycout <<curlines.front().ltrim() << endline;
	 else
	    c.push_back(trim(s));
      else
	 if(output)
	    mycout <<curlines.front().orig() << endline;
	 else
	    c.push_back(trim(s));

      lchar = curlines.front().lastchar();
      curlines.pop_front();
   }
   return 1;
}       // end of handle_pre

void handle_pre_light(fortranline &fs, int &p, bool &more)
{
   //
   // handles preprocessor lines and their continuations:
   //
   // fs (input):     line to handle
   // p  (inout):     input:  type of line: CPP or COCO. 
   //                 output: if no continuation is expected, p = 0
   // more (output):  true if a continuation is expected
   //
   if(p == CPP)
      more = (fs.lastchar() == "\\");
   else
      //
      // since COCO lines always start with '??', there is no need
      // to signify that another COCO line is expected
      //
      more = 0;

   if(more == 0)
      p = 0;
}         // end of handle_pre_light

int guess_indent(const std::string s)
{
   //
   // count spaces at start of line, correct for tabs and & and label
   //
   int si         = 0;
   bool ready     = 0;
   const int tabl = 8;

   if (input_format == FIXED)
   {
      std::string s1 = ltab2sp(s);
      si             = s1.find_first_not_of(' ') -6;
      if (si <0)
	 si = 0;
      return si;
   }

   for (unsigned int j=0; j<s.length(); j++)
   {
      switch (s[j])
      {
	 case ' ' : case '0' : case '1' : case '2' : case '3' : case '4' : case '5' : case '6' : case '7' : case '8' : case '9' :
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
      indent.pop();
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

void mygetline()
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
   end_of_file = (std::cin.eof() && s == "");

   lines_read ++;

   if (!end_of_file && reading_from_tty)
      end_of_file = (s == ".");

   s = handle_dos(s);
   curline.set_line(s);
}              // end of mygetline

int pop_indent()
{
   if (indent.empty())
      return 0;
   indent.pop();
   return top_indent();
}         // end of pop_indent

int top_indent()
{
   if (indent.empty())
      return 0;
   return indent.top();
}         // end of top_indent

void push_indent(int p)
{
   indent.push(p);
}        // end of push_indent

void push_rprops(struct propstruct p)
{
   rprops.push(p);
}        // end of push_rprops

struct propstruct pop_rprops()
{
   if (rprops.empty())
      return empty_rprop;
   rprops.pop();
   return top_rprops();
}       // end of pop_rprops

struct propstruct top_rprops()
{
   if (rprops.empty())
      return empty_rprop;
   return rprops.top();
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
   dolabels.pop();
   return top_dolabel();
}        // end of pop_dolabel

int top_dolabel()
{
   if (dolabels.empty())
      return -1;
   return dolabels.top();
}        // end of top_dolabel

void push_dolabel(int p)
{
   dolabels.push(p);
}       // end of push_dolabel

void empty_dolabels()
{
   while(!dolabels.empty())
      dolabels.pop();
}       // end of empty_dolabels

int guess_fixedfree(const std::string s)
{
   //
   // sometimes, program sources contain carriage control characters
   // such as ^L
   // I cannot get the lexer to respond to [:cntrl:]
   // so I handle that here:
   //
   if (firstchar(s) != '\t')
      if(firstchar(s) < 32)
	 return UNSURE;

   lexer_set(ltab2sp(s),FINDFORMAT);
   int rc = yylex();
   return rc;
}           // end of guess_fixedfree

void push_all()
{
   indent_stack.push(indent);
   nbseen_stack.push(nbseen);
   rprops_stack.push(rprops);
   dolabels_stack.push(dolabels);
   needcon_stack.push(needcon);
}         // end of push_all

void top_all()
{
   if (!indent_stack.empty())
      indent = indent_stack.top();
   if (!nbseen_stack.empty())
      nbseen = nbseen_stack.top();
   if (!rprops_stack.empty())
      rprops = rprops_stack.top();
   if (!dolabels_stack.empty())
      dolabels = dolabels_stack.top();
   if (!needcon_stack.empty())
      needcon = needcon_stack.top();
}         // end of top_all

void pop_all()
{
   if (!indent_stack.empty())
      indent_stack.pop();
   if (!nbseen_stack.empty())
      nbseen_stack.pop();
   if (!rprops_stack.empty())
      rprops_stack.pop();
   if (!dolabels_stack.empty())
      dolabels_stack.pop();
   if (!needcon_stack.empty())
      needcon_stack.pop();
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

std::string handle_dos(const std::string s)
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
