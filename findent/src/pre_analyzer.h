#include <stack>
class pre_analyzer
{
   std::stack<bool> ifelse_stack; // to note if there is an #else after #if

   public:
   int analyze(const std::string s);
   enum {PRE_NONE,PRE_IF,PRE_ELIF,PRE_ELSE,PRE_ENDIF,PRE_ENDIFE};


};
