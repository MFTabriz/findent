#include <iostream>
#include "Lines.h"
int main()
{
   std::cout << "start linestest" << std::endl;
   Lines ll;
   ll.set_reading_from_tty(1);
   std::string s;
   for(int i=0; i<3; i++)
   {
      ll.readline();
   }
   for(int i=0; i<3; i++)
   {
      ll.next();
      ppp("c:"+ll.c());
      ppp("ct:"+ll.ct());
      ppp("ct:"+ll.ct());
   }
   ll.next();
   ppp("c:"+ll.c());
   ppp("ct:"+ll.ct());
   std::cout << "end linestest" << std::endl;
}
