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
   return (cts == 0 || c == 'C' || c == 'c' || cts == '!' || c == '*' \
	 || cts == '#' || c == 'd' || c == 'D' || firstchars(trim(s),2) == "??"); 
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

   const std::string d1_9  =  "123456789";
   const std::string db0_9 = " 0123456789";
   size_t p = s.substr(0,6).find_first_of('\t');
   if (p == std::string::npos)
      return rtrim(s);                  // no tab in first 6 columns

   if (s.find_first_not_of(db0_9) == p) //  all space or numeric before tab? 
   {
      if (s.length() == p+1)                                   // ' 100 T'  ->' 100', ' T'-> ''
	 return rtrim(s.substr(0,p));
      if (d1_9.find(s[p+1]) == std::string::npos)              // ' 10 Tx'  -> ' 10   x'
	 return rtrim(s.substr(0,p)+blanks(6-p)+s.substr(p+1));
      return    rtrim(s.substr(0,p)+blanks(5-p)+s.substr(p+1));// ' 10 T1x' -> ' 10  1x'
   }
   else
      return rtrim(s);
}

std::string remove_trailing_comment(const std::string &s,const char prevquote)
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
   bool instring = prevquote != ' ';
   char q        = prevquote;
   for (unsigned int i=0; i<s.size(); i++)
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
