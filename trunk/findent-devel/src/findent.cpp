// $Id$
#include <iostream>
#include <string>
#include <stack>

#include "debug.h"
#include "emacs_plugin.h"
#include "findent.h"
#include "findent_functions.h"
#include "fixed2fixed.h"
#include "fixed2free.h"
#include "free2free.h"
#include "free2fixed.h"
#include "functions.h"
#include "gedit_plugin.h"
#include "lexer.h"
#include "line_prep.h"
#include "parser.h"
#include "readme_plugin.h"
#include "usage.h"
#include "version.h"
#include "vim_plugin.h"


int               cur_indent;
struct propstruct cur_rprop           = empty_rprop;
fortranline       curline;
bool              end_of_file;
std::string       endline             = "\n";
bool              endline_set         = 0;
Flags             flags;
std::string       full_statement;             // current statement, including continuation lines, &'s removed
bool              indent_handled;
int               input_format;
int               labellength;
int               lines_read          = 0;
simpleostream     mycout;
bool              nbseen;                    // true if non-blank-line is seen 
bool              iscon               = 0;   // true if current line is a continuation
int               num_lines;                 // number of lines read sofar
int               output_format;
pre_analyzer      prea;
struct propstruct prev_props;
bool              reading_from_tty    = 0;
bool              refactor_end_found;
int               start_indent;
int               stlabel;

iscon_t          iscon_stack;     // to store iscon
dolabels_t       dolabels;        // to store labels, necessary for labelled do
dolabels_stack_t dolabels_stack;  // to store dolabels stack
indent_t         indent;          // to store indents
indent_stack_t   indent_stack;    // to store indent stack
fs_stack_t       fs_stack;        // to store full_statement
linebuffer_t     curlinebuffer;   // deque for source lines
lines_t          curlines;        // current line, one continuation line per item
nbseen_stack_t   nbseen_stack;    // to store nbseen
rprops_t         rprops;          // to store routines (module, subroutine ...)
rprops_stack_t   rprops_stack;

int main(int argc, char*argv[])
{
   fortranline::setformat(UNKNOWN);
   int todo = flags.get_flags(argc,argv);
   switch(todo)
   {
      case Flags::DO_VERSION:
	 std::cout << "findent version "<<VERSION<<std::endl;  // --version
	 return 0;
      case Flags::DO_USAGE:
	 usage(0);
	 return 0;
      case Flags::DO_MANPAGE:
	 usage(1);
	 return 0;
      case Flags::DO_VIM_HELP:
	 do_vim_help();
	 return 0;
      case Flags::DO_VIM_FINDENT:
	 do_vim_findent();
	 return 0;
      case Flags::DO_VIM_FORTRAN:
	 do_vim_fortran();
	 return 0;
      case Flags::DO_GEDIT_HELP:
	 do_gedit_help();
	 return 0;
      case Flags::DO_GEDIT_EXTERNAL:
	 do_gedit_external();
	 return 0;
      case Flags::DO_GEDIT_PLUGIN:
	 do_gedit_plugin();
	 return 0;
      case Flags::DO_GEDIT_PLUGIN_PY:
	 do_gedit_plugin_py();
	 return 0;
      case Flags::DO_EMACS_HELP:
	 do_emacs_help();
	 return 0;
      case Flags::DO_EMACS_FINDENT:
	 do_emacs_findent();
	 return 0;
      case Flags::DO_README:
	 do_readme();
	 return 0;
   }

   fortranline::setline_length(flags.input_line_length);
   fortranline::setgnu_format(flags.input_format_gnu);
   start_indent = flags.start_indent;
   handle_reading_from_tty();

   input_format = flags.input_format;
   if (input_format == UNKNOWN)
      input_format = determine_fix_or_free();

   fortranline::setformat(input_format);

   if (flags.only_fix_free)
   {
      switch(input_format)
      {
	 case FIXED : mycout << "fixed" << endline;
		      break;
	 case FREE :  mycout << "free" << endline;
		      break;
      }
      return what_to_return();
   }

   output_format = flags.output_format;
   if(output_format == 0)
      output_format = input_format;

   labellength      = 0;
   end_of_file      = 0;
   cur_rprop        = empty_rprop;
   init_indent();
   if (flags.last_usable_only)
   {
      handle_last_usable_only();
      return what_to_return();
   }

   cur_indent = start_indent;
   while(1)
   {
      get_full_statement();
      //indent_and_output();
      if (end_of_file)
      {
	 if(flags.last_indent_only)
	    std::cout << num_leading_spaces(mycout.get()) << endline;
	 return what_to_return();
      }
   }
   return what_to_return();
}        // end of main

//
// search for the last line that is usable to start indenting
// using findent.
//
void handle_last_usable_only()
{
   int usable_line = 1;
   std::stack<int> usables;     // to store usable lines
   std::stack<int> prevs;       // to store prev-usable lines
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
      while (!curlines.empty())
      {
	 int pretype = curlines.front().scanfixpre();
	 int ifelse  = preb.analyze(curlines.front().trim(),pretype);
	 switch(ifelse)
	 {
	    case pre_analyzer::IF:
	       usables.push(usable_line);
	       prevs.push(prev);
	       break;

	    case pre_analyzer::ELIF:
	       if(!usables.empty())
	       {
		  usable_line = usables.top();
		  prev        = prevs.top();
	       }
	       break;

	    case pre_analyzer::ELSE:
	    case pre_analyzer::ENDIF:
	       if (!usables.empty())
	       {
		  usable_line = usables.top();
		  usables.pop();
		  prev        = prevs.top();
		  prevs.pop();
	       }
	       break;

	    case pre_analyzer::ENDIFE:
	       break;

	    case pre_analyzer::NONE:
	       break;
	 }
	 curlines.pop_front();
      }
      if (end_of_file)
      {
	 std::cout << usable_line << endline;
	 return;
      }
   }
}             // end of last_usable_only


void indent_and_output()
{
   std::string rest = full_statement;
   bool first_time  = 1;
   indent_handled   = 0;
   while(1)
   {
      line_prep p(rest);
      propstruct props = parseline(p); 
      labellength = props.label.size();
      if (labellength > 0)
	 //
	 // if there was a previous labeled do, handle it:
	 //
      {
	 int ilabel = string2number<int>(props.label);
	 while ( top_dolabel() == ilabel )
	 {
	    pop_indent();
	    pop_dolabel();
	    cur_indent = top_indent();
	    indent_handled = 1;
	 }
      }
      //
      // if the previous non-blank line was PROCEDURE (module procedure)
      // then determine if this was a procedure with content
      // if so: take delayed action with respect to indenting
      //
      if (prev_props.kind == PROCEDURE)
      {
	 switch (props.kind)
	 {
	    case ASSIGNMENT:
	    case UNCLASSIFIED:
	    case BLOCK:
	    case CONTAINS:
	    case CRITICAL:
	    case DO:
	    case END:
	    case ENDPROCEDURE:
	    case ENTRY:
	    case ENUM:
	    case FORALL:
	    case IF:
	    case SELECTCASE:
	    case SELECTTYPE:
	    case TYPE:
	    case WHERE:
	       cur_indent = top_indent();
	       push_indent(cur_indent + flags.routine_indent);
	       empty_dolabels();
	       push_rprops(prev_props);
	       break;
	    default:
	       break;
	 }
      }
      cur_indent = top_indent();
      refactor_end_found = 0;
      //
      // for every entity that is eligable for refacoring it's end
      // e.g. subroutine
      // we will push props on the rprops stack
      // for every corresponding end-entity (e.g. endsubroutine) we will
      // pop the rprops stack
      // 
      switch(props.kind)
      {
	 case SUBROUTINE:
	 case FUNCTION:
	 case PROGRAM:
	 case BLOCKDATA:
	    cur_indent = top_indent();
	    push_indent(cur_indent + flags.routine_indent);
	    empty_dolabels();
	    push_rprops(props);
	    break;
	 case MODULE:
	 case SUBMODULE:
	    cur_indent = top_indent();
	    push_indent(cur_indent + flags.module_indent);
	    empty_dolabels();
	    push_rprops(props);
	    break;
	 case BLOCK:
	    cur_indent = top_indent();
	    push_indent(cur_indent + flags.block_indent);
	    break;
	 case CRITICAL:
	    cur_indent = top_indent();
	    push_indent(cur_indent + flags.critical_indent);
	    break;
	 case ENUM:
	    cur_indent = top_indent();
	    push_indent(cur_indent + flags.enum_indent);
	    empty_dolabels();
	    break;
	 case ABSTRACTINTERFACE:
	 case INTERFACE:
	    cur_indent = top_indent();
	    push_indent(cur_indent + flags.interface_indent);
	    empty_dolabels();
	    break;
	 case DO:
	    cur_indent = top_indent();
	    push_indent(cur_indent + flags.do_indent);
	    if (props.dolabel != "")
	       push_dolabel(string2number<int>(props.dolabel));
	    break;
	 case SELECTCASE:
	 case SELECTTYPE:
	    cur_indent = top_indent();
	    push_indent(cur_indent + flags.select_indent);
	    break;
	 case CASE:
	 case CASEDEFAULT:
	 case CLASSDEFAULT:
	 case CLASSIS:
	 case TYPEIS:
	    cur_indent -= flags.case_indent;
	    break;
	 case END:
	 case ENDBLOCKDATA:
	 case ENDFUNCTION:
	 case ENDMODULE:
	 case ENDPROCEDURE:
	 case ENDPROGRAM:
	 case ENDSUBROUTINE:
	    refactor_end_found = 1;
	    if (!indent_handled)
	       cur_indent = pop_indent();
	    cur_rprop = top_rprops();
	    pop_rprops();
	    break;
	 case ENDASSOCIATE:
	 case ENDBLOCK:
	 case ENDCRITICAL:
	 case ENDDO:
	 case ENDENUM:
	 case ENDFORALL:
	 case ENDIF:
	 case ENDINTERFACE:
	 case ENDSELECT:
	 case ENDSUBMODULE:
	 case ENDTYPE:
	 case ENDWHERE:
	    if (!indent_handled)
	       cur_indent = pop_indent();
	    break;
	 case PROCEDURE:  // in fact: moduleprocedure
	    //
	    // depending on what follows this will be 
	    // recognized as a module procedure with content
	    // or only a moduleprocedure specification
	    //
	    break;
	 case CONTAINS:
	    if (flags.indent_contain)
	       cur_indent -= flags.contains_indent;
	    else
	    {
	       cur_indent = start_indent;
	       pop_indent();
	       push_indent(cur_indent);
	    }
	    break;
	 case IF:
	    cur_indent = top_indent();
	    push_indent(cur_indent + flags.if_indent);
	    break;
	 case ELSE:
	    cur_indent -= flags.if_indent;
	    break;
	 case ELSEIF:
	    cur_indent -= flags.if_indent;
	    break;
	 case ELSEWHERE:
	    cur_indent -= flags.where_indent;
	    break;
	 case ENTRY:
	    cur_indent -= flags.entry_indent;
	    break;
	 case WHERE:
	    cur_indent = top_indent();
	    push_indent(cur_indent + flags.where_indent);
	    break;
	 case ASSOCIATE:
	    cur_indent = top_indent();
	    push_indent(cur_indent + flags.associate_indent);
	    break;
	 case TYPE:
	    cur_indent = top_indent();
	    push_indent(cur_indent + flags.type_indent);
	    break;
	 case FORALL:
	    cur_indent = top_indent();
	    push_indent(cur_indent + flags.forall_indent);
	    break;
	 default:
	    cur_indent = top_indent();
      }
      switch(props.kind)
      {
	 case BLANK:
	    break;
	 default:
	    prev_props = props;
      }
      if(first_time)  // check to handle multi-statement line
      {
	 output_line();
	 first_time = 0;
      }
      rest = p.get_line_rest();
      if (rest == "")
	 break;
   }
}               // end of indent_and_output

void getnext()
{
   if (curlinebuffer.empty())
      mygetline();
   else
   {
      curline = curlinebuffer.front();
      curlinebuffer.pop_front();
      if (reading_from_tty && curline.orig() == ".")
	 end_of_file = 1;
   }

   num_lines++;

   if (!nbseen)
   {
      nbseen = !curline.blank_or_comment() && (curline.getpregentype() == 0);
      if (flags.auto_firstindent && nbseen)
      {
	 start_indent = guess_indent(curline.orig());
	 cur_indent   = start_indent;
	 init_indent();
	 indent_handled = 1;
      }
   }
}

void get_full_statement()
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
   //    subroutine compute(x x,y)
   // ( this is not correct, of course, but it will not prevent 
   //   correct indenting)
   //
   // and lines will contain:
   //    subroutine compute(x x,y)
   //
   // #ifdef one
   //      x &
   // #else
   //      x,y &
   // #endif
   //     )
   //

   full_statement       = "";
   indent_handled       = 0;
   bool preproc_more    = 0;
   bool fortran_more    = 0;
   int pretype          = 0;

   enum{unknown = 1, in_preproc, in_fortran};
   int state = unknown;

   // finite state
   void handle_fortran(fortranline &line,bool &more, bool &pushback);
   bool ispre(const std::string &line);
   std::string line;

   bool f_more = 0;
   bool p_more;
   bool pushback;
   getnext();

start:
   full_statement = "";
   if (end_of_file) 
      goto end_start;
   pretype = curline.getpregentype();
   if(pretype == CPP || pretype == COCO)
      goto in_pre;
   goto in_fortran;

in_fortran:
   handle_fortran(curline, f_more, pushback);
   if (f_more)
   {
      getnext();
      if (end_of_file)
	 goto end_fortran;
      pretype = curline.getpregentype();
      if (pretype == CPP || pretype == COCO)
      {
	 indent_and_output();
	 goto in_pre;
      }
      goto in_fortran;
   }
   indent_and_output();
   iscon = 0;                // next line is not a continuation
   if (!pushback)
      getnext();
   goto start;

in_pre:
   handle_pre_light1(curline,pretype,p_more);
   if (p_more)
   {
      getnext();
      if (end_of_file)
	 goto end_pre;
      goto in_pre;
   }
   handle_pre(curlines,f_more);
   getnext();
   goto start;

end_start:
   indent_and_output();
   return;

end_fortran:
   indent_and_output();
   return;

end_pre:
   indent_and_output();
   return;

}           // end of get_full_statement

void handle_free1(fortranline &curline, bool &more,bool &pushback);
void handle_fixed1(fortranline &curline, bool &more,bool &pushback);

void handle_fortran(fortranline &line,bool &more, bool &pushback)
{
   if (input_format == FREE)
      handle_free1(line,more,pushback);
   else
      handle_fixed1(line,more,pushback);
}

void handle_free1(fortranline & curline, bool &more,bool &pushback)
{
   //
   // adds curline to curlines
   // adds curline (stripped from comments, preprocessor stuff and 
   //    continuation stuff)  to full_statement
   // more 1: more lines are to expected
   //      0: this line is complete
   //

   pushback = 0;
   //
   // handle findentfix: 
   //

   if (curlines.empty())
   {
      switch (curline.scanfixpre())
      {
	 case FINDENTFIX:
	    full_statement = curline.rest();
	    break;
	 case PPP_ON:
	    ppp_on = 1;     // debug.h, debug.cpp
	    break;
	 case PPP_OFF:
	    ppp_on = 0;
	    break;
      }
   }

   if (!curline.blank_or_comment())
   {
      //
      // sl becomes the first input_line_length characters of curline
      // and then trimmed left and right:
      //

      std::string sl = curline.trimmed_line();

      if(curline.firstchar() == "&")
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

      more = ( lastchar(full_statement) == '&');
      if (more)            // chop off '&' from full_statement :
	 full_statement.erase(full_statement.length()-1);

   }
   curlines.push_back(curline);
}           // end of handle_free1


void handle_fixed1(fortranline &curline, bool &more,bool &pushback)
{
   //
   // adds curline to curlines
   // adds curline (stripped from comments, preprocessor stuff and 
   //    continuation stuff)  to full_statement
   // more 1: more lines are to expected
   //      0: this line is complete
   //

   //
   // if this is a findentfix line:
   //    Assume that no continuation lines can follow.
   //    So, if there are already one or more lines read,
   //    push this line on curlinebuffer and do not expect
   //    continuation lines.
   //    If, however this is the first line, handle this 
   //    as a normal comment line: in that case no continuation
   //    lines are requested either.
   //

   if (curline.scanfixpre() == FINDENTFIX)
   {
      if (curlines.empty())
	 full_statement = curline.rest();
      else 
      {
	 curlinebuffer.push_front(curline);
	 num_lines--;
	 more = 0;
	 return;
      }
   }

   if (curline.blank_or_comment() || curline.getpregentype() != 0)
   {
      //
      // this is a blank or comment or preprocessor line
      //
      curlines.push_back(curline);

      if (curlines.size() ==1)
	 more = 0;   // do not expect continuation lines
      else
	 more = 1;   // but here we do
      return;
   }

   std::string s = curline.line();

   //
   // replace leading tabs by spaces
   //

   std::string sl = s.substr(0,5);
   if (s.length() >6)
      sl = sl+' '+s.substr(6);

   //
   // this is a line with code
   //
   if (curlines.empty())
   {
      //
      // this is the first line
      //
      curlines.push_back(curline);
      full_statement += trim(sl);
      full_statement = rtrim(remove_trailing_comment(full_statement));
      more = 1;      // maybe there are continuation lines
      return;
   }

   //
   // this is possibly a continuation line
   //
   if (s.length() < 6 || s[5] == ' ' || s[5] == '0')
   {
      //
      // this is not a continuation line
      // push it back, we will see it later
      //
      curlinebuffer.push_front(curline);
      num_lines--;
      more = 0;          // do not look for further continuation lines
      return;
   }
   //
   // this is a continuation line
   //
   curlines.push_back(curline);
   full_statement += rtrim((rtrim(sl)+"      ").substr(6));
   full_statement = rtrim(remove_trailing_comment(full_statement));
   more = 1;   // look for more continuation lines
   return;
}           // end of handle_fixed1

void handle_free(bool &more)
{
   //
   // adds curline to curlines
   // adds curline (stripped from comments, preprocessor stuff and 
   //    continuation stuff)  to full_statement
   // more 1: more lines are to expected
   //      0: this line is complete
   //

   //
   // handle findentfix: 
   //

   if (curlines.empty())
      if (curline.scanfixpre() == FINDENTFIX)
	 full_statement = curline.rest();

   //
   //  if this line is pure comment or empty
   //     add it to curlines
   //

   if (curline.blank_or_comment())
   {
      curlines.push_back(curline);
      more = 0;
      return;
   }

   //
   // sl becomes the first input_line_length characters of curline
   // and then trimmed left and right:
   //

   std::string sl = curline.trimmed_line();

   if(curline.firstchar() == "&")
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

   more = ( lastchar(full_statement) == '&');
   if (more)            // chop off '&' :
      full_statement.erase(full_statement.length()-1);

   curlines.push_back(curline);
}           // end of handle_free


void handle_fixed(bool &more)
{
   //
   // adds curline to curlines
   // adds curline (stripped from comments, preprocessor stuff and 
   //    continuation stuff)  to full_statement
   // more 1: more lines are to expected
   //      0: this line is complete
   //

   //
   // if this is a findentfix line:
   //    Assume that no continuation lines can follow.
   //    So, if there are already one or more lines read,
   //    push this line on curlinebuffer and do not expect
   //    continuation lines.
   //    If, however this is the first line, handle this 
   //    as a normal comment line: in that case no continuation
   //    lines are requested either.
   //

   if (curline.scanfixpre() == FINDENTFIX)
   {
      if (curlines.empty())
	 full_statement = curline.rest();
      else 
      {
	 curlinebuffer.push_front(curline);
	 num_lines--;
	 more = 0;
	 return;
      }
   }

   if (curline.blank_or_comment() || curline.getpregentype() != 0)
   {
      //
      // this is a blank or comment or preprocessor line
      //
      curlines.push_back(curline);

      if (curlines.size() ==1)
	 more = 0;   // do not expect continuation lines
      else
	 more = 1;   // but here we do
      return;
   }

   std::string s = curline.line();

   //
   // replace leading tabs by spaces
   //

   std::string sl = s.substr(0,5);
   if (s.length() >6)
      sl = sl+' '+s.substr(6);

   //
   // this is a line with code
   //
   if (curlines.empty())
   {
      //
      // this is the first line
      //
      curlines.push_back(curline);
      full_statement += trim(sl);
      full_statement = rtrim(remove_trailing_comment(full_statement));
      more = 1;      // maybe there are continuation lines
      return;
   }

   //
   // this is possibly a continuation line
   //
   if (s.length() < 6 || s[5] == ' ' || s[5] == '0')
   {
      //
      // this is not a continuation line
      // push it back, we will see it later
      //
      curlinebuffer.push_front(curline);
      num_lines--;
      more = 0;          // do not look for further continuation lines
      return;
   }
   //
   // this is a continuation line
   //
   curlines.push_back(curline);
   full_statement += rtrim((rtrim(sl)+"      ").substr(6));
   full_statement = rtrim(remove_trailing_comment(full_statement));
   more = 1;   // look for more continuation lines
   return;
}           // end of handle_fixed


void output_line()
{
   if (curlines.empty())
      return;

   mycout.setoutput(!flags.last_indent_only);
   mycout.reset();

   handle_refactor();

   if (!flags.apply_indent)
   {
      //
      // no indentation requested:
      //
      while (! curlines.empty())
      {
	 mycout << curlines.front().orig() << endline;
	 curlines.pop_front();
      }
      return;
   }

   switch(input_format)
   {
      case FREE:
	 switch(output_format)
	 {
	    case FREE:
	       free2free(curlines);
	       break;
	    case FIXED:
	       free2fixed(curlines);
	       break;
	 }
	 break;
      case FIXED:
	 switch(output_format)
	 {
	    case FREE:
	       fixed2free(curlines);
	       break;
	    case FIXED:
	       fixed2fixed(curlines);
	       break;
	 }
	 break;
   }
}           // end of output_line

void handle_refactor()
{
   if (flags.refactor_routines && refactor_end_found)
   {
      //
      // handle refactor routines
      //
      if (cur_rprop.kind != 0) // check if corresponding start is ok
      {
	 //
	 // modify first line to match the corrsponding module, subroutine ... line  
	 // starting at position labellength + spaces, scan lines[0] until isalnumplus()
	 // returns false. The scanned characters will be replaced by something
	 // like: 'end subroutine mysub'
	 //
	 std::string s = curlines.front().trimmed_line();
	 size_t startpos = s.find_first_not_of(' ',labellength);
	 size_t endpos   = s.length();
	 for (size_t i=startpos; i<s.length(); i++)
	 {
	    if (!isalnumplus(s[i]))
	    {
	       endpos = i;
	       break;
	    }
	 }
	 //
	 // correct endpos for trailing spaces:
	 //
	 for (size_t i=endpos-1; ;i--)
	 {
	    bool r;
	    switch(s[i])
	    {
	       case ' ':
	       case '\t':
		  r = 0;
		  break;
	       default:
		  endpos = i+1;
		  r = 1;
		  break;
	    }
	    if (r)
	       break;
	 }
	 std::string replacement = "end " + whatrprop(cur_rprop);
	 if (flags.upcase_routine_type)
	    replacement = stoupper(replacement);
	 if (cur_rprop.name != "")
	    replacement += " " + cur_rprop.name;
	 curlines.front().set_line(s.substr(0,startpos) + replacement + s.substr(endpos));
      }
   }
}

