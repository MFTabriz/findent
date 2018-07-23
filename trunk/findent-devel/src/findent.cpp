// $Id$

#include "debug.h"
#include "emacs_plugin.h"
#include "findent.h"
#include "findent_functions.h"
#include "fixed2fixed.h"
#include "fixed2free.h"
#include "free2free.h"
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
std::deque<fortranline>                     curlinebuffer;   // deque for source lines
std::list<fortranline>                      curlines;        // current line, one continuation line per item
std::stack<bool>                            nbseen_stack;    // to store nbseen
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
   // std::string s;
   full_statement       = "";
   indent_handled       = 0;
   bool preproc_more    = 0;
   bool fortran_more    = 0;
   int pregentype       = 0;

   while(1)
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
	 std::string fcts = curline.firstchar();
	 if (input_format == FREE)
	    nbseen = (fcts != "" && fcts != "!" && fcts != "#" && curline.first2chars() != "??");
	 else
	 {
	    char fc = 0;
	    if (curline.orig().length() > 0)
	       fc = curline.orig()[0];
	    if (curline.ltab2sp().length() > 6)
	       nbseen = (fcts != "" && fc != 'c' && fc != 'C' && fc != 'd' && fc != 'D' 
		     && fcts != "!" && fc != '*' && fcts != "#" && curline.first2chars() != "??");
	 }
	 if (flags.auto_firstindent && nbseen)
	 {
	    start_indent = guess_indent(curline.orig());
	    cur_indent   = start_indent;
	    init_indent();
	    indent_handled = 1;
	 }
      }

      int  pretype = curline.scanfixpre();
      bool ispre   = 0;
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
	 pretype = curline.scanfixpre();
	 switch(pretype)
	 {
	    case COCO_IF: case COCO_ENDIF: case COCO_ELSE: case COCO_ELIF: case COCO: 
	       pregentype = COCO;
	       break;
	    default:
	       pregentype   = 0;
	       ispre        = 0;
	       preproc_more = 0;
	       break;
	 }
      }

      if(preproc_more || ispre)
      { 
	 handle_prc(pregentype, preproc_more);
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

void handle_prc(const int pregentype, bool &more)
{
   //
   // adds preprocessor continuation line curline to full statement
   // more = 1: more preprocessor lines are to expected
   //        0: this line is complete
   //
   if(end_of_file)
   {
      more = 0;
      return;
   }
   std::string sl;
   if (curline.firstchar() == "#" || curline.first2chars() == "??")  // TODO
      sl = curline.trim();
   else
      sl = curline.rtrim();

   curlines.push_back(curline);
   std::string lc=curline.lastchar();
   if((pregentype == CPP && lc == "\\") || (pregentype == COCO && lc == "&"))
      more = 1;
   else
      more = 0;
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
   if (curlines.empty())
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
      curlines.push_back(curline);
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

   curlines.push_back(curline);
}           // end of handle_free


void handle_fixed(bool &more)
{
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

   if (isfixedcmtp(curline.orig()))
      //
      // this is a blank or comment or preprocessor line
      //
   {
      curlines.push_back(curline);

      if (curlines.size() ==1)
	 more = 0;   // do not expect continuation lines
      else
	 more = 1;      // but here we do
      return;
   }

   //
   // replace leading tabs by spaces
   //

   std::string sl;
   sl = curline.line().substr(0,5);
   if (curline.line().length() >6)
      sl = sl+' '+curline.line().substr(6);

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
      remove_trailing_comment(full_statement);
      full_statement = rtrim(full_statement);
      more = 1;      // maybe there are continuation lines
      return;
   }

   //
   // this is possibly a continuation line
   //
   if (curline.line().length() < 6 || curline.line()[5] == ' ' || curline.line()[5] == '0')
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
   remove_trailing_comment(full_statement);
   full_statement = rtrim(full_statement);
   more = 1;   // look for more continuation lines
   return;
}           // end of handle_fixed


void output_line()
{
   if (curlines.empty())
      return;

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

   if (! flags.apply_indent)
   {
      //
      // no indention requested:
      //
      while (! curlines.empty())
      {
	 mycout << curlines.front().orig() << endline;
	 curlines.pop_front();
      }
      return;
   }

   if (input_format == FREE)
      free2free();
   else   // input_format = FIXED, output can be FREE or FIXED
   {
      if (output_format == FREE)
	 fixed2free();
      else
	 fixed2fixed();
   }
}           // end of output_line

