#include "findent.h"
#include "findent_functions.h"
void fixed2free()
{
   unsigned int old_indent   = 0;
   unsigned int first_indent = 0;
   char prevquote            = ' ';
   char preprevquote         = ' ';
   std::string  outputline;
   int lineno = 0;
   std::string needamp = "";

   //while(!lines.empty())
   while(!curlines.empty())
   {
      mycout.reset();
      lineno++;
      std::string s  = lines.front();
      std::string os = olines.front();
      char ofc       = firstchar(os);
      lines.pop_front();
      olines.pop_front();
      curlines.pop_front();
      lexer_set(s,SCANFIXPRE);
      int pretype = yylex();
      if (handle_pre(s,pretype))
	 continue;
      if(isfixedcmtp(s))
      {
	 //
	 // this is an empty line or comment line
	 //
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
      else if(!cleanfive(os)) // check for valid label field
      {
	 mycout << os << endline;  // garbage in, garbage out
      }
      else
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
	    //if (s != "" || lines.size() > 1)
	    if (s != "" || curlines.size() > 1)
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
	 //std::deque<std::string>::iterator it= lines.begin();
	 std::deque<fortranline>::iterator it= curlines.begin();
	 //char prevlchar = 0;
	 std::string prevlchar = "";
	 bool inpreproc = 0;
	 //while(it != lines.end())
	 while(it != curlines.end())
	 {
	    //
	    // if previous lastchar was '\\', do not consider this 
	    // line, if we are in a preprocessor statement
	    //
	    //if (inpreproc && prevlchar == '\\')
	    if (inpreproc && prevlchar == "\\")
	    {
	       //prevlchar = lastchar(*it);
	       //prevlchar = (*it).lastchar();
	       prevlchar = it->lastchar();
	       *it++;
	       continue;
	    }
	    //prevlchar = lastchar(*it);
	    prevlchar = it->lastchar();
	    //inpreproc = (firstchar(*it) == '#' || firstchars(*it,2) == "??");
	    inpreproc = (it->firstchar() == "#" || it->first2chars() == "??");
	    if (!isfixedcmtp((it++)->orig()))
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
