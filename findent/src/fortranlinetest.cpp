#include <iostream>
#include <queue>
#include "fortranline.h"
std::queue<fortranline> linebuffer;
int main()
{
   fortranline s;
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
   fortranline l1;
   fortranline l2;

   std::cout << l1.format2txt() << " " << l2.format2txt() << std::endl;
   fortranline::format = fortranline::FIXED;
   std::cout << l1.format2txt() << " " << l2.format2txt() << std::endl;
   l1.format = fortranline::FREE;
   std::cout << l1.format2txt() << " " << l2.format2txt() << std::endl;

   return 0;
}
