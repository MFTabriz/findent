#ifndef FORTRANLINE_H
#define FORTRANLINE_H
#include <iostream>
#include <string>
#include "functions.h"
#include "parser.h"
#include "lexer.h"

//
// USE_CACHE:
// if #defined ( CXXFLAGS='-DUSE_CACHE' ./configure ) all results are
// cached, hoping this would speed up the program. However, it turns out
// that the effect is only 1%, so by default: no cacheing
//
class fortranline
{

   std::string orig_line;
#ifdef USE_CACHE
   std::string trim_line, ltrim_line, rtrim_line,chopped_line;
   std::string first, last, first2;
   std::string ltab2sp_line, Rest, Trimmed_line;

   int Scanfixpre;

   bool have_trim, have_ltrim, have_rtrim, have_first, have_first2, have_last;
   bool have_ltab2sp, have_scanfixpre, have_chopped_line, have_trimmed_line;
#endif

   static int format, line_length;
   static bool gnu_format;

   public:

   void init()
   {
#ifdef USE_CACHE
      have_chopped_line     = 0;
      have_first            = 0;
      have_first2           = 0;
      have_last             = 0;
      have_ltab2sp          = 0;
      have_ltrim            = 0;
      have_rtrim            = 0;
      have_scanfixpre       = 0;
      have_trim             = 0;
      have_trimmed_line     = 0;
#endif
   }

   void print();

   fortranline()
   {
      init();
   }

   fortranline(const std::string &s)
   {
      init();
      orig_line = s;
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
   static void setline_length(const int what)
   {
      line_length = what;
   }
   static int getline_length()
   {
      return line_length;
   }
   static void setgnu_format(bool what)
   {
      gnu_format = what;
   }
   static bool getgnu_format()
   {
      return gnu_format;
   }
   std::string orig()
   {
      return orig_line;
   }

#ifdef USE_CACHE
   void set_line(const std::string &s)
   {
      init();
      orig_line = s;
   }
#else
   void set_line(const std::string &s)
   {
      orig_line = s;
   }
#endif

#ifdef USE_CACHE

   std::string line()
   {
      if(have_chopped_line)
	 return chopped_line;

      switch(format)
      {
	 case FIXED:
	    if (line_length == 0)
	       chopped_line = ltab2sp();
	    else
	       //
	       // With tabbed input there is a difference between
	       // gfortran and other compilers with respect to the line length.
	       // Other compilers simply count the number of characters.
	       // gfortran always assumes that the
	       // continuation character is in column 6,
	       // so this needs extra attention:
	       //
	       if(getgnu_format())
		  chopped_line = ltab2sp().substr(0,line_length);
	       else
		  chopped_line = orig().substr(0,line_length);
	    have_chopped_line = 1;
	    break;
	 case FREE:
	    if (line_length == 0)
	       chopped_line = orig();
	    else
	       chopped_line = orig().substr(0,line_length);
	    break;
	 default:
	    return orig().substr(0,line_length);
	    break;
	    have_chopped_line = 1;
      }
      return chopped_line;
   }
#else
   std::string line()
   {
      switch(format)
      {
	 case FIXED:
	    if (line_length == 0)
	       return ltab2sp();
	    else
	       //
	       // With tabbed input there is a difference between
	       // gfortran and other compilers with respect to the line length.
	       // Other compilers simply count the number of characters.
	       // gfortran always assumes that the
	       // continuation character is in column 6,
	       // so this needs extra attention:
	       //
	       if(getgnu_format())
		  return ltab2sp().substr(0,line_length);
	       else
		  return orig().substr(0,line_length);
	    break;
	 case FREE:
	    if (line_length == 0)
	       return orig();
	    else
	       return orig().substr(0,line_length);
	    break;
	 default:
	    return orig().substr(0,line_length);
	    break;
      }
   }
#endif

#ifdef USE_CACHE

   std::string trimmed_line()
   {
      //
      // result is different for FIXED or FREE, see below:
      //
      if (!have_trimmed_line)
      {
	 switch(format)
	 {
	    case FIXED:
	       Trimmed_line = ::rtrim(line());
	       have_trimmed_line = 1;
	       break;
	    case FREE:
	    default:
	       Trimmed_line = ::trim(line());
	       have_trimmed_line = 1;
	       break;
	 }
      }
      return Trimmed_line;
   }
#else
   std::string trimmed_line()
   {
      //
      // result is different for FIXED or FREE, see below:
      //
      switch(format)
      {
	 case FIXED:
	    return ::rtrim(line());
	    break;
	 case FREE:
	 default:
	    return ::trim(line());
	    break;
      }
   }

#endif

#ifdef USE_CACHE
   std::string rtrim()
   {
      if (!have_rtrim)
      {
	 rtrim_line = ::rtrim(orig());
	 have_rtrim  = 1;
      }
      return rtrim_line;
   }
#else
   std::string rtrim()
   {
      return ::rtrim(orig());
   }
#endif

#ifdef USE_CACHE
   std::string ltrim()
   {
      if (!have_ltrim)
      {
	 ltrim_line = ::ltrim(orig());
	 have_ltrim  = 1;
      }
      return ltrim_line;
   }
#else
   std::string ltrim()
   {
      return ::ltrim(orig());
   }
#endif

#ifdef USE_CACHE
   std::string trim()
   {
      if (!have_trim)
      {
	 trim_line = ::ltrim(rtrim());
	 have_trim  = 1;
      }
      return trim_line;
   }
#else
   std::string trim()
   {
      return ::trim(orig());
   }
#endif

#ifdef USE_CACHE
   std::string firstchar()
   {
      // returns first char of ltrim()
      if (!have_first)
      {
	 first = ltrim().substr(0,1);
	 have_first = 1;
      }
      return first;
   }
#else
   std::string firstchar()
   {
      // returns first char of ltrim()
      return ltrim().substr(0,1);
   }
#endif

#ifdef USE_CACHE
   std::string lastchar()
   {
      if (!have_last)
      {
	 if (rtrim().length() > 0)
	    last = rtrim().substr(rtrim().length()-1);
	 else
	    last = "";
	 have_last  = 1;
      }
      return last;
   }
#else
   std::string lastchar()
   {
      if (rtrim().length() > 0)
	 return rtrim().substr(rtrim().length()-1);
      else
	 return "";
   }
#endif

#ifdef USE_CACHE
   std::string first2chars()
   {
      if (!have_first2)
      {
	 first2  = ltrim().substr(0,2);
	 have_first2  = 1;
      }
      return first2;
   }
#else
   std::string first2chars()
   {
      return ltrim().substr(0,2);
   }
#endif

#ifdef USE_CACHE
   std::string ltab2sp()
   {
      if (!have_ltab2sp)
      {
	 ltab2sp_line = ::ltab2sp(orig());
	 have_ltab2sp = 1;
      }
      return ltab2sp_line;
   }
#else
   std::string ltab2sp()
   {
      return ::ltab2sp(orig());
   }

#endif

#ifdef USE_CACHE

   int scanfixpre()
   {
      if(!have_scanfixpre)
      {
	 lexer_set(trim(),SCANFIXPRE);
	 Scanfixpre      = yylex();
	 switch(Scanfixpre)
	 {
	    case FINDENTFIX:
	    case FIXFINDENTFIX:
	       Rest = lexer_getrest();
	 }
	 have_scanfixpre = 1;
      }
      if (format == FIXED)
	 if(Scanfixpre == FIXFINDENTFIX)
	    Scanfixpre = FINDENTFIX;
      return Scanfixpre;
   }
#else
   int scanfixpre()
   {
      int rc;
      lexer_set(trim(),SCANFIXPRE);
      rc      = yylex();
      if (format == FIXED)
	 if(rc == FIXFINDENTFIX)
	    rc = FINDENTFIX;
      return rc;
   }
#endif

#ifdef USE_CACHE
   std::string rest()
   {
      if(scanfixpre()==FINDENTFIX)
	 return Rest;
      else
	 return "";
   }
#else
   std::string rest()
   {
      if(scanfixpre()==FINDENTFIX)
	 return lexer_getrest();
      else
	 return "";
   }
#endif

   bool blank_or_comment()
   {
      if (trim() == "")
	 return 1;

      switch (getformat())
      {
	 case FIXED:
	    switch(::firstchar(orig()))
	    {
	       case 'd':
	       case 'D':
	       case 'c':
	       case 'C':
	       case '!':
	       case '*':
		  return 1;
	    }
	    return firstchar() == "!";
	    break;

	 case FREE:
	    return firstchar() == "!";
	    break;
      }
      return 0;
   }

   int getpregentype()
   {
      int  pretype = scanfixpre();
	 switch(pretype)
	 {
	    case CPP_IF: case CPP_ENDIF: case CPP_ELSE: case CPP_ELIF: case CPP: 
	       return CPP;
	       break;
	    case COCO_IF: case COCO_ENDIF: case COCO_ELSE: case COCO_ELIF: case COCO: 
	       return COCO;
	       break;
	    default:
	       return 0;
	 }
   }

   bool precpp()
   {
      return firstchar() == "#";
   }

   bool precoco()
   {
      return first2chars() == "??";
   }

   bool pre()
   {
      return precpp() || precoco();
   }

   bool blank_or_comment_or_pre()
   {
      return blank_or_comment() || pre();
   }

};
#endif
