// $Id$

#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <unistd.h>

#include "debug.h"
#include "emacs_plugin.h"
#include "findent.h"
#include "flags.h"
#include "free2free.h"
#include "functions.h"
#include "gedit_plugin.h"
#include "lexer.h"
#include "line_prep.h"
#include "parser.h"
#include "prop.h"
#include "readme_plugin.h"
#include "simpleostream.h"
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
int               num_lines;                 // number of lines read sofar
int               output_format;
pre_analyzer      prea;
struct propstruct prev_props;
bool              reading_from_tty    = 0;
bool              refactor_end_found;
int               start_indent;
int               stlabel;

std::stack<int>                             dolabels;        // to store labels, necessary for labelled do
std::stack<std::stack <int> >               dolabels_stack;  // to store dolabels stack
std::stack<int>                             indent;          // to store indents
std::stack<std::stack <int> >               indent_stack;    // to store indent stack
std::deque <fortranline>                    curlinebuffer;   // deque for source lines
std::deque <std::string>                    lines;           // current line, one continuation line per item
std::stack<bool>                            nbseen_stack;    // to store nbseen
std::deque <std::string>                    olines;          // the original line
std::stack<struct propstruct>               rprops;          // to store routines (module, subroutine ...)
std::stack<std::stack <struct propstruct> > rprops_stack;

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
      input_format = determine_fix_or_free(1);

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
   get_full_statement();
   cur_indent   = start_indent;
   indent_and_output();
   if(end_of_file)
   {
      if(flags.last_indent_only)
      {
	 std::cout << num_leading_spaces(mycout.get()) << endline;
      }
      return what_to_return();
   }

   while(1)
   {
      get_full_statement();
      indent_and_output();
      if (end_of_file)
      {
	 if(flags.last_indent_only)
	 {
	    std::cout << num_leading_spaces(mycout.get()) << endline;
	 }
	 return what_to_return();
      }
   }
   return what_to_return();
}

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
      while (!lines.empty())
      {
	 lexer_set(lines.front(),SCANFIXPRE);
	 int pretype = yylex();
	 int ifelse  = preb.analyze(trim(lines.front()),pretype);
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
	 lines.pop_front();
	 olines.pop_front();
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
	    {
	       push_dolabel(string2number<int>(props.dolabel));
	    }
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
   std::string s;
   full_statement       = "";
   indent_handled       = 0;
   bool preproc_more    = 0;
   bool fortran_more    = 0;
   int pregentype       = 0;

   while(1)
   {
      //if (linebuffer.empty())
      if (curlinebuffer.empty())
      {
	 mygetline();
	 s = curline.orig();
      }
      else
      {
	 //s = linebuffer.front();
	 //linebuffer.pop_front();
	 curline = curlinebuffer.front();
	 curlinebuffer.pop_front();
	 s = curline.orig();
	 if (reading_from_tty && s == ".")
	    end_of_file = 1;
      }

      num_lines++;

      if (!nbseen)
      {
	 //char fcts = firstchar(trim(s));
	 std::string fcts = curline.firstchar();
	 if (input_format == FREE)
	    // nbseen = (fcts != 0 && fcts != '!' && fcts != '#' && firstchars(trim(s),2) != "??");
	    nbseen = (fcts != "" && fcts != "!" && fcts != "#" && curline.first2chars() != "??");
	 else
	 {
	    std::string s1 = ltab2sp(s);
	    if (s1.length() > 6)
	       //	       nbseen = (s[0] != 'c' && s[0] != 'C' && s[0] != 'd' && s[0] != 'D' 
	       //		     && fcts != '!' && s[0] != '*' && fcts != '#' && firstchars(trim(s),2) != "??");
	       nbseen = (s[0] != 'c' && s[0] != 'C' && s[0] != 'd' && s[0] != 'D' 
		     && fcts != "!" && s[0] != '*' && fcts != "#" && curline.first2chars() != "??");
	 }
	 if (flags.auto_firstindent && nbseen)
	 {
	    start_indent = guess_indent(s);
	    cur_indent   = start_indent;
	    init_indent();
	    indent_handled = 1;
	 }
      }


      //lexer_set(s,SCANFIXPRE);
      //int pretype = yylex();
      int pretype = curline.scanfixpre();
      bool ispre = 0;
      if (!preproc_more)
      {
	 pregentype = 0;
	 switch(pretype)
	 {
	    case CPP_IF: case CPP_ENDIF: case CPP_ELSE: case CPP_ELIF: case CPP: 
	       pregentype = CPP;
	       ispre      = 1;
	       break;
	    case COCO_IF: case COCO_ENDIF: case COCO_ELSE: case COCO_ELIF: case COCO: 
	       pregentype = COCO;
	       ispre      = 1;
	       break;
	 }
      }
      else if(pregentype == COCO)  // coco continuation lines must start with ??
      {
	 //lexer_set(s,SCANFIXPRE);
	 //pretype = yylex();
	 pretype = curline.scanfixpre();
	 switch(pretype)
	 {
	    case COCO_IF: case COCO_ENDIF: case COCO_ELSE: case COCO_ELIF: case COCO: 
	       pregentype = COCO;
	       break;
	    default:
	       pregentype = 0;
	       ispre      = 0;
	       preproc_more = 0;
	       break;
	 }
      }

      if(preproc_more || ispre)
      { 
	 handle_prc(s, pregentype, preproc_more);
	 if (preproc_more || fortran_more)
	    continue;
	 else
	    break;
      }

      if (input_format == FREE)
      {
	 handle_free(fortran_more);
	 if (fortran_more) 
	    continue;
	 else
	    break;
      }
      else
      {
	 handle_fixed(fortran_more);
	 if (fortran_more)
	    continue;
	 else
	    break;
      }
   }
}           // end of get_full_statement

void handle_prc(std::string s, const int pregentype, bool &more)
{
   //
   // adds preprocessor continuation line s to full statement
   // more = 1: more preprocessor lines are to expected
   //        0: this line is complete
   //
   if(end_of_file)
   {
      more = 0;
      return;
   }
   std::string sl;
   std::string sl1 = trim(s);
   if (firstchar(sl1) == '#' || firstchars(sl1,2) == "??")  // TODO
      sl = sl1;
   else
      sl = rtrim(s);

   lines.push_back(sl);
   olines.push_back(s);
   char lc=lastchar(sl);
   if((pregentype == CPP && lc == '\\') || (pregentype == COCO && lc == '&'))
   {
      more = 1;
   }
   else
   {
      more = 0;
   }
}         // end of handle_prc

void handle_free(bool &more)
{
   //
   // adds curline to full_statement
   // more 1: more lines are to expected
   //      0: this line is complete
   //

   if(end_of_file)
   {
      more = 0;
      return;
   }

   //
   // handle findentfix: 
   //
   if (lines.empty())
      if (curline.scanfixpre() == FINDENTFIX)
	 full_statement = curline.rest();

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

   //
   //  if this line is pure comment or empty
   //     add it to lines
   //

   if (sl == "" || firstchar(sl) == '!' )
   {
      lines.push_back(curline.trimmed_line());
      olines.push_back(curline.orig());
      return;
   }

   full_statement = full_statement + sl;

   //
   // remove trailing comment and trailing white space
   //

   remove_trailing_comment(full_statement);
   full_statement = rtrim(full_statement);

   // 
   // If the last character = '&', a continuation is expected.
   //
   more = ( lastchar(full_statement) == '&');
   if (more)            // chop off '&' :
      full_statement.erase(full_statement.length()-1);

   lines.push_back(curline.trimmed_line());
   olines.push_back(curline.orig());
}           // end of handle_free


void handle_fixed(bool &more)
{
   std::string s = curline.orig();
   if(end_of_file)
   {
      more = 0;
      return;
   }

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
      if (lines.empty())
	 full_statement = curline.rest();
      else 
      {
	 curlinebuffer.push_front(curline);
	 num_lines--;
	 more = 0;
	 return;
      }
   }

   if (isfixedcmtp(s))
      //
      // this is a blank or comment or preprocessor line
      //
   {
      lines.push_back(trim(s));
      olines.push_back(s);
      if (lines.size() ==1)
	 more = 0;   // do not expect continuation lines
      else
	 more = 1;      // but here we do
      return;
   }

   //
   // replace leading tabs by spaces
   //
   s = ltab2sp(s);

   std::string sl;
   sl = s.substr(0,5);
   if (s.length() >6)
      sl = sl+' '+s.substr(6);

   //
   // this is a line with code
   //
   if (lines.empty())
   {
      //
      // this is the first line
      //
      lines.push_back(s);
      olines.push_back(s);
      full_statement += trim(sl);
      remove_trailing_comment(full_statement);
      full_statement = rtrim(full_statement);
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
   lines.push_back(s);
   olines.push_back(s);
   full_statement += rtrim((rtrim(sl)+"      ").substr(6));
   remove_trailing_comment(full_statement);
   full_statement = rtrim(full_statement);
   more = 1;   // look for more continuation lines
   return;
}           // end of handle_fixed


void output_line()
{
   if (lines.empty())
      return;
   int lineno                     = 0;
   std::string needamp            = "";
   char prevquote                 = ' ';
   char preprevquote              = ' ';
   std::string outputline;

   mycout.setoutput(!flags.last_indent_only);
   mycout.reset();

   if (flags.refactor_routines && refactor_end_found)
   {
      if (cur_rprop.kind != 0) // check if corresponding start is ok
      {
	 //
	 // modify first line to match the corrsponding module, subroutine ... line  
	 // starting at position labellength + spaces, scan lines[0] until isalnumplus()
	 // returns false. The scanned characters will be replaced by something
	 // like: 'end subroutine mysub'
	 //
	 std::string s   = lines[0];
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
	 lines[0] = s.substr(0,startpos) + replacement + s.substr(endpos);
	 if (! flags.apply_indent)
	    olines[0] = lines[0];
      }
   }

   if (! flags.apply_indent)
   {
      //
      // no indention requested:
      //
      while (! olines.empty())
      {
	 mycout << olines.front() << endline;
	 lines.pop_front();
	 olines.pop_front();
      }
      return;
   }

   if (input_format == FREE)
      free2free();
   else   // input_format = FIXED, output can be FREE or FIXED
   {
      unsigned int old_indent = 0;
      unsigned int first_indent = 0;
      while(!lines.empty())
      {
	 mycout.reset();
	 lineno++;
	 std::string s  = lines.front();
	 std::string os = olines.front();
	 char ofc       = firstchar(os);
	 char ftc       = firstchar(trim(s));
	 lines.pop_front();
	 olines.pop_front();
	 lexer_set(s,SCANFIXPRE);
	 int pretype = yylex();
	 if (handle_pre(s,pretype))
	    continue;
	 if(isfixedcmtp(s))
	 {
	    //
	    // this is an empty line or comment line
	    //
	    if (output_format == FIXED)
	    {
	       if (ofc == '!')                   // do not change lines starting with !
		  mycout << rtrim(os) << endline;
	       else if ( ftc == '!')             // indent indented comments
		  mycout << std::string(6+cur_indent,' ') << trim(s) << endline;
	       else
		  mycout << trim(s) << endline;
	    }
	    else  // output_format = FREE
	    {
	       if (trim(s) == "")
		  mycout << endline;
	       else
	       {
		  switch (ofc)
		  {
		     //
		     // special hack for lines starting with 'd' or 'D'
		     //
		     case 'd' : case 'D' :
			mycout << "!" + rtrim(os) << endline;
			break;
		     case 'c': case 'C': case '*': case '!':
			mycout << '!' << rtrim(os.substr(1)) << endline;
			break;
		     default:  // this must be a ! comment, not starting in column 1
			mycout << std::string(std::max(cur_indent,1),' ') << trim(os) << endline;
		  }
	       }
	    }
	 }
	 else if(!cleanfive(os)) // check for valid label field
	 {
	    mycout << os << endline;  // garbage in, garbage out
	 }
	 else
	 {
	    if (output_format == FIXED)
	    {
	       mycout << s.substr(0,6);

	       if(s.length() > 6)
	       {
		  bool iscont = (s[5] != ' ' && s[5] != '0');
		  //
		  // try to honor current indentation
		  // if this is a continuation line, count the number
		  // of spaces after column 6.
		  //
		  if (iscont)
		  {
		     std::string s6 = ltab2sp(s.substr(6))+'x';
		     old_indent = s6.find_first_not_of(' ');
		  }
		  else
		  {
		     //
		     // count the number of spaces after column 6 of the first line
		     //
		     std::string s6 = ltab2sp(s.substr(6))+'x';
		     first_indent = s6.find_first_not_of(' ');
		  }
		  int adjust_indent = old_indent - first_indent;
		  if (adjust_indent < 0)
		     adjust_indent = 0;

		  switch(prevquote)
		  {
		     case ' ' :   // no dangling strings, output with indent
			mycout << std::string(std::max(adjust_indent+cur_indent,0),' ') << trim(s.substr(6));
			break;
		     default:  // dangling string, output asis
			mycout << s.substr(6);
			break;
		  }
		  //
		  // investigate if this line terminates a string
		  //
		  prevquote = fixedmissingquote(prevquote + s);
	       }

	       mycout << endline;
	    }
	    else  // output_format == FREE
	    {
	       outputline = needamp;
	       if (lineno == 1)
	       {
		  int l;
		  if (s.length()>6)
		  {
		     std::string s6 = ltab2sp(s.substr(6))+'x';
		     first_indent = s6.find_first_not_of(' ');
		  }
		  if (s != "" || lines.size() > 1)
		  {
		     if (flags.label_left && labellength > 0)
		     {
			//
			// put label at start of line
			//
			s = trim(s);
			std::string label = s.substr(0,labellength);
			s    = trim(s.substr(labellength));
			mycout << label;
			l = cur_indent - labellength;
			if ( l <= 0 )
			   l=1;
		     }
		     else
			l = cur_indent;

		     mycout <<std::string(std::max(l,0),' '); 
		  }
		  outputline += trim(s);
		  //
		  // we need the value of prevquote later on:
		  //
		  preprevquote = prevquote;
		  prevquote    = fixedmissingquote(prevquote + s);
	       }
	       else
	       {
		  if (s.length() >6)
		  {
		     mycout << std::string(std::max(cur_indent,0),' ');
		     //
		     // try to honor current indentation
		     // if this is a continuation line, count the number
		     // of spaces after column 6.
		     //
		     if (s[5] != ' ' && s[5] != '0')
		     {
			std::string s6 = ltab2sp(s.substr(6))+'x';
			old_indent     = s6.find_first_not_of(' ');
		     }
		     int adjust_indent = old_indent - first_indent;
		     if (adjust_indent < 0 || prevquote!=' ')
			adjust_indent  = 0;

		     std::string s1 = s.substr(6);
		     if (prevquote == ' ')
			s1 = trim(s1);
		     if (s1 != "")
			outputline += std::string(adjust_indent,' ');
		     outputline += s1;
		     //
		     // we need the value of prevquote later on:
		     //
		     preprevquote = prevquote;
		     prevquote    = fixedmissingquote(prevquote + s1);
		  }
	       }
	       //
	       // check for continuation lines
	       // there is a continuation line if there is a non-comment in 
	       // the lines deque, in that case a trailing & is needed
	       // and the non-comment line needs a leading &
	       //
	       needamp="";
	       std::deque<std::string>::iterator it= lines.begin();
	       char prevlchar = 0;
	       bool inpreproc = 0;
	       while(it != lines.end())
	       {
		  //
		  // if previous lastchar was '\\', do not consider this 
		  // line, if we are in a preprocessor statement
		  //
		  if (inpreproc && prevlchar == '\\')
		  {
		     prevlchar = lastchar(*it);
		     *it++;
		     continue;
		  }
		  prevlchar = lastchar(*it);
		  inpreproc = (firstchar(*it) == '#' || firstchars(*it,2) == "??");
		  if (!isfixedcmtp(*it++))
		  {
		     needamp =  '&';
		     //
		     // we have to put an '&' at the end of the line,
		     // but what if the line ends in a ! comment, as in
		     //   x = x *  ! comment
		     // Then we have to put the '&' like this:
		     //   x = x * & ! comment
		     // but in this case:
		     //  x = ' a string ! no comment
		     // we have to place the '&' like this:
		     //  x = ' a string ! no comment&
		     //
		     // if there is an unterminated string, then:
		     //
		     if (prevquote != ' ')
		     {
			outputline = outputline + '&';
			break;
		     }
		     //
		     // the line does not contain an unterminated string,
		     // is there a !comment outside a string?
		     // here we need the value of preprevquote:
		     //
		     std::string work = preprevquote + outputline;
		     int p0 = work.size();
		     remove_trailing_comment(work);
		     int p  = work.size();
		     if (p0 != p)
		     {
			//
			// there is a comment outside strings,
			// the number of characters before the comment
			// has to be decreased by one, because
			// of the prepending of preprevquote
			//
			p = std::max(p-1,0);
			outputline = outputline.substr(0, p) + '&' + outputline.substr(p);
			break;
		     }
		     else
		     {
			//
			// no !comment, simply put '&' at the end
			//
			outputline += '&';
			break;
		     }
		  }
	       }
	       mycout << outputline << endline;
	    }
	 }
      }
   }
}           // end of output_line


int determine_fix_or_free(const bool store)
{
   // apperantly: store is always 1 ...
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

	 if(store && reading_from_tty)
	 {
	    //linebuffer.push_back(s);       // s == "."
	    curlinebuffer.push_back(curline);
	 }
	 break;
      }

      if (store)
      {
	 //linebuffer.push_back(s);
	 curlinebuffer.push_back(curline);
      }

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

bool handle_pre(const std::string s, const int pretype)
{
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

   mycout << s << endline;
   char lchar = lastchar(s);
   while (!lines.empty())
   {
      if (pregentype == CPP && lchar != '\\')
	 return 1;
      // coco continuation lines must start with ??, but we ignore that

      if (pregentype == COCO && lchar != '&')
	 return 1;

      mycout <<lines.front() << endline;
      lchar = lastchar(lines.front());
      lines.pop_front();
      olines.pop_front();
   }
   return 1;
}       // end of handle_pre

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
