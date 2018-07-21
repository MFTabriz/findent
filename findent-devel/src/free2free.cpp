#include "findent.h"
#include "findent_functions.h"
void free2free()
{
   std::string firstline  = lines.front();
   std::string ofirstline = olines.front();
   char ofc               = firstchar(ofirstline);
   lines.pop_front();
   olines.pop_front();
   curlines.pop_front();
   lexer_set(firstline,SCANFIXPRE);
   int pretype = yylex();
   if(!handle_pre(firstline, pretype))
   {
      int l;
      if (firstline != "" || lines.size() > 1)
      {
	 if (flags.label_left && labellength > 0)
	 {
	    //
	    // put label at start of line
	    //
	    std::string label = firstline.substr(0,labellength);
	    firstline    = trim(firstline.substr(labellength));
	    mycout << label;
	    l = cur_indent - labellength;
	    if ( l <= 0 )
	       l=1;
	 }
	 else
	    l = cur_indent;
	 //
	 // If first character of original line is '!', do not indent
	 // Do not use start_indent: on the next run the first char could
	 // be space and not '!'
	 //
	 if(ofc == '!')
	    l=0;
	 //
	 // if this is a comment line, and the original line did not start
	 // with '!', and cur_indent == 0: put a space before this line, 
	 // to make sure that re-indenting will give the same result
	 //
	 if (ofc != '!' && firstchar(firstline) == '!' && cur_indent == 0)
	    l=1;

	 if (l<0)
	    l=0;
	 mycout << std::string(l,' '); 
      }
      mycout << firstline << endline;
   }

   //while (!lines.empty())
   while (!curlines.empty())
   {
      mycout.reset();
      //
      // sometimes, there are preprocessor statements within a continuation ...
      //
      //std::string s  = lines.front();
      //std::string os = olines.front();
      //std::string s  = curlines.front().trim();
      //std::string os = curlines.front().orig();

      //char fc  = firstchar(s);
      //char ofc  = firstchar(os);
      std::string fc  = curlines.front().firstchar();
      std::string ofc = curlines.front().orig().substr(0,1);
      int pretype = curlines.front().scanfixpre();
      lines.pop_front();
      olines.pop_front();
      //lexer_set(s,SCANFIXPRE);
      //int pretype = yylex();
      // if(!handle_pre(s,pretype))
      if(!handle_pre(curlines.front().trim(),pretype))
      {
	 if (flags.indent_cont || fc == "&")
	 {
	    int l = 0;
	    //
	    // if first character of original line == '!', do not indent
	    // Do not use start_indent: on the next run the first char could
	    // be space and not '!'
	    //
	    if (ofc == "!")
	       l = 0;
	    else
	    {
	       if (fc == "&")
	       {
		  //
		  // if continuation starts with '&', use current indentation
		  // else use current indentation + flags.cont_indent 
		  //
		  l = std::max(cur_indent,0);
	       }
	       else
	       {
		  l = std::max(cur_indent+flags.cont_indent,0);
	       }
	    }
	    //
	    // if this is a comment line, and the original line did not start
	    // with '!', and cur_indent == 0: put a at least one space before this line, 
	    // to make sure that re-indenting will give the same result
	    //
	    if (ofc != "!" && fc == "!" && cur_indent == 0)
	       l=std::max(1,flags.cont_indent);
	    mycout << std::string(l,' ');
	    //mycout << s <<endline;
	    mycout << curlines.front().trim() <<endline;
	 }
	 else
	    //mycout << os << endline;
	    mycout << curlines.front().orig() << endline;
      }
      curlines.pop_front();
   }
}
