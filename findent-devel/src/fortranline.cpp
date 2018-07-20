#include "fortranline.h"
int fortranline::format;
int fortranline::line_length;
bool fortranline::gnu_format;
void fortranline::print()
{
   std::cout << "format:" << format2txt() << std::endl;
   std::cout << "orig_line: [" << orig_line << "]" << std::endl;
   if(have_trim)
      std::cout << "trim_line: [" << trim_line << "]" << std::endl;
   if(have_ltrim)
      std::cout << "ltrim_line: [" << ltrim_line << "]" << std::endl;
   if(have_rtrim)
      std::cout << "rtrim_line: [" << rtrim_line << "]" << std::endl;
   if(have_first)
      std::cout << "firstchar: [" << first << "]" << std::endl;
   if(have_last)
      std::cout << "lastchar: [" << last << "]" << std::endl;
   if(have_first2)
      std::cout << "first2chars: [" << first2 << "]" << std::endl;
   if(have_ltab2sp)
      std::cout << "ltab2sp: [" << ltab2sp_line << "]" << std::endl;
   if(have_scanfixpre)
      std::cout << "scanfixpre: " << Scanfixpre << std::endl;
}

