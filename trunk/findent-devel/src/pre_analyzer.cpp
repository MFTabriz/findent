#include <string>
#include "pre_analyzer.h"
#include "functions.h"
//
// if start of s ==
// #\s*if
// or
// #\s*elif
// or
// #\s*else
// or
// #\s*endif
//
// then the function returns
// IF_pre:  an #if is found
// ELIF_pre:  an #elif is found
// ELSE_pre:  an #else is found
// ENDIF_pre:  an #endif is found, without preceding #else
// ENDIFE_pre:  an #endif is found, with preceding #else
//
// if start of s ==
// ??\s*if
// or
// ??\s*else if
// or
// ??\s*else
// or
// ??\s*endif
//
// (all case and space independent)
//
// then the function returns
// IF_pre:     '??if'  found
// ELIF_pre:   '??else if'  found
// ELSE_pre:   '??else'  found
// ENDIF_pre:  '??endif'  found, without preceding '#else' or '??else'
// ENDIFE_pre: '??endif'  found, with preceding '#else' or '??else'
//
// The funcion returns NONE_pre if none of above is found.
//
int pre_analyzer::analyze(const std::string s)
{
   bool iscoco = (firstchars(s,2) == "??");
   if (s.size() <3 || (s[0] != '#' && !iscoco))
      return this->NONE_pre;

   int k;
   if (iscoco)
      k=2;
   else
      k=1;
   const size_t strBegin = k + s.substr(k).find_first_not_of(" \t");

   if (strBegin == std::string::npos)
      return this->NONE_pre;

   std::string sl = s.substr(strBegin);
   if (iscoco)
   {
      sl = stolower(remove_blanks(sl));
   }

   if (sl.find("if") == 0)
   {
      this->ifelse_stack.push(0);
      return pre_analyzer::IF_pre;
   }
   else if (!iscoco && sl.find("elif") == 0)
   {
      return pre_analyzer::ELIF_pre;
   }
   else if (iscoco && sl.find("elseif") == 0)
   {
      return pre_analyzer::ELIF_pre;
   }
   else if (sl.find("else") == 0)
   {
      if (!this->ifelse_stack.empty())
      {
	 ifelse_stack.pop();
	 ifelse_stack.push(1);
      }
      return pre_analyzer::ELSE_pre;
   }
   else if (sl.find("endif") == 0)
   {
      int r = pre_analyzer::ENDIF_pre; 
      if (!ifelse_stack.empty())
      {
	 if (ifelse_stack.top())
	    r = pre_analyzer::ENDIFE_pre;
	 ifelse_stack.pop();
      }
      return r;
   }
   else
      return pre_analyzer::NONE_pre;
}
