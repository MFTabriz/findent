#ifndef NFORTRANLINE_H
#define NFORTRANLINE_H

#include <deque>

#include "functions.h"
#include "lexer.h"
#include "parser.h"
#include "globals.h"

class Fortranline
{
   //
   // NOTE:
   // some functions assume that clean() is called
   //
   std::string orig_line;
   //
   // I found that some functions are used repeatedly, the results are
   // cached here
   //
   std::string ltrim_cache; bool ltrim_cached;
   std::string trim_cache;  bool trim_cached;
   char firstchar_cache;    bool firstchar_cached;
   int scanfixpre_cache;    bool scanfixpre_cached;

   bool     is_clean;
   Globals* gl;
   int      local_format;
   bool     local_gnu_format;

   void init()
   {
      local_format      = gl->global_format;
      local_gnu_format  = gl->global_gnu_format;
      ltrim_cached      = 0;
      trim_cached       = 0;
      firstchar_cached  = 0;
      is_clean          = 0;
      scanfixpre_cached = 0;
   }

   void init(Globals* g)
   {
      gl = g;
      init();
   }

   public:

   void print();

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

   std::string str() const          { return orig_line; }

   friend std::ostream& operator <<(std::ostream &os,Fortranline &obj);

   void str(const std::string &s)
   {
      init();
      orig_line = s;
   }

   int format() const
   {
      if (local_format == UNKNOWN)
	 return gl->global_format;
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

   std::string rtrim() const { return ::rtrim(orig_line); }

   std::string ltrim()
   {
      if (!ltrim_cached)
      {
	 ltrim_cache = ::ltrim(orig_line);
	 ltrim_cached = 1;
      }
      return ltrim_cache;
   }

   std::string trim() 
   {
      if (!trim_cached)
      {
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

};

std::ostream& operator <<(std::ostream &os,Fortranline &obj);

typedef std::deque<Fortranline> lines_t;

typedef std::deque<Fortranline> linebuffer_t;

#endif
