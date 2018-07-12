#include <queue>
#include <iostream>
#include <string>
#include "functions.h"
class Lines
{
   std::queue<std::string> linebuffer;
   bool endline_set;
   bool reading_from_tty; 
   bool end_of_file;
   int lines_read;
   std::string endline;
   bool trim_av, ltrim_av, rtrim_av;
   std::string curline, curline_t, curline_rt, curline_lt;

   void reset_curline()
   {
      this->trim_av          = 0;
      this->ltrim_av         = 0; 
      this->rtrim_av         = 0;
   }
   void pop()
   {
      if (!this->linebuffer.empty())
      {
	 this->linebuffer.pop();
      }
   }

   public:

   Lines()
   {
      this->endline_set      = 0;
      this->reading_from_tty = 0;
      this->endline          = "\n";
      this->end_of_file      = 0;
      this->lines_read       = 0;
      this->reset_curline();
   }

   void readline();

   std::string get_endline()
   {
      return this->endline;
   }
   bool eof()
   {
      return this->end_of_file;
   }
   void set_reading_from_tty(const bool b)
   {
      this->reading_from_tty = b;
   }
   bool get_reading_from_tty()
   {
      return this->reading_from_tty;
   }
   void next()
   {
      if (this->linebuffer.empty())
      {
	 this->readline();
      }
      else
      {
	 this->curline=linebuffer.front();
	 this->reset_curline();
	 this->pop();
      }
   }
   std::string c()
   {
      return this->curline;
   }
   std::string ct()
   {
      if (!this->trim_av)
      {
	 ppp("trimming");
	 this->curline_t = trim(this->curline);
	 this->trim_av = 1;
      }
      return this->curline_t;
   }
};
