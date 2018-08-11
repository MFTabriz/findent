#ifndef FORTRANLINE_H
#define FORTRANLINE_H
#include <iostream>
#include <string>
#include "functions.h"
#include "parser.h"
#include "lexer.h"

class fortranline
{

   std::string orig_line;

   static int global_format, global_line_length;
   static bool global_gnu_format;

   bool iscontinuation;
   bool hascontinuation;
   int  local_format;
   bool local_gnu_format;

   public:

   void init()
   {
      iscontinuation   = 0;
      hascontinuation  = 0;
      local_format     = global_format;
      local_gnu_format = global_gnu_format;
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

   static std::string g_format2txt()
   {
      switch(g_format())
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

   static void g_format(const int what)
   {
      global_format = what;
   }
   static int g_format()
   {
      return global_format;
   }
   static void line_length(const int what)
   {
      global_line_length = what;
   }
   static int line_length()
   {
      return global_line_length;
   }
   static void gnu_format(bool what)
   {
      global_gnu_format = what;
   }
   static bool gnu_format()
   {
      return global_gnu_format;
   }
   std::string str() const
   {
      return orig_line;
   }

   friend std::ostream& operator <<(std::ostream &os,fortranline &obj);

   void str(const std::string &s)
   {
      orig_line = s;
   }

   int format() const
   {
      if (local_format == UNKNOWN)
	 return global_format;
      return local_format;
   }

   std::string line() const
   {
      switch(global_format)
      {
	 case FIXED:
	    if (line_length() == 0)
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
	       if(gnu_format())
		  return ltab2sp().substr(0,line_length());
	       else
		  return str().substr(0,line_length());
	    break;
	 case FREE:
	    if (line_length() == 0)
	       return str();
	    else
	       return str().substr(0,line_length());
	    break;
	 default:
	    return str().substr(0,line_length());
	    break;
      }
      return "";   // never reached
   }

   std::string trimmed_line() const
   {
      //
      // result is different for FIXED or FREE, see below:
      //
      switch(global_format)
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

   std::string rtrim() const
   {
      return ::rtrim(str());
   }

   std::string ltrim() const
   {
      return ::ltrim(str());
   }

   std::string trim() const
   {
      return ::trim(str());
   }

   std::string firstchar() const
   {
      // returns first k-th char of ltrim()
      return ltrim().substr(0,1);
   }

   std::string col(const unsigned int k = 0) const
   {
      //returns character in column k of the original line
      if(format() == FIXED)
      {
	 std::string s = ltab2sp();
	 if(s.length() > k)
	    return s.substr(k,1);
	 else
	    return "";
      }
      else
      {
	 if(orig_line.length() > k)
	    return orig_line.substr(k,1);
	 else
	    return "";
      }
   }

   char operator [] (int i) const
   {
      //returns character in column k of the original line
      if(format() == FIXED)
      {
	 std::string s = ltab2sp();
	 if(s.length() > (unsigned) i)
	    return s[i];
	 else
	    return 0;
      }
      else
      {
	 if(orig_line.length() > (unsigned) i)
	    return orig_line[i];
	 else
	    return 0;
      }
   }

   std::string lastchar() const
   {
      if (rtrim().length() > 0)
	 return rtrim().substr(rtrim().length()-1);
      else
	 return "";
   }

   std::string first2chars() const
   {
      return ltrim().substr(0,2);
   }

   std::string ltab2sp() const
   {
      return ::ltab2sp(str());
   }


   int scanfixpre() const
   {
      int rc;
      lexer_set(trim(),SCANFIXPRE);
      rc      = yylex();
      if (global_format == FIXED)
	 if(rc == FIXFINDENTFIX)
	    rc = FINDENTFIX;
      return rc;
   }

   std::string rest() const
   {
      if(scanfixpre()==FINDENTFIX)
	 return lexer_getrest();
      else
	 return "";
   }

   bool blank() const
   {
      return (trim().length() == 0);
   }

   bool comment() const
   {
      switch (format())
      {
	 case FIXED:
	    switch(::firstchar(str()))
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

   bool blank_or_comment() const
   {
      return blank() || comment();
   }

   int getpregentype() const
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

   bool precpp() const
   {
      return firstchar() == "#";
   }

   bool precoco() const
   {
      return first2chars() == "??";
   }

   bool pre() const
   {
      return precpp() || precoco();
   }

   bool blank_or_comment_or_pre() const
   {
      return blank_or_comment() || pre();
   }

   void iscon(const bool b)
   {
      iscontinuation = b;
   }

   bool iscon() const
   {
      return iscontinuation;
   }

   void hascon(const bool b)
   {
      hascontinuation = b;
   }

   bool hascon() const
   {
      return hascontinuation;
   }

   bool fortran() const
   {
      return !blank_or_comment_or_pre();
   }

   bool fixedcontinuation() const
   {
      //
      // returns 1 if the line, interpreted as a fixed format line,
      // contains a character other than 0 or ' ' in column 5
      //
      const std::string c = " 0";
      return c.find((*this)[5]) == std::string::npos;
   }

};
std::ostream& operator <<(std::ostream &os,fortranline &obj);
#endif
