#include "fortran.h"

bool Fortran::output_pre(lines_t &lines, lines_t *outlines)
{
   //
   // if the first line of lines is a preprocessor line
   // output this line and the continuation lines
   // popping lines
   //

   bool to_mycout = outlines == 0;

   if(lines.empty())
      return 0;
   if (lines.front().pre())
   {
      bool p_more = 0;
      while(1)
      {
	 handle_pre_light(lines.front(),p_more);
	 if (lines.front().pre())
	    if (to_mycout)
	       mycout << lines.front().trim() << endline;
	    else
	       outlines->push_back(lines.front().trim());
	 else
	    if (to_mycout)
	       mycout << lines.front().str() << endline;
	    else
	       outlines->push_back(lines.front().str());
	 lines.pop_front();
	 if (lines.empty() || !p_more)
	    break;
      }
      return 1;
   }
   else
      return 0;
}     // end of output_pre

void Fortran::handle_pre_light(fortranline &line, bool &p_more)
{
   //
   // handles preprocessor lines and their continuations:
   //
   // line (input):   line to handle
   // p    (inout):   input:  type of line: CPP or COCO. 
   //                 output: if no continuation is expected, p = 0
   // p_more (output):  true if a continuation is expected
   //
   static int pregentype;

   if (!p_more)   // this is the first line of a preprocessor sequence
      pregentype = line.getpregentype();

   if(pregentype == COCO)
      p_more = (line.lastchar() == '&');
   else
      p_more = (line.lastchar() == '\\');

}         // end of handle_pre_light
