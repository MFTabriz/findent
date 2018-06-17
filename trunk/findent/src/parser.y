%{
// $Id$
#include <iostream>
#include "findent.h"
#include "line_prep.h"
struct propstruct properties;
%}

%token MODULE SUBFUN ENTRY SUBMODULE
%token MODULESUBROUTINE MODULEFUNCTION
%token END ENDSUBROUTINE ENDFUNCTION ENDPROGRAM ENDMODULE ENDSUBMODULE
%token IF THEN ELSE ELSEIF ENDIF
%token WHERE ENDWHERE FORALL ENDFORALL ELSEWHERE
%token DO DOCOMMA DOWHILE DOCONCURRENT ENDDO
%token SELECTCASE SELECTTYPE ENDSELECT CASE CASEDEFAULT TYPEIS CLASSIS CLASSDEFAULT
%token INTERFACE ABSTRACTINTERFACE ENDINTERFACE
%token CONTAINS
%token BLOCK ENDBLOCK
%token BLOCKDATA ENDBLOCKDATA
%token ASSOCIATE ENDASSOCIATE
%token CRITICAL ENDCRITICAL
%token ENUM ENDENUM
%token ASSIGNMENT
%token ASSIGN TO
%token MODULEPROCEDURE PROCEDURE ENDPROCEDURE
%token TIDENTIFIER
%token BLANK
%token FINDFORMAT FREE FIXED UNSURE PROBFREE

%token IDENTIFIER SKIP SKIPALL SKIPNOOP KEYWORD

%token ELEMENTAL IMPURE PURE RECURSIVE SUBROUTINE FUNCTION PROGRAM 
%token EOL NAMED_LABEL
%token STLABEL 
%token TYPE ENDTYPE CLASS
%token BASICTYPE TYPEC
%token QSTRING HSTRING 
%token LR LRB 
%token DOTOPERATOR 
%token I_NUMBER 
%token UNCLASSIFIED
%token ERROR
%token LAST_TOKEN

%left '%'

%%

lline:               labels line
     ;
labels:              empty          
      |              stlabel        
      |              named_label    
      |              stlabel  named_label
      ;
line: 
    |                abstractinterface        { properties.kind = ABSTRACTINTERFACE; }
    |                assignment               { properties.kind = ASSIGNMENT;        }
    |                associate                { properties.kind = ASSOCIATE;         }
    |                blank                    { properties.kind = BLANK;             }
    |                block                    { properties.kind = BLOCK;             }
    |                blockdata                { properties.kind = BLOCKDATA;         }
    |                case                     { properties.kind = CASE;              }
    |                casedefault              { properties.kind = CASEDEFAULT;       }
    |                classdefault             { properties.kind = CLASSDEFAULT;      }
    |                classis                  { properties.kind = CLASSIS;           }
    |                contains                 { properties.kind = CONTAINS;          }
    |                critical                 { properties.kind = CRITICAL;          }
    |                do_construct             { properties.kind = DO;                }
    |                else                     { properties.kind = ELSE;              }
    |                elseif                   { properties.kind = ELSEIF;            }
    |                elsewhere                { properties.kind = ELSEWHERE;         }
    |                endassociate             { properties.kind = ENDASSOCIATE;      }
    |                endblock                 { properties.kind = ENDBLOCK;          }
    |                endblockdata             { properties.kind = ENDBLOCKDATA;      }
    |                endcritical              { properties.kind = ENDCRITICAL;       }
    |                enddo                    { properties.kind = ENDDO;             }
    |                endenum                  { properties.kind = ENDENUM;           }
    |                endforall                { properties.kind = ENDFORALL;         }
    |                endfunction              { properties.kind = ENDFUNCTION;       }
    |                endif                    { properties.kind = ENDIF;             }
    |                endinterface             { properties.kind = ENDINTERFACE;      }
    |                endmodule                { properties.kind = ENDMODULE;         }
    |                endprocedure             { properties.kind = ENDPROCEDURE;      }
    |                endprogram               { properties.kind = ENDPROGRAM;        }
    |                endselect                { properties.kind = ENDSELECT;         }
    |                endsubmodule             { properties.kind = ENDSUBMODULE;      }
    |                endsubroutine            { properties.kind = ENDSUBROUTINE;     }
    |                endtype                  { properties.kind = ENDTYPE;           }
    |                endwhere                 { properties.kind = ENDWHERE;          }
    |                entry                    { properties.kind = ENTRY;             }
    |                enum                     { properties.kind = ENUM;              }
    |                forall_construct         { properties.kind = FORALL;            }
    |                if_construct             { properties.kind = IF;                }
    |                interface                { properties.kind = INTERFACE;         }
    |                module                   { properties.kind = MODULE;            }
    |                moduleprocedure          { properties.kind = PROCEDURE;         }
    |                program_stmt             { properties.kind = PROGRAM;           }
    |                procedure                { properties.kind = PROCEDURE;         }
    |                selectcase               { properties.kind = SELECTCASE;        }
    |                selecttype               { properties.kind = SELECTTYPE;        }
    |                simple_end               { properties.kind = END;               }
    |                subroutine_stmt          { properties.kind = SUBROUTINE;        }
    |                function_stmt            { properties.kind = FUNCTION;          }
    |                submodule                { properties.kind = SUBMODULE;         }
    |                type                     { properties.kind = TYPE;              }
    |                typeis                   { properties.kind = TYPEIS;            }
    |                where_construct          { properties.kind = WHERE;             }
    ;
blank:               BLANK ;

stlabel:             STLABEL getstlabel ;
named_label:         NAMED_LABEL        ;

module:              MODULE enable_identifier IDENTIFIER getname EOL ;

abstractinterface:   ABSTRACTINTERFACE  EOL     ;
contains:            CONTAINS           EOL     ;
interface:           INTERFACE          skipall ;
moduleprocedure:     MODULEPROCEDURE    enable_identifier IDENTIFIER getname EOL ;
procedure:           PROCEDURE          enable_identifier IDENTIFIER getname EOL ;


	/* standard dictates that only                                         */
	/*    PROGRAM program_name                                             */
	/* is allowed, but there is (or was) at least one dialect that allows: */
	/*    PROGRAM                                                          */
	/* and another dialect that allows                                     */
	/*    PROGRAM program_name(p1,...,p8), comment                         */
	/* and                                                                 */
	/*    PROGRAM program_name,p1,...,p8, comment                          */
	/* so we will be a bit sloppy here                                     */

program_stmt:            PROGRAM enable_identifier IDENTIFIER getname enable_skip SKIP
	            |    PROGRAM enable_identifier EOL
		    ;

subroutine_stmt:         subroutineprefix subroutine subroutinename enable_skip SKIP;
subroutine:              subroutine_spec ;
subroutine_spec:         SUBROUTINE
                    |    MODULESUBROUTINE
	            ;
subroutinename:          enable_identifier IDENTIFIER getname ;
subroutineprefix:        empty
                    |    subroutineprefix subroutineprefix_spec 
		    ;
subroutineprefix_spec:  ELEMENTAL   
		    |   IMPURE      
		    |   PURE        
		    |   RECURSIVE   
		    |   intrinsic_type_spec
		    |   TYPEC LR
		    |   CLASS LR 
		    ;

function_stmt:          subroutineprefix function functionname LR enable_skip SKIP ;
function:               function_spec ;
function_spec:          FUNCTION
	            |   MODULEFUNCTION
	            ;
functionname:           enable_identifier IDENTIFIER getname ;

submodule:           SUBMODULE LR enable_identifier IDENTIFIER getname EOL ;

intrinsic_type_spec: BASICTYPE
		   | BASICTYPE kind_selector 
		   ;
kind_selector:       '*' I_NUMBER      /* extension */
	     |       '*' LR            /* extension */
	     |       LR 
	     ;

entry:               ENTRY enable_identifier IDENTIFIER skipall ;

endassociate:        ENDASSOCIATE  construct_name EOL ;
endblock:            ENDBLOCK      construct_name EOL ;
endblockdata:        ENDBLOCKDATA  construct_name EOL ;
endcritical:         ENDCRITICAL   construct_name EOL ;
enddo:               ENDDO         construct_name EOL ;
endenum:             ENDENUM       EOL                ;
endforall:           ENDFORALL     construct_name EOL ;
endfunction:         ENDFUNCTION   construct_name EOL ;
endif:               ENDIF         construct_name EOL ;
endinterface:        ENDINTERFACE  skipall            ;
endmodule:           ENDMODULE     construct_name EOL ;
endprocedure:        ENDPROCEDURE  construct_name EOL ;
endprogram:          ENDPROGRAM    construct_name EOL ;
endselect:           ENDSELECT     skipall            ;
endsubmodule:        ENDSUBMODULE  construct_name EOL ;
endsubroutine:       ENDSUBROUTINE construct_name EOL ;
endtype:             ENDTYPE       construct_name EOL ;
endwhere:            ENDWHERE      construct_name EOL ;
simple_end:          END                          EOL ;
gidentifier:         IDENTIFIER
	   |         TIDENTIFIER 
	   ;

assignment:          lvalue '=' skipnoop
	  |          ASSIGN I_NUMBER TO enable_identifier gidentifier EOL 
	  ;

else:                ELSE           construct_name EOL ;
elseif:              ELSEIF LR THEN construct_name EOL ;
elsewhere:           ELSEWHERE LR   construct_name EOL
	 |           ELSEWHERE      construct_name EOL 
	 ;

if_construct:        IF     LR THEN EOL ;
where_construct:     WHERE  LR EOL ;
forall_construct:    FORALL LR EOL ;

do_construct:        do       I_NUMBER     getdolabel skipall      /* do 100 i=1,10          */
            |        do       gidentifier             skipall      /* do i=1,10              */
            |        docomma  gidentifier             skipall      /* do, i=1,10             */
	    |        do                                       EOL  /* do                     */ 
	    |        DOWHILE      LR                          EOL  /* do while (i<10)        */
	                                                           /* do, while (i<10)       */
	    |        DOCONCURRENT LR                          EOL  /* do concurrent (i=1:20) */
	                                                           /* do, concurrent (i=1:20)*/
	    ;

do:                  DO      enable_identifier ;
docomma:             DOCOMMA enable_identifier ;

selectcase:          SELECTCASE LR EOL     ;
selecttype:          SELECTTYPE LR skipall ;

case:                CASE          LR  skipall ;
casedefault:         CASEDEFAULT       skipall ;
classdefault:        CLASSDEFAULT      skipall ;
classis:             CLASSIS       LR  skipall ;
typeis:              TYPEIS        LR  skipall ;


block:               BLOCK                    EOL ;
blockdata:           BLOCKDATA construct_name EOL ;
associate:           ASSOCIATE LR             EOL ;
critical:            CRITICAL                 EOL ;
enum:                ENUM ','             skipall ;

type:                type1 ','  skipall
    |                type1 ':'  skipall
    |                type1 IDENTIFIER  skipall 
    ;
type1:               TYPE enable_identifier ;

lvalue:              gidentifier
      |              gidentifier LR
      |              lvalue '%' lvalue
      ;
construct_name:      enable_identifier empty
	      |      enable_identifier IDENTIFIER getname
	      ;
skipall:             enable_skipall SKIPALL
       ;
skipnoop:            enable_skipnoop SKIPNOOP
        ;
enable_identifier:   {lexer_enable(IDENTIFIER);}
	         ;
enable_skip:         {lexer_enable(SKIP);}
	   ;
enable_skipall:      {lexer_enable(SKIPALL);}
	      ;
enable_skipnoop:     {lexer_enable(SKIPNOOP);}
	       ;
getname:             {properties.name=lexer_getname();}
       ;
getstlabel:          {properties.label=lexer_getstlabel();}
          ;
getdolabel:          {properties.dolabel=lexer_geti_number();}
          ;
empty:               /* empty */
     ;
%%

void resetprop()
{
   properties.kind    = UNCLASSIFIED;
   properties.name    = "";
   properties.label   = "";
   properties.dolabel = "";
}

propstruct parseline(class line_prep p)
{
   D(O("entering parseline"););
   lexer_set(p);
   resetprop();
   lexer_enable(IDENTIFIER);
   yyparse();
   if (properties.kind != UNCLASSIFIED)
      return properties;
   lexer_set(p);
   lexer_enable(KEYWORD);
   yyparse();
   return properties;
}

void yyerror(const char *c)
{
    D(O("ERROR");O(c););
}

extern "C" int yywrap()
{
  D(O("yywrap"););
  return 1;
}

