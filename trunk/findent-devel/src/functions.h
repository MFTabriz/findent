#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include <iostream>
#include <sstream>

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

std::string stoupper(const std::string s);
std::string stolower(const std::string s);
std::string firstchars(const std::string s, const int n);
std::string remove_blanks(const std::string s);
int         ppp(const std::string s);
char        firstchar(const std::string s);
bool        isalnumplus(const char c);
char        lastchar(const std::string s);
std::string trim(const std::string& str);
std::string rtrim(const std::string& str);
std::string ltrim(const std::string& str);

bool        cleanfive(const std::string s);
int         num_leading_spaces(const std::string &s);
bool        isfixedcmtp(const std::string s);
char        fixedmissingquote(const std::string s);
std::string ltab2sp(const std::string& s);
#endif
