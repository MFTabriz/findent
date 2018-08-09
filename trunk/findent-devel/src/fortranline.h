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

   static int format, line_length;
   static bool gnu_format;

   bool iscontinuation;

   public:

   void init()
   {
      iscontinuation = 0;
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
   std::string orig() const
   {
      return orig_line;
   }

   friend std::ostream& operator <<(std::ostream &os,fortranline &obj);

   void set_line(const std::string &s)
   {
      orig_line = s;
   }

   std::string line() const
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

   std::string trimmed_line() const
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

   std::string rtrim() const
   {
      return ::rtrim(orig());
   }

   std::string ltrim() const
   {
      return ::ltrim(orig());
   }

   std::string trim() const
   {
      return ::trim(orig());
   }

   std::string firstchar() const
   {
      // returns first char of ltrim()
      return ltrim().substr(0,1);
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
      return ::ltab2sp(orig());
   }


   int scanfixpre() const
   {
      int rc;
      lexer_set(trim(),SCANFIXPRE);
      rc      = yylex();
      if (format == FIXED)
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

   void set_con(const bool b)
   {
      iscontinuation = b;
   }

   bool con() const
   {
      return iscontinuation;
   }

   bool fortran() const
   {
      return !blank_or_comment_or_pre();
   }

};
std::ostream& operator <<(std::ostream &os,fortranline &obj);
#endif
