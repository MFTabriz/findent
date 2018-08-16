#include <iostream>
#include <string>

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

#include "newfindent.h"

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
bool              nbseen;                    // true if non-blank-line is seen 
int               num_lines;                 // number of lines read sofar
int               output_format;
debugostream      ppp;
pre_analyzer      prea;
struct propstruct prev_props;
bool              reading_from_tty    = 0;
bool              refactor_end_found;
int               start_indent;
int               stlabel;

linebuffer_t     curlinebuffer;   // deque for source lines
lines_t          curlines;        // current line, one continuation line per item
dolabels_store_t dolabels_store;  // to store dolabels
dolabels_t       dolabels;        // to store labels, necessary for labelled do
fs_store_t       fs_store;        // to store full_statement
fortranline      getnext(bool &eof, bool use_wb = 1);
indent_store_t   indent_store;    // to store indent store
indent_t         indent;          // to store indents
linebuffer_t     wizardbuffer;    // to store wizard lines and push back lines from handle_fortran
nbseen_store_t   nbseen_store;    // to store nbseen
rprops_store_t   rprops_store;
rprops_t         rprops;          // to store routines (module, subroutine ...)

int main(int argc, char*argv[])
{
   newfindent();
   fortranline::g_format(UNKNOWN);
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

   fortranline::line_length(flags.input_line_length);
   fortranline::gnu_format(flags.input_format_gnu);
   start_indent = flags.start_indent;
   handle_reading_from_tty();

   input_format = flags.input_format;
   if (input_format == UNKNOWN)
      input_format = determine_fix_or_free();

   fortranline::g_format(input_format);

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

   num_lines        = 0;
   labellength      = 0;
   end_of_file      = 0;
   cur_rprop        = empty_rprop;
   init_indent();
   if (flags.last_usable_only)
   {
      mycout.setoutput(0);
      handle_last_usable_only();
      return what_to_return();
   }
   if (flags.last_indent_only)
      mycout.setoutput(0);

   cur_indent = start_indent;
   while(1)
   {
      full_statement = "";
      get_full_statement();
      indent_and_output();
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
      // for every entity that is eligible for refacoring it's end
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
      if(first_time)  // check to handle multi-statement line like x=1;y=3
      {
	 output_line();
	 first_time = 0;
      }
      rest = p.get_line_rest();
      if (rest == "")
	 break;
   }
}               // end of indent_and_output

fortranline getnext(bool &eof, bool use_wb)
{
   fortranline line;
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
      nbseen = !line.blank_or_comment() && (line.getpregentype() == 0);
      if (flags.auto_firstindent && nbseen)
      {
	 start_indent = guess_indent(line);
	 cur_indent   = start_indent;
	 init_indent();
	 indent_handled = 1;
      }
   }

   return line;
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
   indent_handled = 0;

   //
   // 'pushback' and 'first_call' must be static in this version,
   // for safety 'pretype' and 'f_more' and 'p_more' are also made static
   //
   static int pretype;     // 
   static bool f_more = 0;
   static bool p_more;
   static bool pushback;
   static bool first_call = 1;

   if (first_call)
   {
      curline = getnext(end_of_file);
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

	    if (end_of_file) 
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
	    curline = getnext(end_of_file);
	    state = start;
	    return;

	 case in_fortran:
	    if(end_of_file) { state = end_fortran; break; }

	    handle_fortran(curline, f_more, pushback);
	    if (f_more)
	    {
	       curline = getnext(end_of_file); if (end_of_file) { state = end_fortran; break; }
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
			curline = getnext(end_of_file); if (end_of_file) { state = end_fortran; break; }
		     }
		     else
			break;
		  }
		  curline = getnext(end_of_file);
	       }
	       state = in_fortran;
	       break;
	    }
	    state = in_fortran_1;
	    //
	    // need state in_fortran_1 to get correct result from last_usable
	    //
	    return;

	 case in_fortran_1:
	    if (!pushback)                     // here is why pushback has to be static
	       curline = getnext(end_of_file);
	    state = start;
	    break;

	 case in_pre:
	    p_more = 0;
	    while(1)
	    {
	       handle_pre(curline,f_more,p_more);
	       curlines.push_back(curline);
	       if(p_more)
	       {
		  curline = getnext(end_of_file); if (end_of_file) { state = end_pre; break; }
	       }
	       else
		  break;
	    }
	    curline = getnext(end_of_file);
	    state = start;
	    break;

	 case end_start:
	 case end_fortran:
	 case end_pre:
	    state = start;
	    return;
      }
   }
}           // end of get_full_statement


void handle_fortran(fortranline &line,bool &f_more, bool &pushback)
{
   if (input_format == FREE)
      handle_free(line,f_more,pushback);
   else
      handle_fixed(line,f_more,pushback);
}  // end of handle_fortran

void handle_free(fortranline &line, bool &f_more, bool &pushback)
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
}           // end of handle_free

bool is_findentfix(fortranline &line)
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

void handle_fixed(fortranline &line, bool &f_more, bool &pushback)
{
   //
   // adds line to curlines
   // adds line (stripped from comments, preprocessor stuff and 
   //    continuation stuff)  to full_statement
   // f_more 1: more lines are to expected
   //        0: this line is complete
   //
   // TODO: push back all trailing comments, an extra deque is needed for that
   // in main. Has consequences for handle_refactor
   // Implementation: ?

   pushback = 0;

   if (line.blank_or_comment())
   {
      curlines.push_back(line);

      if (curlines.size() ==1)
	 f_more = 0;   // do not expect continuation lines
      else
	 f_more = 1;   // but here we do
      return;
   }

   //
   // replace leading tabs by spaces
   //

   std::string s = line.str();

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
      curlines.push_back(line);
      full_statement += trim(sl);
      full_statement = rtrim(remove_trailing_comment(full_statement));
      if (!f_more)
	 f_more = wizard();     // is there a continuation line in the future?
      return;
   }

   // 
   // special attention for garbage lines:
   //
   if(!cleanfive(s))
   {
      curlines.push_back(line);
      return;
   }
   //
   // this is possibly a continuation line
   //
   if (!line.fixedcontinuation())
   {
      //
      // this is not a continuation line
      // push it back, we will see it later
      //
      pushback = 1;
      f_more   = 0;          // do not look for further continuation lines
      return;
   }
   //
   // this is a continuation line
   //
   curlines.push_back(line);
   full_statement += rtrim((rtrim(sl)+"      ").substr(6));
   full_statement = rtrim(remove_trailing_comment(full_statement));
   if(!f_more)
      f_more = wizard();   // look for more continuation lines
   return;
}           // end of handle_fixed

void output_line()
{
   if (curlines.empty())
      return;

   mycout.reset();

   handle_refactor();

   if (!flags.apply_indent)
   {
      //
      // no indentation requested:
      //
      while (! curlines.empty())
      {
	 mycout << curlines.front().str() << endline;
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
	 // modify line to match the corrsponding module, subroutine ... line  
	 // first, we have to locate that line, the back of the deque
	 // could have comment or empty lines
	 //
	 lines_t::reverse_iterator it = curlines.rbegin();
	 while (it != curlines.rend())
	 {
	    if ( it->blank_or_comment_or_pre() )
	       it++;
	    else
	       break;
	 }

	 // starting at position labellength + spaces, scan lines[0] until isalnumplus()
	 // returns false. The scanned characters will be replaced by something
	 // like: 'end subroutine mysub'
	 //
	 //std::string s = curlines.back().trimmed_line();
	 std::string s = it->trimmed_line();
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
	 it->str(s.substr(0,startpos) + replacement + s.substr(endpos));
      }
   }
}

bool wizard()
{
   //
   // look ahead to see if the next format fortran line is a continuation
   // return 1 if a continuation is found, 0 otherwize
   // for free format, always return 0
   //

   // 
   // TODO: wizard keeps no track of preprocessor statements, so it could be fooled
   // like:
   //       do
   //     #ifdef X
   //      1  i=1,10
   //     #else
   //      2  j=1,10
   //     #endif
   //       enddo
   if (fortranline::g_format() == FREE)
      return 0;

   fortranline line;
   bool eof;

   while(1)
   {
      line = getnext(eof,0);
      if (eof)
	 return 0;

      if (line.pre())
      {
	 bool p_more = 0;
	 while(1)
	 {
	    handle_pre_light(line,p_more);
	    if (p_more)
	    {
	       line = getnext(eof,0);
	       if (eof)
		  return 0;
	    }
	    else
	       break;
	 }
	 if(eof)
	    return 0;
	 continue;
      }

      if (line.fortran() && cleanfive(line.str()))
      {
	 //
	 // return 1 if this is a fixed fortran continuation line
	 //
	 return line.fixedcontinuation();
      }
   }
   return 0;
}     // end of wizard

