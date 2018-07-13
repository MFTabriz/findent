#include <iostream>
#include <queue>
#include "Fortranline.h"
std::queue<Fortranline> linebuffer;
int main()
{
   Fortranline s;
   s.set_line("   1  ");
   s.trim();
   linebuffer.push(s);
   s.set_line("   2");
   s.ltrim();
   linebuffer.push(s);
   s.set_line("   3x   ");
   s.firstchar();
   s.lastchar();
   linebuffer.push(s);
   s.set_line("  #ifdef  ");
   s.first2chars();
   s.ltab2sp();
   s.scanfixpre();
   linebuffer.push(s);
   while(1)
   {
      if(linebuffer.empty())
	 break;
      linebuffer.front().lastchar();
      linebuffer.front().print();
      linebuffer.pop();
   }
}
