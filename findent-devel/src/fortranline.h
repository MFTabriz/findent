#ifndef FORTRANLINE_H
#define FORTRANLINE_H
#include <iostream>
#include <string>
#include "functions.h"
#include "parser.h"
#include "lexer.h"

class fortranline
{

   // NOTE:
   // some functions assume that clean() is called
   //
   std::string orig_line;
   //
   // I found that some functions are used repeatedly, the results are
   // cached here
   //
   std::string ltrim_line; bool have_ltrim_line;
   std::string trim_line;  bool have_trim_line;
   char firstchar_val;     bool have_firstchar_val;

   static int global_format, global_line_length;
   static bool global_gnu_format;

   int  local_format;
   bool local_gnu_format;
   bool is_clean;


   void init()
   {
      local_format        = global_format;
      local_gnu_format    = global_gnu_format;
      have_ltrim_line     = 0;
      have_trim_line      = 0;
      have_firstchar_val  = 0;
      is_clean            = 0;
   }

   public:

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
      init();
      orig_line = s;
   }

   int format() const
   {
      if (local_format == UNKNOWN)
	 return global_format;
      return local_format;
   }

   void clean()
   {
      if(is_clean)  // with fixed-format, lines are often read twice
	 return;
      init();
      switch(format())
      {
	 case FIXED:
	    if (line_length() == 0)
	       orig_line = ltab2sp(orig_line);
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
		  orig_line = ltab2sp(orig_line).substr(0,line_length());
	       else
		  orig_line = ::rtrim(orig_line.substr(0,line_length()));
	    break;
	 case FREE:
	 default:
	    if (line_length() == 0)
	       orig_line = ::rtrim(orig_line);
	    else
	       orig_line = ::rtrim(orig_line.substr(0,line_length()));
	    break;
      }
      is_clean = 1;
   }

   std::string trimmed_line() const
   {
      //
      // result is different for FIXED or FREE, see below:
      //
      switch(format())
      {
	 case FIXED:
	    return ::rtrim(orig_line);
	    break;
	 case FREE:
	 default:
	    return ::trim(orig_line);
	    break;
      }
   }

   std::string rtrim() const
   {
      return ::rtrim(orig_line);
   }

   std::string ltrim()
   {
      if (!have_ltrim_line)
      {
	 ltrim_line = ::ltrim(orig_line);
	 have_ltrim_line = 1;
      }
      return ltrim_line;
   }

   std::string trim() 
   {
      if (!have_trim_line)
      {
	 trim_line = ::trim(orig_line);
	 have_trim_line = 1;
      }
      return trim_line;
   }

   char firstchar() 
   {
      // returns first char of ltrim(), 0 if length()=0
      if (!have_firstchar_val)
      {
	 firstchar_val = *(ltrim().begin());
	 have_firstchar_val = 1;
      }
      return firstchar_val;
   }

   char operator [] (int i) const
   {
      //returns character in column k of the original line
      if(orig_line.length() > (unsigned) i)
	 return orig_line[i];
      else
	 return 0;
   }

   char lastchar() const
   {
      return *orig_line.rbegin();
   }

   std::string first2chars() 
   {
      return ltrim().substr(0,2);
   }

   int scanfixpre()
   {
      int rc;
      lexer_set(trim(),SCANFIXPRE);
      rc      = yylex();
      if (format() == FIXED)
	 if(rc == FIXFINDENTFIX)
	    rc = FINDENTFIX;
      return rc;
   }

   std::string rest() 
   {
      if(scanfixpre()==FINDENTFIX)
	 return lexer_getrest();
      else
	 return "";
   }

   bool blank() 
   {
      return (trim().length() == 0);
   }

   bool comment() 
   {
      switch (format())
      {
	 case FIXED:
	    switch(::firstchar(orig_line))
	    {
	       case 'd':
	       case 'D':
	       case 'c':
	       case 'C':
	       case '!':
	       case '*':
		  return 1;
	    }
	    return firstchar() == '!';
	    break;

	 case FREE:
	    return firstchar() == '!';
	    break;
      }
      return 0;
   }

   bool blank_or_comment() 
   {
      return blank() || comment();
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
      return firstchar() == '#';
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

   bool fortran() 
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
