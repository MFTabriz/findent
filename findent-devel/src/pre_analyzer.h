#ifndef PRE_ANALYZER_H
#define PRE_ANALYZER_H

#include <stack>

class Pre_analyzer
{
   std::stack<bool> ifelse_stack; // to note if there is an #else after #if

   public:
   int analyze(const std::string s, const int pretype);
   enum {NONE=1,IF,ELIF,ELSE,ENDIF,ENDIFE};
};

#endif
