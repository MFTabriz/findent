#include "Lines.h"
void Lines::readline()
   //
   // reads line from stdin, stores the line in linebuffer
   // sets this.endline to "\n" or "\r\n", depending on
   // the last characters of the line read.
   //
{
   getline(std::cin,this->curline);
   //
   // sometimes, files do not end with (cr)lf, hence the test for s=="":
   //
   this->end_of_file = (std::cin.eof() && this->curline == "");

   if (!this->end_of_file && this->reading_from_tty)
      this->end_of_file = (this->curline == ".");

   if (!this->endline_set)
   {
      if (this->curline != "" && lastchar(this->curline) == '\r')
      {
	 this->endline = "\r\n";
	 this->curline.erase(this->curline.length()-1);
      }
      this->endline_set = 1;
   }

   this->linebuffer.push(this->curline);
   this->reset_curline();
}
