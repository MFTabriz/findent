#include <iostream>

#include "fortranline.h"

void Fortranline::print()
{
   std::cout << "orig_line: ["      << orig_line      << "]" << std::endl;
   std::cout << "trim: ["           << trim()         << "]" << std::endl;
   std::cout << "ltrim: ["          << ltrim()        << "]" << std::endl;
   std::cout << "rtrim: ["          << rtrim()        << "]" << std::endl;
   std::cout << "trimmed_line: ["   << trimmed_line() << "]" << std::endl;
   std::cout << "firstchar: ["      << firstchar()    << "]" << std::endl;
   std::cout << "lastchar: ["       << lastchar()     << "]" << std::endl;
   std::cout << "first2chars: ["    << first2chars()  << "]" << std::endl;
   std::cout << "scanfixpre: "      << scanfixpre()   <<        std::endl;
   std::cout << "rest: ["           << rest()         << "]" << std::endl;
   std::cout << "global_format:"    << g_format2txt() <<        std::endl;
}

std::ostream& operator <<(std::ostream &os,Fortranline &obj)
{
   os<<"["<<obj.str()<<"]";
   return os;
}

void Fortranline::do_clean()
{
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
	 // code to create orig_without_omp
	 if (omp())
	 {
	    orig_without_omp = "  " + orig_line.substr(2);
	 }
	 else
	    orig_without_omp = orig_line;
	 break;
      case FREE:
      default:
	 if (line_length() == 0)
	    orig_line = ::rtrim(orig_line);
	 else
	    orig_line = ::rtrim(orig_line.substr(0,line_length()));
	 // code to create orig_without_omp
	 if (omp())
	 {
	    //
	    // this is a line starting with [ ]*!$
	    // there is a problem here: if this is the first
	    // line then a space must follow. If it is not the
	    // first line, then anything can follow.
	    // To simplify things, the lexer only says it is a
	    // omp conditional compilation line if blank space 
	    // follows !$, or the line ends at !$
	    //
	    // orig_line will start with '!$ '
	    // chop off
	    //
	    std::string sl = ::ltrim(orig_line);
	    switch(sl.length())
	    {
	       case 0:  // cannot happen
		  orig_without_omp = "";
		  break;
	       case 1:  // cannot happen
		  orig_without_omp = " ";
		  break;
	       case 2:
		  orig_without_omp = "  ";
		  break;
	       case 3:
		  orig_without_omp = "   ";
		  break;
	       default:
		  orig_without_omp = sl.substr(3);
	    }
	 }
	 else
	    orig_without_omp = orig_line;
	 break;
   }
   is_clean = 1;
}

bool Fortranline::do_omp()
{
      if (!gl->global_omp)
	 return 0;
      if (format() == FIXED)
	 lexer_set(orig_line,SCANOMPFIXED);
      else
	 lexer_set(orig_line,SCANOMPFREE);
      int rc = yylex();
      return rc == OMP;
}
