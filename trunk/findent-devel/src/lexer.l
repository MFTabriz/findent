%{
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "debug.h"
#include "lexer.h"
#include "line_prep.h"
#include "parser.h"

#define YY_DECL extern "C" int yylex()
std::stack<int> start_stack;
std::string     lexer_name, lexer_stlabel, lexeri_number, lexer_rest, lexer_string;
std::string     input_string;
int             lrlevel;
bool            lrreturn;
Line_prep       pline;

%}

%s state_identifier state_keyword

%x state_lr state_lrb state_skip state_skipall state_skipnoop state_error
%x state_findformat state_scanfixpre state_scanompfixed state_scanompfree
%x state_incfilename state_char

b [ \t]

  //  following are keywords starting with c
ckey  call|close|common|continue|case|contains|cycle|class|codimension|contiguous|critical|complex|changeteam
%%

<state_error>.  {  D(O("ERROR");Y;); return ERROR; }

<state_lr>{
"("             { D(O("lr+");O(lrlevel);Y;); lrlevel++; }

")"             { D(O("lr-");O(lrlevel);Y;); 
                  lrlevel--;
		  if(lrlevel == 0)
		  {
		     D(O("state:");O(start_stack.top());O(lrreturn););
		     BEGIN(start_stack.top());
		     start_stack.pop();
		     if(lrreturn)
		     {
			return LR;
		     }
		  }
		}

.               { D(O("lrbla");O(lrlevel);Y;); } 
\n              { D(O("lreol");O(lrlevel);Y;); yyless(0); BEGIN(start_stack.top()); }

}

<state_lrb>{
"["             { D(O("lrb+");O(lrlevel);Y;); 
                  lrlevel++;
		}

"]"             { D(O("lrb-");O(lrlevel);Y;); 
                  lrlevel--;
		  if(lrlevel == 0)
		  {
		     D(O("state:");O(start_stack.top());O(lrreturn););
		     BEGIN(start_stack.top());
		     start_stack.pop();
		     if(lrreturn)
		     {
			return LRB;
		     }
		  }
		}

.               { D(O("lrbbla");O(lrlevel);Y;); 
		}

\n              { D(O("lrbeol");O(lrlevel);Y;) 
                  yyless(0);
                  BEGIN(start_stack.top());
		}

}

<state_skip,state_skipall,state_skipnoop>{
"("          {  D(O("skipLPAREN");Y;);
		start_stack.push(YY_START);
		lrlevel  = 1;
		lrreturn = 0;
		BEGIN(state_lr);
	     }

"["          {  D(O("skipLPAREN");Y;);
		start_stack.push(YY_START);
		lrlevel  = 1;
		lrreturn = 0;
		BEGIN(state_lrb);
	     }
}

<state_skip>"="             { D(O("NOSKIP");Y;);     return yytext[yyleng-1]; }
<state_skipnoop>[,|~!#$]    { D(O("NOSKIPNOOP");Y;); return yytext[yyleng-1]; }

<state_skip,state_skipall,state_skipnoop>{
\n           { D(O("endSKIP");Y;);
               switch(YY_START)
	       {
                  case state_skip:
		     return SKIP;
	          case state_skipall:
		     return SKIPALL;
		  case state_skipnoop:
		     return SKIPNOOP;
	       }
	     }

.            { D(O("SKIP");Y;); }
}

<state_identifier>{
[[:alpha:]][[:alnum:]_$]*  { D(O("IDENTIFIER");Y;);  lexer_name = yytext; return IDENTIFIER;  }
[[:alpha:]][[:alnum:]_$%]* { D(O("TIDENTIFIER");Y;); lexer_name = yytext; return TIDENTIFIER; }
}

<state_incfilename>{  /* to be used in '#include <file>' */
[^>]+                      { D(O("INCFILENAME");Y;); lexer_string = yytext; 
                             BEGIN state_char; return INCFILENAME; }
}

<state_char>{
\n                            {  D(O("EOL"););   return EOL;        }
.                             {  D(O("BLA");Y;); return yytext[0];  }
}

<state_keyword>{
abstractinterface { D(O("ABSTRACTINTERFACE");Y;); return ABSTRACTINTERFACE; }
associate         { D(O("ASSOCIATE");Y;);         return ASSOCIATE;         }
assign            { D(O("ASSIGN");Y;);            return ASSIGN;            }
block             { D(O("BLOCK");Y;);             return BLOCK;             }
blockdata         { D(O("BLOCKDATA");Y;);         return BLOCKDATA;         }
casedefault       { D(O("CASEDEFAULT");Y);        return CASEDEFAULT;       }
case              { D(O("CASE");Y);               return CASE;              }
character         { D(O("CHARACTER");Y;);         return BASICTYPE;         }
classdefault      { D(O("CLASSDEFAULT");Y);       return CLASSDEFAULT;      }
changeteam        { D(O("CHANGETEAM");Y);         return CHANGETEAM;        }
class             { D(O("CLASS");Y;);             return CLASS;             }
classis           { D(O("CLASSIS");Y);            return CLASSIS;           }
complex           { D(O("COMPLEX");Y;);           return BASICTYPE;         }
contains          { D(O("CONTAINS");Y);           return CONTAINS;          }
critical          { D(O("CRITICAL");Y;);          return CRITICAL;          }
do                { D(O("DO");Y;);                return DO;                }
do,               { D(O("DO,");Y;);               return DOCOMMA;           }
doconcurrent      { D(O("DOCONCURRENT");Y;);      return DOCONCURRENT;      }
do,concurrent     { D(O("DO,CONCURRENT");Y;);     return DOCONCURRENT;      }
dowhile           { D(O("DOWHILE");Y;);           return DOWHILE;           }
do,while          { D(O("DO,WHILE");Y;);          return DOWHILE;           }
doublecomplex     { D(O("DOUBLECOMPLEX");Y;);     return BASICTYPE;         }
doubleprecision   { D(O("DOUBLEPRECISION");Y;);   return BASICTYPE;         }
elemental         { D(O("ELEMENTAL");Y;);         return ELEMENTAL;         }
else              { D(O("ELSE");Y);               return ELSE;              }
elseif            { D(O("ELSEIF");Y);             return ELSEIF;            }
elsewhere         { D(O("ELSEWHERE");Y);          return ELSEWHERE;         }
endassociate      { D(O("ENDASSOCIATE");Y;);      return ENDASSOCIATE;      }
endblock          { D(O("ENDBLOCK");Y;);          return ENDBLOCK;          }
endblockdata      { D(O("ENDBLOCKDATA");Y;);      return ENDBLOCKDATA;      }
endcritical       { D(O("ENDCRITICAL");Y;);       return ENDCRITICAL;       }
enddo             { D(O("ENDDO");Y;);             return ENDDO;             }
end               { D(O("END");Y;);               return END;               }
endenum           { D(O("ENDENUM");Y;);           return ENDENUM;           }
endforall         { D(O("ENDFORALL");Y;);         return ENDFORALL;         }
endfunction       { D(O("ENDFUNCTION");Y;);       return ENDFUNCTION;       }
endif             { D(O("ENDIF");Y);              return ENDIF;             }
endinterface      { D(O("ENDINTERFACE");Y;);      return ENDINTERFACE;      }
endmodule         { D(O("ENDMODULE");Y;);         return ENDMODULE;         }
endprocedure      { D(O("ENDPROCEDURE");Y;);      return ENDPROCEDURE;      }
endprogram        { D(O("ENDPROGRAM");Y;);        return ENDPROGRAM;        }
endselect         { D(O("ENDSELECT");Y);          return ENDSELECT;         }
endsubroutine     { D(O("ENDSUBROUTINE");Y;);     return ENDSUBROUTINE;     }
endsubmodule      { D(O("ENDSUBMODULE");Y;);      return ENDSUBMODULE;      }
endteam           { D(O("ENDTEAM");Y);            return ENDTEAM;           }
endtype           { D(O("ENDTYPE");Y;);           return ENDTYPE;           }
endwhere          { D(O("ENDWHERE");Y;);          return ENDWHERE;          }
entry             { D(O("ENTRY");Y);              return ENTRY;             }
enum              { D(O("ENUM");Y;);              return ENUM;              }
forall            { D(O("FORALL");Y;);            return FORALL;            }
function          { D(O("FUNCTION");Y;);          return FUNCTION;          }
if                { D(O("IF");Y;);                return IF;                }
impure            { D(O("IMPURE");Y;);            return IMPURE;            }
include           { D(O("INCLUDE");Y;);           return INCLUDE;           }
#include          { D(O("INCLUDE_CPP");Y;);       return INCLUDE_CPP;       }
\?\?include       { D(O("INCLUDE_COCO");Y);       return INCLUDE_COCO;      }
integer           { D(O("INTEGER");Y;);           return BASICTYPE;         }
interface         { D(O("INTERFACE");Y;);         return INTERFACE;         }
logical           { D(O("LOGICAL");Y;);           return BASICTYPE;         }
module            { D(O("MODULE");Y);             return MODULE;            }
moduleprocedure   { D(O("MODULEPROCEDURE");Y);    return MODULEPROCEDURE;   }
modulesubroutine  { D(O("MODULESUBROUTINE");Y);   return MODULESUBROUTINE;  }
modulefunction    { D(O("MODULEFUNCTION");Y);     return MODULEFUNCTION;    }
procedure         { D(O("PROCEDURE");Y);          return PROCEDURE;         }
program           { D(O("PROGRAM");Y;);           return PROGRAM;           }
pure              { D(O("PURE");Y;);              return PURE;              }
real              { D(O("REAL");Y;);              return BASICTYPE;         }
recursive         { D(O("RECURSIVE");Y;);         return RECURSIVE;         } 
selectcase        { D(O("SELECTCASE");Y);         return SELECTCASE;        }
selecttype        { D(O("SELECTTYPE");Y);         return SELECTTYPE;        }
submodule         { D(O("SUBMODULE");Y;);         return SUBMODULE;         }
subroutine        { D(O("SUBROUTINE");Y;);        return SUBROUTINE;        }
to                { D(O("TO");Y;);                return TO;                }
then              { D(O("THEN");Y;);              return THEN;              }
type              { D(O("TYPE");Y;);              return TYPE;              }
type/\(           { D(O("TYPEC");Y;);             return TYPEC;             }
typeis            { D(O("TYPEIS");Y);             return TYPEIS;            }
use               { D(O("USE");Y);                return USE;               }
where             { D(O("WHERE");Y;);             return WHERE;             }
}

<state_findformat>{
^\?\?.*\n                     { D(O("UNSURE");Y;);   return UNSURE;   }
^[^dDcC#!* 0-9].*\n           { D(O("FREE");Y;);     return FREE;     }
^[ 0-9]{1,4}[[:alpha:]_%].*\n { D(O("FREE");Y;);     return FREE;     }
^[^!]*!.*\n                   { D(O("UNSURE");Y;);   return UNSURE;   }
^[ ]{5}&[^&]*\n               { D(O("UNSURE");Y;);   return UNSURE;   }
^.{0,4}&{b}*\n                { D(O("FREE");Y;);     return FREE;     }
^.{6,}&{b}*\n                 { D(O("FREE");Y;);     return FREE;     }
^[^&]*&{b}*\n                 { D(O("FREE");Y;);     return FREE;     }
^[ ]{0,4}&.*\n                { D(O("FREE");Y;);     return FREE;     }
^[ ]{6,}&.*\n                 { D(O("FREE");Y;);     return FREE;     }
^{ckey}.*\n                   { D(O("FREE");Y;);     return FREE;     }
^c{b}+[[:alnum:]].*\n         { D(O("FIXED");Y;);    return FIXED;    }
^[ 0123456789]{6}.*\n         { D(O("UNSURE");Y;);   return UNSURE;   }
.*\n                          { D(O("UNSURE");Y;);   return UNSURE;   }
}

<state_scanompfixed>{
^[c!\*]\$[ 0-9]{3}[ 0]{0,1} |          /* a first line */
^[c!\*]\$[ ]{3}[^ ^0]       |          /* a continuation line  */
^[c!\*]\${b}*                 { D(O("FIXOMP");Y;);
                                return OMP;
                              }
\n                            {  D(O("EOL"););   return EOL;        }
.                             {  D(O("BLA");Y;); return yytext[0];  }
}
<state_scanompfree>{
^{b}*!\$$ |
^{b}*!\${b}                   { D(O("OMP");Y;);
				return OMP;
                              }
\n                            {  D(O("EOL"););   return EOL;        }
.                             {  D(O("BLA");Y;); return yytext[0];  }
}
<state_scanfixpre>{
{b}*\!{b}*findentfix:p-on   { D(O("FINDENTFIX P-ON");Y;); 
				return P_ON;
		              }
^[c\*]{b}*findentfix:p-on   { D(O("FIXFINDENTFIX P-ON");Y;);
				return P_ON;
		              }
{b}*\!{b}*findentfix:p-off  { D(O("FINDENTFIX P-OFF");Y;); 
				return P_OFF;
		              }
^[c\*]{b}*findentfix:p-off  { D(O("FIXFINDENTFIX P-OFF");Y;);
				return P_OFF;
		              }
{b}*\!{b}*findentfix:         { D(O("FINDENTFIX");Y;); 
                                size_t l = input_string.length()-yyleng-1;
                                lexer_rest = input_string.substr(yyleng,l);
				return FINDENTFIX;
		              }
^[c\*]{b}*findentfix:         { D(O("FIXFINDENTFIX");Y;);
                                size_t l = input_string.length()-yyleng-1;
                                lexer_rest = input_string.substr(yyleng,l);
				return FIXFINDENTFIX;
		              }
^{b}*#                        { D(O("CPP");Y;);
                                return CPP;
                              }
^{b}*#{b}*if                  { D(O("CPP_IF");Y;);
                                return CPP_IF;
			      }
^{b}*#{b}*endif               { D(O("CPP_ENDIF");Y;);
                                return CPP_ENDIF;
			      }
^{b}*#{b}*else                { D(O("CPP_ELSE");Y;);
                                return CPP_ELSE;
			      }
^{b}*#{b}*elif                { D(O("CPP_ELIF");Y;);
                                return CPP_ELIF;
			      }
^{b}*#{b}*include             { D(O("INCLUDE_CPP");Y;);
                                return INCLUDE_CPP;
		              }

^{b}*\?\?                     { D(O("COCO");Y;);
                                return COCO;
                              }
^{b}*\?\?{b}*i{b}*f           { D(O("COCO_IF");Y;);
                                return COCO_IF;
			      }
^{b}*\?\?{b}*e{b}*n{b}*d{b}*i{b}*f { D(O("COCO_ENDIF");Y;);
                                return COCO_ENDIF;
			      }
^{b}*\?\?{b}*e{b}*l{b}*s{b}*e { D(O("COCO_ELSE");Y;);
                                return COCO_ELSE;
			      }
^{b}*\?\?{b}*e{b}*l{b}*s{b}*e{b}*i{b}*f { D(O("COCO_ELIF");Y;);
                                return COCO_ELIF;
			      }
^{b}*\?\?{b}*i{b}*n{b}*c{b}*l{b}*u{b}*d{b}*e          { D(O("INCLUDE_COCO");Y;);
                              /* coco statements must start with '??' in column 1.
			         However, for this code that is somewhat inconvenient,
				 so we allow white space before '??' */
                                return INCLUDE_COCO;
		              }


\n                       {  D(O("EOL"););   return EOL;        }
.                        {  D(O("BLA");Y;); return yytext[0];  }
}

" "[0-9]*" "    {
		   int type = pline.get_type(std::string(yytext));
                   D(O("found_special");O(type);O(pline.get_type_as_string(std::string(yytext)));Y;);
		   D(O("encoded line");O(pline.get_line_encoded()););
		    if (type == pline.is_string)
		    {
		       lexer_string = pline.get_value(std::string(yytext));
		       D(O("QSTRING");O(lexer_string);Y;);
		       return QSTRING;
		    }
		    if (type == pline.is_stlabel)
		    {
		       lexer_stlabel = pline.get_value(std::string(yytext));
		       D(O("STLABEL");O(lexer_stlabel);Y;);
		       return STLABEL;
		    }
		    if (type == pline.is_dotop)
		    {
		       D(O("DOTOPERATOR"););
		       return DOTOPERATOR;
		    }
		    D(O("This should not happen"););
                }


[[:alpha:]][[:alnum:]_]*:/[^:] {  D(O("NAMED_LABEL");Y;);
                            lexer_name = yytext;
			    lexer_name.erase(lexer_name.size()-1);
                            return NAMED_LABEL;
			 }

[0-9][0-9]*              {  D(O("I_NUMBER");Y;);
                            lexer_name = yytext;
			    lexeri_number = yytext;
                            return I_NUMBER;
                         }


"("                      {  D(O("LPAREN");Y;);
                            start_stack.push(YY_START);
			    lrlevel  = 1;
			    lrreturn = 1;
			    BEGIN(state_lr);
			 }

"["                      {  D(O("LPARENB");Y;);
                            start_stack.push(YY_START);
			    lrlevel  = 1;
			    lrreturn = 1;
			    BEGIN(state_lrb);
			 }

^\n                      {  D(O("BLANK");); return BLANK;      }

\n                       {  D(O("EOL"););   return EOL;        }
.                        {  D(O("BLA");Y;); return yytext[0];  }

%%

void lexer_set(Line_prep p, const int state)
{
   input_string  = p.get_line_encoded()+'\n';
   pline         = p;
   yy_delete_buffer(YY_CURRENT_BUFFER);
   BEGIN(INITIAL);
   yy_scan_string(input_string.c_str());
   D(O("lexer_set");O(input_string);O(p.get_type_as_string(0)););
   lexer_enable(state);
}

void lexer_set(const std::string &s, const int state)
{
   input_string  = s+'\n';
   D(O("lexer_set");O(input_string););
   yy_delete_buffer(YY_CURRENT_BUFFER);
   yy_scan_string(input_string.c_str());
   lexer_enable(state);
}

void lexer_enable(const int k)
{
   switch(k)
   {
      case IDENTIFIER:    BEGIN(state_identifier);   break;
      case INCFILENAME:   BEGIN(state_incfilename);  break;
      case SKIPALL:       BEGIN(state_skipall);      break;
      case SKIP:          BEGIN(state_skip);         break;
      case SKIPNOOP:      BEGIN(state_skipnoop);     break;
      case KEYWORD:       BEGIN(state_keyword);      break;
      case FINDFORMAT:    BEGIN(state_findformat);   break;
      case SCANFIXPRE:    BEGIN(state_scanfixpre);   break;
      case SCANOMPFIXED:  BEGIN(state_scanompfixed); break;
      case SCANOMPFREE:   BEGIN(state_scanompfree);  break;
      default:
	 D(O("invalid parameter in lexer_enable");O(k););
	 BEGIN(state_error);
	 break;
   }
   D(O("enabled");O(k);O(YY_START););
}

std::string lexer_getname()
{
   return lexer_name;
}
std::string lexer_getstlabel()
{
   return lexer_stlabel;
}
std::string lexer_geti_number()
{
   return lexeri_number;
}
std::string lexer_getrest()
{
   return lexer_rest;
}
std::string lexer_getstring()
{
   D(O("lexer_string");O(lexer_string););
   return lexer_string;
}

#if 0
// maybe we need this in the future:
// not sure if this works OK
std::stack<std::string> input_string_stack;
void lexer_push(std::string s, const int state)
{
   // https://sourceforge.net/p/flex/mailman/message/30542280/

   input_string_stack.push(s);
   input_string = s+'\n';
   yypush_buffer_state(YY_CURRENT_BUFFER);
   yy_scan_string(input_string.c_str());
   lexer_enable(state);
}
void lexer_pop()
{
   yypop_buffer_state();
   input_string=input_string_stack.top();
   input_string_stack.pop();
}
#endif

void quiet_compiler()                   // to prevent warning about unused unput
{
   char *a=0;
   yyunput(1,a);
}

