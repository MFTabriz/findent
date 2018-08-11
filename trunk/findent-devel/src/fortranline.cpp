#include <iostream>

#include "fortranline.h"

int fortranline::global_format;
int fortranline::global_line_length;
bool fortranline::global_gnu_format;
void fortranline::print()
{
   std::cout << "orig_line: ["      << orig_line      << "]" << std::endl;
   std::cout << "trim: ["           << trim()         << "]" << std::endl;
   std::cout << "ltrim: ["          << ltrim()        << "]" << std::endl;
   std::cout << "rtrim: ["          << rtrim()        << "]" << std::endl;
   std::cout << "line: ["           << line()         << "]" << std::endl;
   std::cout << "trimmed_line: ["   << trimmed_line() << "]" << std::endl;
   std::cout << "firstchar: ["      << firstchar()    << "]" << std::endl;
   std::cout << "lastchar: ["       << lastchar()     << "]" << std::endl;
   std::cout << "first2chars: ["    << first2chars()  << "]" << std::endl;
   std::cout << "ltab2sp: ["        << ltab2sp()      << "]" << std::endl;
   std::cout << "scanfixpre: "      << scanfixpre()   <<        std::endl;
   std::cout << "rest: ["           << rest()         << "]" << std::endl;
   std::cout << "global_format:"    << g_format2txt() <<        std::endl;
}

std::ostream& operator <<(std::ostream &os,fortranline &obj)
{
      os<<"["<<obj.str()<<"]";
      return os;
}


