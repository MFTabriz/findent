#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include <iostream>
#include <sstream>
#include "simpleostream.h"

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
std::string ltrim(const std::string& str);
int         num_leading_spaces(const std::string &s);
std::string remove_blanks(const std::string &s);
std::string remove_trailing_comment(const std::string &s);
std::string rtrim(const std::string &str);
std::string trim(const std::string &str);
std::string stolower(const std::string &s);
std::string stoupper(const std::string &s);

#endif
