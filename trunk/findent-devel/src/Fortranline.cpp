#include "Fortranline.h"
void Fortranline::print()
{
   std::cout << "orig_line: [" << orig_line << "]" << std::endl;
   if(has_trim)
      std::cout << "trim_line: [" << trim_line << "]" << std::endl;
   if(has_ltrim)
      std::cout << "ltrim_line: [" << ltrim_line << "]" << std::endl;
   if(has_rtrim)
      std::cout << "rtrim_line: [" << rtrim_line << "]" << std::endl;
   if(has_first)
      std::cout << "firstchar: [" << first << "]" << std::endl;
   if(has_last)
      std::cout << "lastchar: [" << last << "]" << std::endl;
   if(has_first2)
      std::cout << "first2chars: [" << first2 << "]" << std::endl;
   if(has_ltab2sp)
      std::cout << "ltab2sp: [" << ltab2sp_line << "]" << std::endl;
   if(has_scanfixpre)
      std::cout << "scanfixpre: " << Scanfixpre << std::endl;
}

std::string Ltab2sp(const std::string& s)
{
   //
   // converts leading white space and white space after a statement label
   //   to spaces and removes trailing white space
   // if line starts with 0-5 spaces or digits followed by a tab, followed
   //   by 1-9, this is counted as 5 spaces, it appears that many compilers
   //   assume that 
   //   <tab>1  <some code>
   //   is a continuation statement, if the continuation character is 1-9
   //   If the character is not within 1-9, it is assumed that 
   //   this character is the first of a statement, so in this case
   //   this is counted as 6 spaces
   //

   int si              = 0;
   bool ready          = 0;
   const int tabl      = 6;
   bool firsttab       = 1;
   std::string leader  = "";
   int removed         = 0;

   for (unsigned int j=0; j<s.length(); j++)
   {
      switch (s[j])
      {
	 case ' ' :
	    si ++;
	    removed++;
	    leader = leader + " ";
	    break;
	 case '\t' :
	    if (firsttab)
	    {
	       firsttab = 0;
	       if (si < 6)
		  //
		  // investigate next char: if 1-9, count this tab as 5 spaces
		  //
		  if (s.length() > j+1)
		     if (s[j+1] >= '1' && s[j+1] <= '9')
		     {
			si = 5;
			removed++;
			leader = std::string(5,' ');
			break;
		     }
	    }
	    si = (si/tabl)*tabl + tabl;
	    leader = leader + std::string(si - leader.length(),' ');
	    break;
	 case '0': case '1': case '2': case '3': case '4':
	 case '5': case '6': case '7': case '8': case '9':
	    si++;
	    removed++;
	    leader += s[j];
	    firsttab = 0;
	    break;
	 default:
	    ready = 1;
	    break;
      }
      if(ready)
	 break;
   }
   return leader + trim(s.substr(removed));
}
