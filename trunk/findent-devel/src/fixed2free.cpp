#include <string>
#include <vector>

#include "debug.h"
#include "findent.h"
#include "findent_functions.h"
#include "fortranline.h"

void fixed2free(lines_t &lines)
{
   unsigned int old_indent          = 0;
   static unsigned int first_indent = 0;
   static char prevquote            = ' ';

   std::vector <fortranline> nlines;
   std::ostringstream os;

   while(!lines.empty())
   {
      //mycout.reset();
      os.str("");
      std::string s   = lines.front().line();
      if(lines.front().blank_or_comment())
      {
	 //
	 // this is an empty line or comment line
	 //
	 if (firstchar(lines.front().orig()) == '!')                   // do not change lines starting with !
	 {
	    //mycout << lines.front().rtrim() << endline;
	    os << lines.front().rtrim();
	    nlines.push_back(os.str());
	 }
	 else if ( lines.front().firstchar() == "!")             // indent indented comments
	 {
	    //mycout << std::string(6+cur_indent,' ') << trim(s) << endline;
	    os << std::string(6+cur_indent,' ') << trim(s);
	    nlines.push_back(os.str());
	 }
	 else
	 {
	    //mycout << trim(s) << endline;
	    os << trim(s);
	    nlines.push_back(os.str());
	 }
      }
      else if(!cleanfive(lines.front().orig())) // check for valid label field
	 mycout << lines.front().orig() << endline;  // garbage in, garbage out
      else
      {
	 // mycout << s.substr(0,6);
	 bool iscontinuation;

	 if(s.length() > 6)
	 {
	    iscontinuation = (s[5] != ' ' && s[5] != '0');
	    //
	    // try to honor current indentation
	    // if this is a continuation line, count the number
	    // of spaces after column 6.
	    //
	    if (iscontinuation)
	    {
	       std::string s6 = ltab2sp(s.substr(6))+'x';
	       old_indent = s6.find_first_not_of(' ');
	       s[5] = ' ';
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
		  //mycout << std::string(std::max(adjust_indent+cur_indent,0),' ') << trim(s.substr(6));
		  os << std::string(std::max(adjust_indent+cur_indent,0),' ') << trim(s.substr(6));
		  break;
	       default:  // dangling string, output asis
		  //mycout << s.substr(6);
		  os << s.substr(6);
		  break;
	    }
	    //
	    // investigate if this line terminates a string
	    //
	    prevquote = fixedmissingquote(prevquote + s);
	 }
	 //mycout << endline;

	 nlines.push_back(os.str());
      }
      lines.pop_front();
   }
   //ppp<<"fixfree:"<<nlines<<endchar;
}

void fixed2free1(lines_t &lines)
{
   unsigned int old_indent   = 0;
   static unsigned int first_indent = 0;
   static char prevquote     = ' ';
   static char preprevquote  = ' ';
   std::string  outputline;
   static int lineno = 0;
   std::string needamp = "";

   while(!lines.empty())
   {
      mycout.reset();
      lineno++;
      std::string s  = lines.front().line();
      if(lines.front().blank_or_comment())
      {
	 //
	 // this is an empty line or comment line
	 //
	 if (trim(s) == "")
	    mycout << endline;
	 else
	 {
	    switch (firstchar(lines.front().orig()))
	    {
	       //
	       // special hack for lines starting with 'd' or 'D'
	       //
	       case 'd' : case 'D' :
		  mycout << "!" + rtrim(lines.front().orig()) << endline;
		  break;
	       case 'c': case 'C': case '*': case '!':
		  mycout << '!' << lines.front().rtrim().substr(1) << endline;
		  break;
	       default:  // this must be a ! comment, not starting in column 1
		  mycout << std::string(std::max(cur_indent,1),' ') << lines.front().trim() << endline;
	    }
	 }
      }
      else if(!cleanfive(lines.front().orig())) // check for valid label field
	 mycout << lines.front().orig() << endline;  // garbage in, garbage out
      else
      {
	 //
	 // this must be a line with a (continuation of) a statement
	 //
	 outputline = needamp;
	 if (lineno == 1)
	    //
	    // special action for first line: could have a label
	    //
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
	 // Check for continuation lines by iterating over the rest of 
	 // the lines.
	 // There is a continuation line if there is a non-comment in 
	 // the lines list, in that case a trailing & is needed
	 // and the non-comment line needs a leading &
	 //
	 needamp="";
	 lines_t::iterator it = lines.begin();
	 it++;                                   // start at next line
	 std::string prevlchar = "";
	 bool inpreproc = 0;
	 while(it != lines.end())
	 {
	    //
	    // if previous lastchar was '\\', do not consider this 
	    // line, if we are in a preprocessor statement
	    //
	    if (inpreproc && prevlchar == "\\")
	    {
	       prevlchar = it->lastchar();
	       it++;
	       continue;
	    }
	    prevlchar = it->lastchar();
	    inpreproc = it->precpp();
	    if(!(it++)->blank_or_comment_or_pre())
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
	       work = remove_trailing_comment(work);
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
      lines.pop_front();
   }
}
