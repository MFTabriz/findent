#include <stack>
class pre_analyzer
{
   std::stack<bool> ifelse_stack; // to note if there is an #else after #if

   public:
   int analyze(const std::string s, const int pretype);
   enum {NONE=1,IF,ELIF,ELSE,ENDIF,ENDIFE};


};
