%{
#include <iostream>

#include "debug.h"
#include "lexer.h"
#include "line_prep.h"
#include "prop.h"

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
%token CHANGETEAM ENDTEAM
%token ENUM ENDENUM
%token ASSIGNMENT
%token ASSIGN TO
%token MODULEPROCEDURE PROCEDURE ENDPROCEDURE
%token TIDENTIFIER
%token BLANK CHAR
%token FINDFORMAT UNKNOWN FREE FIXED UNSURE PROBFREE FINDENTFIX FIXFINDENTFIX
%token P_ON P_OFF
%token SCANFIXPRE
%token CPP_IF CPP_ENDIF CPP_ELSE CPP_ELIF CPP
%token COCO_IF COCO_ENDIF COCO_ELSE COCO_ELIF COCO
%token INCLUDE INCLUDE_CPP INCLUDE_CPP_STD INCLUDE_COCO INCFILENAME
%token USE
%token SEGMENT ENDSEGMENT ESOPE

%token IDENTIFIER SKIP SKIPALL SKIPNOOP KEYWORD

%token ELEMENTAL IMPURE PURE RECURSIVE NON_RECURSIVE SUBROUTINE FUNCTION PROGRAM 
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
%token OMP SCANOMPFIXED SCANOMPFREE
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
    |                changeteam               { properties.kind = CHANGETEAM;        }
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
    |                endteam                  { properties.kind = ENDTEAM;           }
    |                endtype                  { properties.kind = ENDTYPE;           }
    |                endwhere                 { properties.kind = ENDWHERE;          }
    |                entry                    { properties.kind = ENTRY;             }
    |                enum                     { properties.kind = ENUM;              }
    |                forall_construct         { properties.kind = FORALL;            }
    |                if_construct             { properties.kind = IF;                }
    |                include                  { properties.kind = INCLUDE;           }
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
    |                use                      { properties.kind = USE;               }
    |                where_construct          { properties.kind = WHERE;             }
    |                segment                  { properties.kind = SEGMENT;           }
    |                endsegment               { properties.kind = ENDSEGMENT;        }
    ;
blank:               BLANK ;

stlabel:             STLABEL getstlabel ;
named_label:         NAMED_LABEL        ;

module:              MODULE enable_identifier IDENTIFIER getname EOL ;

use:                 USE    enable_identifier IDENTIFIER getname enable_skipall SKIPALL ;

include:             INCLUDE     QSTRING getstring EOL {D(O("include"););} ; /* include "file.inc" */

identifiers:         IDENTIFIER
	   |         identifiers ',' IDENTIFIER ;

abstractinterface:   ABSTRACTINTERFACE  EOL     ;
contains:            CONTAINS           EOL     ;
interface:           INTERFACE          skipall ;   /* interface [name, operator(*), assignment(=) */
moduleprocedure:     MODULEPROCEDURE    enable_identifier identifiers getname EOL ;
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
		    |   NON_RECURSIVE   
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

submodule:           SUBMODULE LR getlr enable_identifier IDENTIFIER getname EOL ;

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
endfunction:         ENDFUNCTION   construct_name EOL 
	   |         ENDFUNCTION   construct_name LR EOL;  /* to accommodate preprocessors who recognize END FUNCTION MYFUNC (SOMETHING) */
endif:               ENDIF         construct_name EOL ;
endinterface:        ENDINTERFACE  skipall            ;   /* end interface [name, operator(*), assignment(=)] */
endmodule:           ENDMODULE     construct_name EOL ;
endprocedure:        ENDPROCEDURE  construct_name EOL 
	    |        ENDPROCEDURE  construct_name LR EOL;  /* to accommodate preprocessors who recognize END PROCEDURE MYPROC (SOMETHING) */
endprogram:          ENDPROGRAM    construct_name EOL 
	  |          ENDPROGRAM    construct_name LR EOL;  /* to accommodate preprocessors who recognize END PROGRAM MYPROG (SOMETHING) */
endselect:           ENDSELECT     construct_name EOL ;
endsubmodule:        ENDSUBMODULE  construct_name EOL ;
endsubroutine:       ENDSUBROUTINE construct_name EOL 
	     |       ENDSUBROUTINE construct_name LR EOL;  /* to accommodate preprocessors who recognize END SUBROUTINE MYSUB (SOMETHING) */
endteam:             ENDTEAM       lr_construct_name EOL ;
endtype:             ENDTYPE       construct_name EOL ;
endsegment:          ENDSEGMENT    EOL ;
endwhere:            ENDWHERE      construct_name EOL ;
simple_end:          END                          EOL ;
gidentifier:         IDENTIFIER
	   |         TIDENTIFIER 
	   ;

assignment:          lvalue '=' skipnoop  /* this includes '=>' */
	  |          ASSIGN I_NUMBER TO enable_identifier gidentifier EOL 
	  ;

else:                ELSE           construct_name EOL ;
elseif:              ELSEIF LR THEN construct_name EOL ;
elsewhere:           ELSEWHERE      lr_construct_name EOL ;

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

case:                CASE enable_identifier LR EOL                /* case (3)            */
    |                CASE enable_identifier LR IDENTIFIER EOL;    /* case (3) name       */
casedefault:         CASEDEFAULT       construct_name EOL    ;    /* case default [name] */
classdefault:        CLASSDEFAULT      construct_name EOL ;

classis:             CLASSIS       LR  construct_name EOL ;
typeis:              TYPEIS        LR  construct_name EOL ;

changeteam:          CHANGETEAM    LR  EOL ;

block:               BLOCK                    EOL ;
blockdata:           BLOCKDATA construct_name EOL ;
associate:           ASSOCIATE LR             EOL ;
critical:            CRITICAL                 EOL
        |            CRITICAL  LR             EOL ;
enum:                ENUM ','             skipall ;

type:                type1 ','  skipall
    |                type1 ':'  skipall
    |                type1 IDENTIFIER  skipall 
    ;
type1:               TYPE enable_identifier ;

segment:             SEGMENT enable_identifier IDENTIFIER EOL
       ;

lvalue:              gidentifier
      |              gidentifier LR
      |              lvalue '%' lvalue
      ;
construct_name:      enable_identifier empty                             /*           */
	      |      enable_identifier IDENTIFIER getname                /* name      */
	      ;
lr_construct_name:   enable_identifier empty                             /*           */
		 |   enable_identifier LR                                /* (..)      */
		 |   enable_identifier IDENTIFIER getname                /* name      */
		 |   enable_identifier LR IDENTIFIER getname             /* (..) name */
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
getstring:           {properties.stringvalue=lexer_getstring();}
	 ;
getlr:               {properties.lrvalue=lexer_getlr();}
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

propstruct parseline(Line_prep p)
{
   D(O("entering parseline"););
   lexer_set(p,IDENTIFIER);
   resetprop();
   yyparse();
   if (properties.kind != UNCLASSIFIED)
      return properties;
#ifdef USEESOPE
   lexer_set(p,ESOPE);    // enables KEYWORD+ESOPE (SEGMENT, ENDSEGMENT)
#else
   lexer_set(p,KEYWORD);  // enables KEYWORD
#endif
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
