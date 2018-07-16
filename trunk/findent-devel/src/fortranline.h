#include <iostream>
#include <string>
#include "functions.h"
#include "parser.h"
#include "lexer.h"

class fortranline
{

   std::string trim_line, ltrim_line, rtrim_line, orig_line;
   std::string first, last, first2;
   std::string ltab2sp_line;
   int Scanfixpre;
   bool has_trim, has_ltrim, has_rtrim, has_first, has_first2, has_last;
   bool has_ltab2sp, has_scanfixpre;

   public:

   enum {UNKNOWN=1,FIXED,FREE};

   static int format;

   void init()
   {
      has_trim       = 0;
      has_ltrim      = 0;
      has_rtrim      = 0;
      has_first      = 0;
      has_last       = 0;
      has_first2     = 0;
      has_ltab2sp    = 0;
      has_scanfixpre = 0;

      format      = UNKNOWN;
   }

   void print();

   fortranline()
   {
      init();
   }
   fortranline(const std::string& s)
   {
      init();
      orig_line = s;
   }

   void set_line(const std::string& s)
   {
      init();
      orig_line = s;
   }
   std::string orig()
   {
      return orig_line;
   }
   std::string rtrim()
   {
      if (!has_rtrim)
      {
	 rtrim_line = ::rtrim(orig_line);
	 has_rtrim  = 1;
      }
      return rtrim_line;
   }
   std::string ltrim()
   {
      if (!has_ltrim)
      {
	 ltrim_line = ::ltrim(orig_line);
	 has_ltrim  = 1;
      }
      return ltrim_line;
   }
   std::string trim()
   {
      if (!has_trim)
      {
	 trim_line = ::ltrim(rtrim());
	 has_trim  = 1;
      }
      return trim_line;
   }
   std::string firstchar()
   {
      if (!has_first)
      {
	 if (ltrim().length() > 0)
	    first  = ltrim_line[0];
	 else
	    first = "";
	 has_first  = 1;
      }
      return first;
   }
   std::string lastchar()
   {
      if (!has_last)
      {
	 if (rtrim().length() > 0)
	    last  = rtrim_line[rtrim_line.length()-1];
	 else
	    last = "";
	 has_last  = 1;
      }
      return last;
   }
   std::string first2chars()
   {
      if (!has_first2)
      {
	 if (ltrim().length() > 1)
	    first2  = ltrim_line.substr(0,2);
	 else
	    first2 = "";
	 has_first2  = 1;
      }
      return first2;
   }
   std::string ltab2sp()
   {
      if (!has_ltab2sp)
      {
	 ltab2sp_line = ::ltab2sp(orig_line);
	 has_ltab2sp = 1;
      }
      return ltab2sp_line;
   }

   int scanfixpre()
   {
      if(!has_scanfixpre)
      {
	 lexer_set(trim(),SCANFIXPRE);
	 Scanfixpre = yylex();
	 has_scanfixpre = 1;
      }
      return Scanfixpre;
   }

   static std::string format2txt()
   {
      switch(getformat())
      {
	 case UNKNOWN:
	    return "unknown";
	 case FIXED:
	    return "fixed";
	 case FREE:
	    return "free";
	 default:
	    return "";
      }
   }

   static void setformat(const int what)
   {
      format = what;
   }

   static int getformat()
   {
      return format;
   }
};
