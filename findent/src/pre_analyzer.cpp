#include <string>
#include "pre_analyzer.h"
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
// PRE_IF:  an #if is found
// PRE_ELIF:  an #elif is found
// PRE_ELSE:  an #else is found
// PRE_ENDIF:  an #endif is found, without preceding #else
// PRE_ENDIFE:  an #endif is found, with preceding #else
//
// The funcion returns PRE_NONE if none of above is found.
//
int pre_analyzer::analyze(const std::string s)
{
   if (s.size() <3 || s[0] != '#')
      return this->PRE_NONE;

   const size_t strBegin = 1 + s.substr(1).find_first_not_of(" \t");

   if (strBegin == std::string::npos)
      return this->PRE_NONE;

   std::string sl = s.substr(strBegin);

   if (sl.find("if") == 0)
   {
      this->ifelse_stack.push(0);
      return pre_analyzer::PRE_IF;
   }
   else if (sl.find("elif") == 0)
   {
      return pre_analyzer::PRE_ELIF;
   }
   else if (sl.find("else") == 0)
   {
      if (!this->ifelse_stack.empty())
      {
	 ifelse_stack.pop();
	 ifelse_stack.push(1);
      }
      return pre_analyzer::PRE_ELSE;
   }
   else if (sl.find("endif") == 0)
   {
      int r = pre_analyzer::PRE_ENDIF; 
      if (!ifelse_stack.empty())
	 if (ifelse_stack.top())
	    r = pre_analyzer::PRE_ENDIFE;
	 ifelse_stack.pop();
      return r;
   }
   else
      return pre_analyzer::PRE_NONE;
}
