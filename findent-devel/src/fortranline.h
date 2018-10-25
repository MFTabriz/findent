#ifndef FORTRANLINE_H
#define FORTRANLINE_H

#include <deque>

#include "functions.h"
#include "lexer.h"
#include "parser.h"
#include "globals.h"
#include "debug.h"

class Fortranline
{
   //
   // NOTE:
   // some functions assume that clean() is called
   //
   std::string orig_line;
   std::string orig_without_omp;
   //
   // Some functions are used repeatedly, the results are
   // cached here
   //
   char        firstchar_cache;    bool firstchar_cached;
   std::string ltrim_cache;        bool ltrim_cached;
   bool        omp_cache;          bool omp_cached;
   int         scanfixpre_cache;   bool scanfixpre_cached;
   std::string trim_cache;         bool trim_cached;

   bool     is_clean;
   Globals* gl;
   int      local_format;
   bool     local_gnu_format;


   void init()
   {
      local_format      = gl->global_format;
      local_gnu_format  = gl->global_gnu_format;

      is_clean          = 0;

      firstchar_cached  = 0;
      ltrim_cached      = 0;
      omp_cached        = 0;
      scanfixpre_cached = 0;
      trim_cached       = 0;
   }

   void init(Globals* g)
   {
      gl = g;
      init();
   }

   void do_clean();
   bool do_omp();

   public:

   void print();

   void clean()
   {
      if (is_clean)
	 return;
      else
	 do_clean();
   }

   void clean(bool force)
   {
      if (force)
	 do_clean();
      else
	 clean();
   }

   Fortranline(Globals* g)
   {
      init(g);
   }

   Fortranline(Globals*g, const std::string &s)
   {
      init(g);
      orig_line = s;
   }

   std::string g_format2txt()
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

   void g_format(const int what)    { gl->global_format = what; }

   int g_format()                   { return gl->global_format; }

   void line_length(const int what) { gl->global_line_length=what; }

   int line_length()                { return gl->global_line_length; }

   void gnu_format(bool what)       { gl->global_gnu_format=what; }

   bool gnu_format()                { return gl->global_gnu_format; }

   std::string str()                { return orig_line; }

   std::string strnomp()      
   {
      clean();
      return orig_without_omp; 
   }

   friend std::ostream& operator <<(std::ostream &os,Fortranline &obj);

   void str(const std::string &s)
   {
      orig_line = s;
      init();
   }

   int format() const
   {
      if (local_format == UNKNOWN)
	 return gl->global_format;
      return local_format;
   }


   std::string trimmed_line()
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
	    if (omp())
	       return ::trim(orig_without_omp);
	    else
	       return ::trim(orig_line);
	    break;
      }
   }

   std::string rtrim() 
   {
      if (omp())
	 return ::rtrim(orig_without_omp);
      else
	 return ::rtrim(orig_line);
   }

   std::string ltrim()
   {
      if (!ltrim_cached)
      {
	 if (omp())
	    ltrim_cache = ::ltrim(orig_without_omp);
	 else
	    ltrim_cache = ::ltrim(orig_line);
	 ltrim_cached = 1;
      }
      return ltrim_cache;
   }

   std::string trim() 
   {
      if (!trim_cached)
      {
	 if (omp())
	    trim_cache = ::trim(orig_without_omp);
	 else
	    trim_cache = ::trim(orig_line);
	 trim_cached = 1;
      }
      return trim_cache;
   }

   char firstchar() 
   {
      // returns first char of ltrim(), 0 if length()=0
      if (!firstchar_cached)
      {
	 if (ltrim().length()>0)
	    firstchar_cache = ltrim()[0];
	 else
	    firstchar_cache = 0;
	 firstchar_cached = 1;
      }
      return firstchar_cache;
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
      if (orig_line.length() > 0)
	 return *orig_line.rbegin();
      else
	 return 0;
   }

   std::string first2chars() { return ltrim().substr(0,2); }

   int scanfixpre()
   {
      if(!scanfixpre_cached)
      {
	 lexer_set(trim(),SCANFIXPRE);
	 scanfixpre_cache = yylex();
	 if (format() == FIXED)
	    if(scanfixpre_cache == FIXFINDENTFIX)
	       scanfixpre_cache = FINDENTFIX;
	 scanfixpre_cached = 1;
      }
      return scanfixpre_cache;
   }

   bool omp()
   {
      if (!omp_cached)
      {
	 omp_cache = do_omp();
	 omp_cached = 1;
      }
      return omp_cache;
   }

   std::string rest() 
   {
      if(scanfixpre()==FINDENTFIX)
	 return lexer_getrest();
      else
	 return "";
   }

   bool blank() { return (trim().length() == 0); }

   bool comment() 
   {
      switch (format())
      {
	 case FIXED:
	    if (omp())
	    {
	       return firstchar() == '!';
	    }
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

   bool blank_or_comment() { return blank() || comment(); }

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
	 case INCLUDE_CPP: case INCLUDE_CPP_STD: case INCLUDE_COCO:
	    return pretype;
	    break;
	 default:
	    return 0;
      }
   }

   bool precpp() { return firstchar() == '#'; }

   bool precoco() { return first2chars() == "??"; }

   bool pre() { return precpp() || precoco(); }

   bool blank_or_comment_or_pre() { return blank_or_comment() || pre(); }

   bool fortran() { return !blank_or_comment_or_pre(); }

   bool fixedcontinuation() const
   {
      //
      // returns 1 if the line, interpreted as a fixed format line,
      // contains a character other than 0 or ' ' in column 5
      //
      const std::string c = " 0";
      return c.find((*this)[5]) == std::string::npos;
   }

   std::string remove_trailing_comment(const char prevquote = ' ')
   {
      return ::rtrim(::remove_trailing_comment(orig_without_omp,prevquote));
   }

};

std::ostream& operator <<(std::ostream &os,Fortranline &obj);

typedef std::deque<Fortranline> lines_t;

typedef std::deque<Fortranline> linebuffer_t;

#endif
