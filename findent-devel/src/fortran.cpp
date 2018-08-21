#include "fortran.h"
#include "npre_analyzer.h"
#include "nline_prep.h"

bool Fortran::output_pre(lines_t &lines, lines_t *outlines)
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
	       mycout << lines.front().trim() << fi->get_endline();
	    else
	       outlines->push_back(lines.front().trim());
	 else
	    if (to_mycout)
	       mycout << lines.front().str() << fi->get_endline();
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

void Fortran::handle_pre_light(Fortranline &line, bool &p_more)
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


void Fortran::handle_last_usable_only()
{
   //
   // search for the last line that is usable to start indenting
   // using findent.
   //
   int usable_line = 1;
   std::deque<int> usables;     // to store usable lines
   std::deque<int> prevs;       // to store prev-usable lines
   pre_analyzer preb;

   fi->init_indent();
   while(1)
   {
      int prev         = fi->get_num_lines();
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
      if (fi->get_end_of_file())
      {
	 std::cout << usable_line << fi->get_endline();
	 return;
      }
   }
}             // end of last_usable_only

void Fortran::get_full_statement()
{
   //
   // this function collects 'full_statement': a complete
   // fortran line, concatenated from possible continuation lines,
   // comments and preprocessor lines removed
   //
   // full_statement is used to determine the indentation
   //
   // Also, every line is stored in 'lines'
   // 
   // If the input starts with a comment or a preprocessor line,
   // full_statement = "", lines will contain the line, possibly
   // followed by preprocessor continuation lines as in:
   /* #define foo \   */
   //           bar
   //
   // A totally empty line is treated as a comment line,
   //
   // Comment lines and preprocessor lines can be embedded in 
   // fortran continuation lines as in:
   //
   //    subroutine compute( &
   // #ifdef one
   //      x &
   // #else
   //      x,y &
   // #endif
   //     )
   //
   // In this example, full_statement will contain:
   //
   //    subroutine compute(x,y)
   // ( this is only correct if 'one' is not defined, but it 
   //   will not prevent correct indenting)
   //

   //
   // if things get hairy: try a finite state machine
   //
   enum {
      start=1,
      in_fortran, in_fortran_1,
      in_pre, 
      end_start, end_fortran, end_pre, 
      in_ffix
   };

   full_statement = "";
   fi->set_indent_handled(0);

   //
   // 'pushback' and 'first_call' must be static in this version,
   // for safety 'pretype' and 'f_more' and 'p_more' are also made static
   //
   static int pretype;     // 
   static bool f_more = 0;
   static bool p_more;
   static bool pushback;
   static bool first_call = 1;

   Fortranline curline;

   bool my_end;  // g++ forbids rl->getnext(end_of_file) ???
   //                  error: invalid initialization of non-const reference of type ‘bool&’ from an rvalue of type ‘bool’
   //

   if (first_call)
   {
      curline = fi->getnext(my_end);
      first_call = 0;
   }

   while(!curlines.empty())
      curlines.pop_back();

   // curlines.push_front(fortranline("_"));

   static int state = start;

   while(1)
   {
      switch(state)
      {
	 case start:
	    if (fs_store.empty())
	       full_statement = "";
	    else
	       full_statement = fs_store.back();

	    if (my_end) 
	    {
	       state = end_start;
	       break;
	    }
	    pretype = curline.getpregentype();
	    if(pretype == CPP || pretype == COCO)
	    {
	       state = in_pre;
	       break;
	    }
	    if (is_findentfix(curline))
	    {
	       state = in_ffix;
	       break;
	    }

	    state = in_fortran;
	    break;

	 case in_ffix:
	    curlines.push_back(curline);
	    full_statement = rtrim(remove_trailing_comment(curline.rest()));
	    curline = fi->getnext(my_end);
	    fi->set_end_of_file(my_end);
	    state = start;
	    return;

	 case in_fortran:
	    if(my_end) { state = end_fortran; break; }

	    build_statement(curline, f_more, pushback);
	    if (f_more)
	    {
	       curline = fi->getnext(my_end); if (my_end) { state = end_fortran; break; }
	       pretype = curline.getpregentype();
	       if (pretype == CPP || pretype == COCO)
	       {
		  p_more = 0;
		  while (1)
		  {
		     handle_pre(curline,f_more,p_more);
		     curlines.push_back(curline);
		     if(p_more)
		     {
			curline = fi->getnext(my_end); if (my_end) { state = end_fortran; break; }
		     }
		     else
			break;
		  }
		  curline = fi->getnext(my_end);
	       }
	       state = in_fortran;
	       break;
	    }
	    state = in_fortran_1;
	    //
	    // need state in_fortran_1 to get correct result from last_usable
	    //
	    fi->set_end_of_file(my_end);
	    return;

	 case in_fortran_1:
	    if (!pushback)                     // here is why pushback has to be static
	       curline = fi->getnext(my_end);
	    state = start;
	    fi->set_end_of_file(my_end);
	    break;

	 case in_pre:
	    p_more = 0;
	    while(1)
	    {
	       handle_pre(curline,f_more,p_more);
	       curlines.push_back(curline);
	       if(p_more)
	       {
		  curline = fi->getnext(my_end); if (my_end) { state = end_pre; break; }
	       }
	       else
		  break;
	    }
	    curline = fi->getnext(my_end);
	    state = start;
	    fi->set_end_of_file(my_end);
	    break;

	 case end_start:
	 case end_fortran:
	 case end_pre:
	    state = start;
	    fi->set_end_of_file(my_end);
	    return;
      }
      fi->set_end_of_file(my_end);
   }
   fi->set_end_of_file(my_end);
}           // end of get_full_statement

bool Fortran::is_findentfix(Fortranline &line)
{
   bool rc = 0;
   switch (line.scanfixpre())
   {
      case FINDENTFIX:
	 rc = 1;
	 break;
      case P_ON:
	 ppp.on();     // debug.h, debug.cpp
	 break;
      case P_OFF:
	 ppp.off();
	 break;
   }
   return rc;
}

void Fortran::handle_pre(Fortranline &line, const bool f_more, bool &p_more)
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
