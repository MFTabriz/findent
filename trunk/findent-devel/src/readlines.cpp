#include <stdio.h>
#include <unistd.h>

#include "findent_types.h"
#include "readlines.h"

// linebuffer_t Readlines::curlinebuffer;
// bool         Readlines::indent_handled;
// int          Readlines::input_format;
// int          Readlines::lines_read;
//int          Readlines::num_lines;
// bool         Readlines::reading_from_tty;
//linebuffer_t Readlines::wizardbuffer;
// bool         Readlines::endline_set;


fortranline Readlines::getnext(bool &eof, bool use_wb)
{
   fortranline line;
   eof = 0;
   if (use_wb && !wizardbuffer.empty())
   {
      line = wizardbuffer.front();
      wizardbuffer.pop_front();
      if (reading_from_tty && line.str() == ".")
	 eof = 1;
   }
   else if (!curlinebuffer.empty())
   {
      line = curlinebuffer.front();
      curlinebuffer.pop_front();
      num_lines++;
      if (reading_from_tty && line.str() == ".")
	 eof = 1;
   }
   else
   {
      line = mygetline(eof);
      if (!eof)
	 num_lines++;
   }

   //
   // remove trailing white space
   // FIXED: convert leading tab to space
   //

   line.clean();

   if(!use_wb && !eof)
      wizardbuffer.push_back(line);

   if (!nbseen)
   {
      nbseen = !line.blank_or_comment() && (line.getpregentype() == 0);
      if (flags.auto_firstindent && nbseen)
      {
	 start_indent = guess_indent(line);
	 cur_indent   = start_indent;
	 init_indent();
	 indent_handled = 1;
      }
   }

   return line;
}

void Readlines::handle_reading_from_tty()
{
   reading_from_tty = isatty(fileno(stdin));
   if (reading_from_tty)
   {
      std::cerr << "! Warning: reading from terminal"                << std::endl;
      std::cerr << "! End this session by typing a single dot ('.')" << std::endl;
      std::cerr << "!     on a new line"                             << std::endl;
      std::cerr << "! "                                              << std::endl;
      std::cerr << "! Examples of typical usage:"                    << std::endl;
      std::cerr << "!   help:    findent -h"                         << std::endl;
      std::cerr << "!   indent:  findent < in.f > out.f"             << std::endl;
      std::cerr << "!   convert: findent -ofree < prog.f > prog.f90" << std::endl;
   }
}                // end of handle_reading_from_tty

fortranline Readlines::mygetline(bool &eof)
{
   //
   // reads next line from cin.
   // side effects:
   //   end_of_file is set if endoffile condition is met
   //   endline is set to \n or \r\n
   //   lines_read is incremented
   //

   std::string s;

   getline(std::cin,s);

   //
   // sometimes, files do not end with (cr)lf, hence the test for s=="":
   //
   eof = (std::cin.eof() && s == "");

   lines_read ++;

   if (!eof && reading_from_tty)
      eof = (s == ".");

   s = handle_dos(s);
   return fortranline(s);
}              // end of mygetline

int Readlines::guess_indent(fortranline line)
{
   //
   // count spaces at start of line, correct for tabs and & and label
   //
   int si         = 0;
   bool ready     = 0;
   const int tabl = 8;

   if (input_format == FIXED)
   {
      std::string s = line.str();
      si             = s.find_first_not_of(' ') -6;
      if (si <0)
	 si = 0;
      return si;
   }

   std::string s = line.str();
   for (unsigned int j=0; j<s.length(); j++)
   {
      switch (s[j])
      {
	 case ' ' : case '0' : case '1' : case '2' : case '3' : case '4' : 
	 case '5' : case '6' : case '7' : case '8' : case '9' :
	    si ++;
	    break;
	 case '&' :
	    si++;
	    ready = 1;
	    break;
	 case '\t' :
	    si = (si/tabl)*tabl + tabl;
	    break;
	 default:
	    ready = 1;
	    break;
      }
      if(ready)
	 break;
   }
   return si;
}                // end of guess_indent

std::string Readlines::handle_dos(const std::string &s)
{
   //
   // determine if the input is dos format:
   // side effect: sets endline if not already been set
   //
   std::string sl;
   sl = s;
   if (!endline_set)
   {
      if (sl != "" && lastchar(sl) == '\r')
      {
	 endline = "\r\n";
      }
      endline_set = 1;
   }
   if (sl != "" && lastchar(sl) =='\r')
      sl.erase(sl.length()-1);
   return sl;
}         // end of handle_dos
