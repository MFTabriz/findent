#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include <iostream>
#include <sstream>
#include "simpleostream.h"

inline std::string blanks(const size_t x)
{
   return std::string(x,' ');
}

inline std::string ltrim(const std::string &str)
{
   const std::string whitespace = " \t";
   size_t strBegin = str.find_first_not_of(whitespace);
   if (strBegin == std::string::npos)
      return ""; // no content

   return str.substr(strBegin);
}

inline std::string rtrim(const std::string &str)
{
   const std::string whitespace = " \t";

   size_t strEnd = str.find_last_not_of(whitespace);
   if (strEnd == std::string::npos)
      return ""; // no content
   return str.substr(0,strEnd+1);
}

inline std::string trim(const std::string &str)
{
   const std::string whitespace = " \t";
   size_t strBegin = str.find_first_not_of(whitespace);
   if (strBegin == std::string::npos)
      return ""; // no content

   size_t strEnd = str.find_last_not_of(whitespace);
   size_t strRange = strEnd - strBegin + 1;

   return str.substr(strBegin, strRange);
}

inline char firstchar(const std::string &s)
{
   size_t l = s.length();
   if (l == 0)
      return 0;
   return s[0];
}

inline char lastchar(const std::string &s)
{
   size_t l = s.length();
   if (l == 0)
      return 0;
   return s[l-1];
}



extern simpleostream mycout; 

template <typename T>
  std::string number2string ( T number )
  {
    std::ostringstream ss;
    ss << number;
    return ss.str();
  }

template <typename T>
  T string2number ( const std::string &text )
  {
    std::istringstream ss(text);
    T result;
    return ss >> result ? result : 0;
  }

bool        cleanfive(const std::string &s);
std::string firstchars(const std::string &s, const int n);
char        firstchar(const std::string &s);
char        fixedmissingquote(const std::string &s);
bool        isalnumplus(const char c);
bool        isfixedcmtp(const std::string &s);
char        lastchar(const std::string &s);
std::string ltab2sp(const std::string& s);
int         num_leading_spaces(const std::string &s);
std::string remove_blanks(const std::string &s);
std::string remove_trailing_comment(const std::string &s, const char prevquote = ' ');
std::string stolower(const std::string &s);
std::string stoupper(const std::string &s);

#endif
