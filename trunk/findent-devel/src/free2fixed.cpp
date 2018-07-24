#include "findent.h"
#include "findent_functions.h"
#include "fixed2fixed.h"
void free2fixed()
{
   std::list<fortranline> localcurlines;

   bool need_continuation = 0;
   while (!curlines.empty())
   {
      int pretype     = curlines.front().scanfixpre();
      std::string s   ;

      std::string continuation = "\\";
      std::string label;
      switch (pretype)
      {
	 case CPP:  case CPP_IF:  case CPP_ELIF:  case CPP_ENDIF:  case CPP_ELSE: 
	 case COCO: case COCO_IF: case COCO_ELIF: case COCO_ENDIF: case COCO_ELSE: 
	    if (pretype == COCO)
	       continuation = "&";
	    localcurlines.push_back(curlines.front());
	    while (!curlines.empty())
	    {
	       if(curlines.front().lastchar() == continuation)
	       {
		  curlines.pop_front();
		  localcurlines.push_back(curlines.front());
	       }
	       else
		  break;
	    }
	    break;
	 default:
	    s  = curlines.front().trimmed_line();

	    if (labellength > 0)
	    {
	       label = s.substr(0,labellength);
	       s = s.substr(labellength);
	    }

	    if (curlines.front().firstchar() == "&")
	       s = s.substr(1);

	    if (need_continuation)
	       s = "     &" + s;
	    else
	       if (curlines.front().orig().substr(0,1) != "!")
		  s = "      " + s;

	    if (curlines.front().lastchar() == "&" && curlines.front().firstchar() != "!")
	    {
	       s = s.substr(0,s.length()-1);
	       need_continuation = 1;
	    }
	    else
	       need_continuation = 0;

	    if (labellength > 0)
	       s = label + "      " + s;
	    localcurlines.push_back(fortranline(s));
      }
      curlines.pop_front();
   }
   curlines = localcurlines;
   fortranline::setformat(FIXED);
#if 1
   fixed2fixed();
#else
   while (!curlines.empty())
   {
      std::cout << curlines.front().orig()<<std::endl;
      curlines.pop_front();
   }
#endif
   fortranline::setformat(FREE);
}
