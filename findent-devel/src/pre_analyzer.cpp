#include <string>
#include "pre_analyzer.h"
#include "functions.h"
#include "parser.h"
//
// if start of s ==
// #\s*if
// or
// #\s*elif
// or
// #\s*else
// or
// #\s*endif
//
// then the function returns
// IF:  an #if is found
// ELIF:  an #elif is found
// ELSE:  an #else is found
// ENDIF:  an #endif is found, without preceding #else
// ENDIFE:  an #endif is found, with preceding #else
//
// if start of s ==
// ??\s*if
// or
// ??\s*else if
// or
// ??\s*else
// or
// ??\s*endif
//
// (all case and space independent)
//
// then the function returns
// IF:     '??if'  found
// ELIF:   '??else if'  found
// ELSE:   '??else'  found
// ENDIF:  '??endif'  found, without preceding '#else' or '??else'
// ENDIFE: '??endif'  found, with preceding '#else' or '??else'
//
// The funcion returns NONE if none of above is found.
//
int Pre_analyzer::analyze(const std::string s, const int pretype)
{
   switch(pretype)
   {
      case CPP_IF:  case CPP_ENDIF:  case CPP_ELSE:  case CPP_ELIF:
      case COCO_IF: case COCO_ENDIF: case COCO_ELSE: case COCO_ELIF: 
      case INCLUDE_CPP: case INCLUDE_COCO: break;
      default: return this->NONE;
   }

   int r;
   switch(pretype)
   {
      case CPP_IF: case COCO_IF:
	 this->ifelse_stack.push(0);
	 return this->IF;
      case CPP_ELIF: case COCO_ELIF:
	 return this->ELIF;
      case CPP_ELSE: case COCO_ELSE:
	 if (!this->ifelse_stack.empty())
	 {
	    ifelse_stack.pop();
	    ifelse_stack.push(1);
	 }
	 return this->ELSE;
      case CPP_ENDIF: case COCO_ENDIF:
	 r = this->ENDIF; 
	 if (!ifelse_stack.empty())
	 {
	    if (ifelse_stack.top())
	       r = this->ENDIFE;
	    ifelse_stack.pop();
	 }
	 return r;
    default:
      return this->NONE;
   }
}
