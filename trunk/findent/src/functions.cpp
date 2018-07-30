#include <string>
#include <iostream>
#include <sstream>
#include "functions.h"

std::string stoupper(const std::string &s)
{
   std::string sl = s;
   int l     = sl.size();
   for (int i=0; i<l; i++)
      sl[i] = toupper(sl[i]);
   return sl;
}

std::string stolower(const std::string &s)
{
   std::string sl = s;
   int l     = sl.size();
   for (int i=0; i<l; i++)
      sl[i] = tolower(sl[i]);
   return sl;
}

std::string firstchars(const std::string &s, const int n)
{
   size_t l = s.length();
   switch(l)
   {
      case 0:
	 return std::string("");
      case 1:
	 return s.substr(0,1);
      default:
	 return s.substr(0,2);
   }
}

std::string remove_blanks(const std::string &s)
{
   std::string sl = "";
   size_t l = s.length();
   for (size_t i=0; i<l; i++)
   {
      switch (s[i])
      {
	 case ' ':
	 case '\t':
	    break;
	 default:
	    sl = sl + s[i];
      }
   }
   return sl;
}

char firstchar(const std::string &s)
{
   size_t l = s.length();
   if (l == 0)
      return 0;
   return s[0];
}

char lastchar(const std::string &s)
{
   size_t l = s.length();
   if (l == 0)
      return 0;
   return s[l-1];
}


std::string rtrim(const std::string &str)
{
   const std::string whitespace = " \t";

   const size_t strEnd = str.find_last_not_of(whitespace);
   if (strEnd == std::string::npos)
      return ""; // no content
   return str.substr(0,strEnd+1);
}

std::string ltrim(const std::string &str)
{
   const std::string whitespace = " \t";
   const size_t strBegin = str.find_first_not_of(whitespace);
   if (strBegin == std::string::npos)
      return ""; // no content

   return str.substr(strBegin);
}

std::string trim(const std::string &str)
{
   const std::string whitespace = " \t";
   const size_t strBegin = str.find_first_not_of(whitespace);
   if (strBegin == std::string::npos)
      return ""; // no content

   const size_t strEnd = str.find_last_not_of(whitespace);
   const size_t strRange = strEnd - strBegin + 1;

   return str.substr(strBegin, strRange);
}

bool cleanfive(const std::string &s)
   //
   // returns 1, if columns 1-5 contain only [0-9 \t]
   // else returns 0
   //
{
   int l = std::min((int)s.size(), 5);
   for (int i=0; i<l; i++)
   {
      char c = s[i];
      if (c == '\t')
	 return 1;
      if (c == ' ' || (c >='0' && c <='9'))
	 continue;
      return 0;
   }
   return 1;
}

bool isalnumplus(const char c)
   //
   // returns true if c is alfanum or in " \t_"
   //
{
   if (std::isalnum(c))
      return 1;
   else 
      switch (c)
      {
	 case ' ':
	 case '\t':
	 case '_':
	    return 1;
      }
   return 0;
}

bool isfixedcmtp(const std::string &s)
{
   //
   // returns 1 if this is a fixed empty line or fixed comment line or preprocessor line
   //                                         or debug line ('d' or 'D' in column 1)
   //
   if (s == "" || trim(s) == "")
      return 1;
   char c = firstchar(s);
   char cts = firstchar(trim(s));
   return (cts == 0 || c == 'C' || c == 'c' || cts == '!' || c == '*' || cts == '#' || c == 'd' || c == 'D' || firstchars(trim(s),2) == "??"); 
}

int num_leading_spaces(const std::string &s)
{
   size_t p = s.find_first_not_of(' ');
   if (p == std::string::npos)
      return s.size();
   return p;
}

char fixedmissingquote(const std::string &s)
{
   //
   // investigate if this line terminates a string
   // returns ' ' if there is no unterminated string
   // returns '"' if this is an unterminated string, a '"' is missing
   // returns '\'' if this is an unterminated string, a '\'' is missing
   //
   bool instring = 0;
   char q = ' ';
   for(unsigned int i=0; i<s.size(); i++)
   {
      if (instring)
      {
	 if (s[i] == q)
	    instring = 0;
      }
      else
      {
	 switch(s[i])
	 {
	    case '"': case '\'':
	       instring = 1;
	       q = s[i];
	 }
      }
   }
   if (instring)
      return q;
   return ' ';
}

std::string ltab2sp(const std::string &s)
{
   //
   // converts leading white space and white space after a statement label
   //   to spaces and removes trailing white space
   // if line starts with 0-5 spaces or digits followed by a tab, followed
   //   by 1-9, this is counted as 5 spaces, it appears that many compilers
   //   assume that 
   //   <tab>1  <some code>
   //   is a continuation statement, if the continuation character is 1-9
   //   If the character is not within 1-9, it is assumed that 
   //   this character is the first of a statement, so in this case
   //   this is counted as 6 spaces
   //

   int         si       = 0;
   bool        ready    = 0;
   const int   tabl     = 6;
   bool        firsttab = 1;
   std::string leader   = "";
   int         removed  = 0;

   for (unsigned int j=0; j<s.length(); j++)
   {
      switch (s[j])
      {
	 case ' ' :
	    si ++;
	    removed++;
	    leader = leader + " ";
	    break;
	 case '\t' :
	    if (firsttab)
	    {
	       firsttab = 0;
	       if (si < 6)
		  //
		  // investigate next char: if 1-9, count this tab as 5 spaces
		  //
		  if (s.length() > j+1)
		     if (s[j+1] >= '1' && s[j+1] <= '9')
		     {
			si = 5;
			removed++;
			leader = std::string(5,' ');
			break;
		     }
	    }
	    si = (si/tabl)*tabl + tabl;
	    leader = leader + std::string(si - leader.length(),' ');
	    break;
	 case '0': case '1': case '2': case '3': case '4':
	 case '5': case '6': case '7': case '8': case '9':
	    si++;
	    removed++;
	    leader += s[j];
	    firsttab = 0;
	    break;
	 default:
	    ready = 1;
	    break;
      }
      if(ready)
	 break;
   }
   return leader + trim(s.substr(removed));
}

std::string remove_trailing_comment(const std::string &s)
{
   //
   // removes trailing comment, but only if not part of an
   // unterminated string.
   // e.g:
   // 'print *, " Hi! and goodbye'
   // becomes:
   // 'print *, " Hi! and goodbye'
   // but
   // 'print *, " Hi! and goodbye" ! say goodbye'
   // becomes
   // 'print *, " Hi! and goodbye" '
   //

   std::string so = s;
   bool instring = 0;
   char q        = ' ';
   for (unsigned int i=0; i<so.size(); i++)
   {
      if (instring)
      {
	 if(so[i] == q)
	    instring = 0;
      }
      else
      {
	 switch(so[i])
	 {
	    case '"': case '\'':
	       instring = 1;
	       q = so[i];
	       break;
	    case '!':
	       so.erase(i,std::string::npos);
	       return so;
	 }
      }
   }
   return so;
}              // end of remove_trailing_comment

