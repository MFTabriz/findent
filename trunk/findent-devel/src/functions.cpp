#include <string>
#include <iostream>
#include "functions.h"

std::string stoupper(const std::string s)
{
   std::string sl = s;
   int l     = sl.size();
   for (int i=0; i<l; i++)
      sl[i] = toupper(sl[i]);
   return sl;
}

std::string stolower(const std::string s)
{
   std::string sl = s;
   int l     = sl.size();
   for (int i=0; i<l; i++)
      sl[i] = tolower(sl[i]);
   return sl;
}

std::string firstchars(const std::string s, const int n)
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

std::string remove_blanks(const std::string s)
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

int ppp(const std::string s)     // for ad-hoc debugging purposes
{
   std::cout << "ppp:["+s+"]" << std::endl;
   return 0;
}

char firstchar(const std::string s)
{
   size_t l = s.length();
   if (l == 0)
      return 0;
   return s[0];
}

char lastchar(const std::string s)
{
   size_t l = s.length();
   if (l == 0)
      return 0;
   return s[l-1];
}


std::string rtrim(const std::string& str)
{
   const std::string whitespace = " \t";

   const size_t strEnd = str.find_last_not_of(whitespace);
   if (strEnd == std::string::npos)
      return ""; // no content
   return str.substr(0,strEnd+1);
}

std::string ltrim(const std::string& str)
{
   const std::string whitespace = " \t";
   const size_t strBegin = str.find_first_not_of(whitespace);
   if (strBegin == std::string::npos)
      return ""; // no content

   return str.substr(strBegin);
}

std::string trim(const std::string& str)
{
   const std::string whitespace = " \t";
   const size_t strBegin = str.find_first_not_of(whitespace);
   if (strBegin == std::string::npos)
      return ""; // no content

   const size_t strEnd = str.find_last_not_of(whitespace);
   const size_t strRange = strEnd - strBegin + 1;

   return str.substr(strBegin, strRange);
}

bool cleanfive(const std::string s)
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

bool isfixedcmtp(const std::string s)
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

char fixedmissingquote(const std::string s)
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
