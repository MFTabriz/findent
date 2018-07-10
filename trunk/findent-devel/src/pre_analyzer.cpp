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
// IF_pre:  an #if is found
// ELIF_pre:  an #elif is found
// ELSE_pre:  an #else is found
// ENDIF_pre:  an #endif is found, without preceding #else
// ENDIFE_pre:  an #endif is found, with preceding #else
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
// IF_pre:     '??if'  found
// ELIF_pre:   '??else if'  found
// ELSE_pre:   '??else'  found
// ENDIF_pre:  '??endif'  found, without preceding '#else' or '??else'
// ENDIFE_pre: '??endif'  found, with preceding '#else' or '??else'
//
// The funcion returns NONE_pre if none of above is found.
//
int pre_analyzer::analyze(const std::string s, const int pretype)
{
   switch(pretype)
   {
      case CPP_IF:  case CPP_ENDIF:  case CPP_ELSE:  case CPP_ELIF:
      case COCO_IF: case COCO_ENDIF: case COCO_ELSE: case COCO_ELIF: break;
      default: return this->NONE_pre;
   }

   int r;
   switch(pretype)
   {
      case CPP_IF: case COCO_IF:
	 this->ifelse_stack.push(0);
	 return pre_analyzer::IF_pre;
      case CPP_ELIF: case COCO_ELIF:
	 return pre_analyzer::ELIF_pre;
      case CPP_ELSE: case COCO_ELSE:
	 if (!this->ifelse_stack.empty())
	 {
	    ifelse_stack.pop();
	    ifelse_stack.push(1);
	 }
	 return pre_analyzer::ELSE_pre;
      case CPP_ENDIF: case COCO_ENDIF:
	 r = pre_analyzer::ENDIF_pre; 
	 if (!ifelse_stack.empty())
	 {
	    if (ifelse_stack.top())
	       r = pre_analyzer::ENDIFE_pre;
	    ifelse_stack.pop();
	 }
	 return r;
    default:
      return pre_analyzer::NONE_pre;
   }
}
