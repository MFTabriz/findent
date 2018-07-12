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
