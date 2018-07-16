#include "Fortranline.h"
int Fortranline::format;
void Fortranline::print()
{
   std::cout << "format:" << format2txt() << std::endl;
   std::cout << "orig_line: [" << orig_line << "]" << std::endl;
   if(has_trim)
      std::cout << "trim_line: [" << trim_line << "]" << std::endl;
   if(has_ltrim)
      std::cout << "ltrim_line: [" << ltrim_line << "]" << std::endl;
   if(has_rtrim)
      std::cout << "rtrim_line: [" << rtrim_line << "]" << std::endl;
   if(has_first)
      std::cout << "firstchar: [" << first << "]" << std::endl;
   if(has_last)
      std::cout << "lastchar: [" << last << "]" << std::endl;
   if(has_first2)
      std::cout << "first2chars: [" << first2 << "]" << std::endl;
   if(has_ltab2sp)
      std::cout << "ltab2sp: [" << ltab2sp_line << "]" << std::endl;
   if(has_scanfixpre)
      std::cout << "scanfixpre: " << Scanfixpre << std::endl;
}

