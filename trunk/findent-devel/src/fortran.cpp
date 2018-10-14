#include "fortran.h"
#include "pre_analyzer.h"
#include "line_prep.h"

#define Cur_indent   fi->cur_indent
#define FLAGS        fi->flags
#define Endline      fi->endline
#define End_of_file  fi->end_of_file
#define Getnext      fi->getnext
#define Curline      (*curline)

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
	 fi->handle_pre_light(lines.front(),p_more);
	 if (lines.front().pre())
	    if (to_mycout)
	       mycout << lines.front().trim() << Endline;
	    else
	       outlines->push_back(F(lines.front().trim()));
	 else
	    if (to_mycout)
	       mycout << lines.front().str() << Endline;
	    else
	       outlines->push_back(F(lines.front().str()));
	 lines.pop_front();
	 if (lines.empty() || !p_more)
	    break;
      }
      return 1;
   }
   else
      return 0;
}     // end of output_pre


void Fortran::handle_last_usable_only()
{
   //
   // search for the last line that is usable to start indenting
   // using findent.
   //
   int usable_line = 1;

   fi->init_indent();
   while(1)
   {
      int prev         = fi->num_lines;
      get_full_statement();
      Line_prep p(full_statement);
      propstruct props = parseline(p);
      switch (props.kind)
      {
	 case BLANK:
	 case CASE:
	 case CASEDEFAULT:
	 case CLASSIS:
	 case CLASSDEFAULT:
	 case CONTAINS:
	 case ENTRY:
	 case ELSE:
	 case ELSEIF:
	 case ELSEWHERE:
	 case TYPEIS:
	    break;
	 default: 
	    usable_line = prev+1;
	    break;
      }
      if (End_of_file)
      {
	 std::cout << usable_line << Endline;
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

   // 
   // see fortran.h for definitions of some variables
   //

   full_statement = "";
   fi->indent_handled=0;

   if (first_call)
   {
      Curline = Getnext(End_of_file);
      first_call = 0;
   }

   while(!curlines.empty())
      curlines.pop_back();

   while(1)
   {
      switch(state)
      {
	 case start:
	    if (fs_store.empty())
	       full_statement = "";
	    else
	       full_statement = fs_store.back();

	    if (End_of_file) 
	    {
	       state = end_start;
	       break;
	    }
	    pretype = Curline.getpregentype();
	    if(pretype == CPP || pretype == COCO)
	    {
	       state = in_pre;
	       break;
	    }
	    if (is_findentfix(Curline))
	    {
	       state = in_ffix;
	       break;
	    }

	    state = in_fortran;
	    break;

	 case in_ffix:
	    curlines.push_back(Curline);
	    full_statement = rtrim(remove_trailing_comment(Curline.rest()));
	    Curline = Getnext(End_of_file);
	    state = start;
	    return;

	 case in_fortran:
	    if(End_of_file) { state = end_fortran; break; }

	    build_statement(Curline, f_more, pushback);

	    if (f_more)
	    {
	       Curline = Getnext(End_of_file); 
	       if (End_of_file) { state = end_fortran; break; }
	       pretype = Curline.getpregentype();
	       if (pretype == CPP || pretype == COCO)
	       {
		  p_more = 0;
		  while (1)
		  {
		     handle_pre(Curline,f_more,p_more);
		     curlines.push_back(Curline);
		     if(p_more)
		     {
			Curline = Getnext(End_of_file); 
			if (End_of_file) { state = end_fortran; break; }
		     }
		     else
			break;
		  }
		  Curline = Getnext(End_of_file);
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
	    if (!pushback)
	       Curline = Getnext(End_of_file);
	    state = start;
	    break;

	 case in_pre:
	    p_more = 0;
	    while(1)
	    {
	       handle_pre(Curline,f_more,p_more);
	       curlines.push_back(Curline);
	       if(p_more)
	       {
		  Curline = Getnext(End_of_file); 
		  if (End_of_file) { state = end_pre; break; }
	       }
	       else
		  break;
	    }
	    Curline = Getnext(End_of_file);
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
	       case Pre_analyzer::IF:
		  push_all();
		  break;

	       case Pre_analyzer::ELIF:
		  top_all();
		  break;

	       case Pre_analyzer::ELSE:
		  top_all();
	       case Pre_analyzer::ENDIF:
		  pop_all();
		  break;

	       case Pre_analyzer::ENDIFE:
		  break;

	       default:
		  return;
		  break;
	    }

	    switch(ifelse) // full_statement needs apart treatment:
	    {
	       case Pre_analyzer::IF:
		  fs_store.push_back(full_statement);
		  break;

	       case Pre_analyzer::ELIF:
		  if(fs_store.empty())
		     full_statement = "";
		  else
		     full_statement = fs_store.back();
		  break;

	       case Pre_analyzer::ELSE:
		  if(fs_store.empty())
		     full_statement = "";
		  else
		     full_statement = fs_store.back();
		  break;

	       case Pre_analyzer::ENDIF:
	       case Pre_analyzer::ENDIFE:
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

void Fortran::indent_and_output()
{
   std::string rest = full_statement;
   bool first_time  = 1;
   while(1)
   {
      Line_prep p(rest);
      propstruct props = parseline(p); 
      fi->labellength = props.label.size();
      if (fi->labellength > 0)
	 //
	 // if there was a previous labeled do, handle it:
	 //
      {
	 int ilabel = string2number<int>(props.label);
	 while ( top_dolabel() == ilabel )
	 {
	    pop_indent();
	    pop_dolabel();
	    Cur_indent = top_indent();
	    fi->indent_handled = 1;
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
	    case CHANGETEAM:
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
	       Cur_indent = top_indent();
	       push_indent(Cur_indent + FLAGS.routine_indent);
	       empty_dolabels();
	       push_rprops(prev_props);
	       break;
	    default:
	       break;
	 }
      }
      Cur_indent = top_indent();
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
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.routine_indent);
	    empty_dolabels();
	    push_rprops(props);
	    break;
	 case MODULE:
	 case SUBMODULE:
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.module_indent);
	    empty_dolabels();
	    push_rprops(props);
	    break;
	 case BLOCK:
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.block_indent);
	    break;
	 case CHANGETEAM:
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.changeteam_indent);
	    break;
	 case CRITICAL:
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.critical_indent);
	    break;
	 case ENUM:
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.enum_indent);
	    empty_dolabels();
	    break;
	 case ABSTRACTINTERFACE:
	 case INTERFACE:
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.interface_indent);
	    empty_dolabels();
	    break;
	 case DO:
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.do_indent);
	    if (props.dolabel != "")
	       push_dolabel(string2number<int>(props.dolabel));
	    break;
	 case SELECTCASE:
	 case SELECTTYPE:
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.select_indent);
	    break;
	 case CASE:
	 case CASEDEFAULT:
	 case CLASSDEFAULT:
	 case CLASSIS:
	 case TYPEIS:
	    Cur_indent -= FLAGS.case_indent;
	    break;
	 case END:
	 case ENDBLOCKDATA:
	 case ENDFUNCTION:
	 case ENDMODULE:
	 case ENDPROCEDURE:
	 case ENDPROGRAM:
	 case ENDSUBROUTINE:
	    refactor_end_found = 1;
	    if (!fi->indent_handled)
	       Cur_indent = pop_indent();
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
	 case ENDTEAM:
	 case ENDTYPE:
	 case ENDWHERE:
	    if (!fi->indent_handled)
	       Cur_indent = pop_indent();
	    break;
	 case PROCEDURE:  // in fact: moduleprocedure
	    //
	    // depending on what follows this will be 
	    // recognized as a module procedure with content
	    // or only a moduleprocedure specification
	    //
	    break;
	 case CONTAINS:
	    if (FLAGS.indent_contain)
	       Cur_indent -= FLAGS.contains_indent;
	    else
	    {
	       Cur_indent = fi->start_indent;
	       pop_indent();
	       push_indent(Cur_indent);
	    }
	    break;
	 case IF:
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.if_indent);
	    break;
	 case ELSE:
	    Cur_indent -= FLAGS.if_indent;
	    break;
	 case ELSEIF:
	    Cur_indent -= FLAGS.if_indent;
	    break;
	 case ELSEWHERE:
	    Cur_indent -= FLAGS.where_indent;
	    break;
	 case ENTRY:
	    Cur_indent -= FLAGS.entry_indent;
	    break;
	 case WHERE:
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.where_indent);
	    break;
	 case ASSOCIATE:
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.associate_indent);
	    break;
	 case TYPE:
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.type_indent);
	    break;
	 case FORALL:
	    Cur_indent = top_indent();
	    push_indent(Cur_indent + FLAGS.forall_indent);
	    break;
	 case INCLUDE:
	    if (FLAGS.include_left)
	       Cur_indent = fi->start_indent;
	    else
	       Cur_indent = top_indent();
	    D(O("INCLUDE");O(props.stringvalue);O(FLAGS.deps);O(FLAGS.include_left);O(fi->start_indent);O(top_indent()););
	    if (FLAGS.deps)
	       fi->includes.push((struct twostrings){"inc",props.stringvalue});
	    break;
	 case INCLUDE_CPP:
	    D(O("INCLUDE_CPP");O(props.stringvalue);O(FLAGS.deps););
	    if (FLAGS.deps)
	       fi->includes.push((struct twostrings){"cpp",props.stringvalue});
	    break;
	 case INCLUDE_CPP_STD:
	    D(O("INCLUDE_CPP_STD");O(props.stringvalue);O(FLAGS.deps););
	    if (FLAGS.deps)
	       fi->includes.push((struct twostrings){"std",props.stringvalue});
	    break;
	 case INCLUDE_COCO:
	    D(O("INCLUDE_COCO");O(props.stringvalue);O(FLAGS.deps););
	    if (FLAGS.deps)
	       fi->includes.push((struct twostrings){"coco",props.stringvalue});
	    break;
	 default:
	    Cur_indent = top_indent();
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

void Fortran::output_line()
{
   if (curlines.empty())
      return;

   mycout.reset();

   handle_refactor();

   if (!FLAGS.apply_indent)
   {
      //
      // no indentation requested:
      //
      while (! curlines.empty())
      {
	 mycout << curlines.front().str() << Endline;
	 curlines.pop_front();
      }
      return;
   }

   if (fi->input_format == fi->output_format)
      output(curlines);
   else
      output_converted(curlines);


}           // end of output_line

void Fortran::handle_refactor()
{
   if (FLAGS.refactor_routines && refactor_end_found)
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
	 size_t startpos = s.find_first_not_of(' ',fi->labellength);
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
	 if (FLAGS.upcase_routine_type)
	    replacement = stoupper(replacement);
	 if (cur_rprop.name != "")
	    replacement += " " + cur_rprop.name;
	 it->str(s.substr(0,startpos) + replacement + s.substr(endpos));
      }
   }
}


#undef Cur_indent
#undef FLAGS
#undef Endline
#undef End_of_file
#undef Getnext
#undef Curline
