#ifndef NFORTRANLINE_H
#define NFORTRANLINE_H
#include <string>
class Fortranline
{
   public:

   Fortranline()
   {
      format = g_format;
      line = "fortranline";
   }
   Fortranline(const std::string &s)
   {
      format = g_format;
      line = s;
   }
   std::string str()
   {
      return line;
   }
   int g_format;
   int format;
   std::string line;
};
#endif
