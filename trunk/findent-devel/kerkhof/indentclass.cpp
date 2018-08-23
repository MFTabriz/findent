#include "indentclass.h"

int          Indent::all_indent;
int          Indent::cur_indent;
std::string  Indent::endline;
bool         Indent::endline_set;
bool         Indent::end_of_file;
Flags        Indent::flags;
bool         Indent::indent_handled;
indent_t     Indent::indent;          // to store indents
int          Indent::input_format;
bool         Indent::nbseen;
int          Indent::start_indent;

int Indent::testint;


void Indent::init_indent()
{
   //
   // fills the indent-stack until indent 0
   // if flags.all_indent <= 0: build indent_stack with a number of start_indent's
   //
   while(!indent.empty())
      indent.pop_back();
   int l=0;
   if(flags.all_indent > 0)
   {
      for (l = start_indent%flags.all_indent; l<start_indent; l+=flags.all_indent)
      {
	 push_indent(l);
      }
   }
   else
   {
      for (int i=0; i<100; i++)
	 push_indent(start_indent);
   }
   push_indent(start_indent);

}             // end of init_indent

void Indent::push_indent(int p)
{
   indent.push_back(p);
}

std::string Indent::handle_dos(const std::string &s)
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

int Indent::guess_indent(Fortranline line)
{
   //
   // count spaces at start of line, correct for tabs and & and label
   //
   int si         = 0;
   bool ready     = 0;
   const int tabl = 8;

   if (line.format() == FIXED)
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
