/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <iostream>

#include "debug.h"
#include "lexer.h"
#include "line_prep.h"
#include "prop.h"

struct propstruct properties;

#line 81 "parser.cpp"

# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MODULE = 258,
    SUBFUN = 259,
    ENTRY = 260,
    SUBMODULE = 261,
    MODULESUBROUTINE = 262,
    MODULEFUNCTION = 263,
    END = 264,
    ENDSUBROUTINE = 265,
    ENDFUNCTION = 266,
    ENDPROGRAM = 267,
    ENDMODULE = 268,
    ENDSUBMODULE = 269,
    IF = 270,
    THEN = 271,
    ELSE = 272,
    ELSEIF = 273,
    ENDIF = 274,
    WHERE = 275,
    ENDWHERE = 276,
    FORALL = 277,
    ENDFORALL = 278,
    ELSEWHERE = 279,
    DO = 280,
    DOCOMMA = 281,
    DOWHILE = 282,
    DOCONCURRENT = 283,
    ENDDO = 284,
    SELECTCASE = 285,
    SELECTTYPE = 286,
    ENDSELECT = 287,
    CASE = 288,
    CASEDEFAULT = 289,
    TYPEIS = 290,
    CLASSIS = 291,
    CLASSDEFAULT = 292,
    INTERFACE = 293,
    ABSTRACTINTERFACE = 294,
    ENDINTERFACE = 295,
    CONTAINS = 296,
    BLOCK = 297,
    ENDBLOCK = 298,
    BLOCKDATA = 299,
    ENDBLOCKDATA = 300,
    ASSOCIATE = 301,
    ENDASSOCIATE = 302,
    CRITICAL = 303,
    ENDCRITICAL = 304,
    CHANGETEAM = 305,
    ENDTEAM = 306,
    ENUM = 307,
    ENDENUM = 308,
    ASSIGNMENT = 309,
    ASSIGN = 310,
    TO = 311,
    MODULEPROCEDURE = 312,
    PROCEDURE = 313,
    ENDPROCEDURE = 314,
    TIDENTIFIER = 315,
    BLANK = 316,
    CHAR = 317,
    FINDFORMAT = 318,
    UNKNOWN = 319,
    FREE = 320,
    FIXED = 321,
    UNSURE = 322,
    PROBFREE = 323,
    FINDENTFIX = 324,
    FIXFINDENTFIX = 325,
    P_ON = 326,
    P_OFF = 327,
    SCANFIXPRE = 328,
    CPP_IF = 329,
    CPP_ENDIF = 330,
    CPP_ELSE = 331,
    CPP_ELIF = 332,
    CPP = 333,
    COCO_IF = 334,
    COCO_ENDIF = 335,
    COCO_ELSE = 336,
    COCO_ELIF = 337,
    COCO = 338,
    INCLUDE = 339,
    INCLUDE_CPP = 340,
    INCLUDE_CPP_STD = 341,
    INCLUDE_COCO = 342,
    INCFILENAME = 343,
    USE = 344,
    SEGMENT = 345,
    ENDSEGMENT = 346,
    ESOPE = 347,
    IDENTIFIER = 348,
    SKIP = 349,
    SKIPALL = 350,
    SKIPNOOP = 351,
    KEYWORD = 352,
    ELEMENTAL = 353,
    IMPURE = 354,
    PURE = 355,
    RECURSIVE = 356,
    NON_RECURSIVE = 357,
    SUBROUTINE = 358,
    FUNCTION = 359,
    PROGRAM = 360,
    EOL = 361,
    NAMED_LABEL = 362,
    STLABEL = 363,
    TYPE = 364,
    ENDTYPE = 365,
    CLASS = 366,
    BASICTYPE = 367,
    TYPEC = 368,
    QSTRING = 369,
    HSTRING = 370,
    LR = 371,
    LRB = 372,
    DOTOPERATOR = 373,
    I_NUMBER = 374,
    UNCLASSIFIED = 375,
    ERROR = 376,
    OMP = 377,
    SCANOMPFIXED = 378,
    SCANOMPFREE = 379,
    LAST_TOKEN = 380
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   382

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  131
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  94
/* YYNRULES -- Number of rules.  */
#define YYNRULES  191
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  358

#define YYUNDEFTOK  2
#define YYMAXUTOK   380

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   126,     2,     2,
       2,     2,   128,     2,   127,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   130,     2,
       2,   129,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    61,    61,    63,    64,    65,    66,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   128,   130,   131,   133,
     135,   137,   139,   140,   142,   143,   144,   145,   146,   159,
     160,   163,   164,   165,   166,   168,   169,   170,   172,   173,
     174,   175,   176,   177,   178,   179,   182,   183,   184,   185,
     187,   189,   191,   192,   194,   195,   196,   199,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   230,   231,   234,   235,   236,
     238,   239,   240,   242,   243,   244,   245,   246,   248,   252,
     253,   255,   256,   258,   259,   260,   261,   263,   264,   266,
     268,   269,   270,   271,   272,   273,   275,   276,   277,   279,
     281,   284,   285,   286,   288,   289,   291,   292,   293,   294,
     296,   298,   300,   302,   304,   306,   308,   310,   312,   314,
     316,   319
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MODULE", "SUBFUN", "ENTRY", "SUBMODULE",
  "MODULESUBROUTINE", "MODULEFUNCTION", "END", "ENDSUBROUTINE",
  "ENDFUNCTION", "ENDPROGRAM", "ENDMODULE", "ENDSUBMODULE", "IF", "THEN",
  "ELSE", "ELSEIF", "ENDIF", "WHERE", "ENDWHERE", "FORALL", "ENDFORALL",
  "ELSEWHERE", "DO", "DOCOMMA", "DOWHILE", "DOCONCURRENT", "ENDDO",
  "SELECTCASE", "SELECTTYPE", "ENDSELECT", "CASE", "CASEDEFAULT", "TYPEIS",
  "CLASSIS", "CLASSDEFAULT", "INTERFACE", "ABSTRACTINTERFACE",
  "ENDINTERFACE", "CONTAINS", "BLOCK", "ENDBLOCK", "BLOCKDATA",
  "ENDBLOCKDATA", "ASSOCIATE", "ENDASSOCIATE", "CRITICAL", "ENDCRITICAL",
  "CHANGETEAM", "ENDTEAM", "ENUM", "ENDENUM", "ASSIGNMENT", "ASSIGN", "TO",
  "MODULEPROCEDURE", "PROCEDURE", "ENDPROCEDURE", "TIDENTIFIER", "BLANK",
  "CHAR", "FINDFORMAT", "UNKNOWN", "FREE", "FIXED", "UNSURE", "PROBFREE",
  "FINDENTFIX", "FIXFINDENTFIX", "P_ON", "P_OFF", "SCANFIXPRE", "CPP_IF",
  "CPP_ENDIF", "CPP_ELSE", "CPP_ELIF", "CPP", "COCO_IF", "COCO_ENDIF",
  "COCO_ELSE", "COCO_ELIF", "COCO", "INCLUDE", "INCLUDE_CPP",
  "INCLUDE_CPP_STD", "INCLUDE_COCO", "INCFILENAME", "USE", "SEGMENT",
  "ENDSEGMENT", "ESOPE", "IDENTIFIER", "SKIP", "SKIPALL", "SKIPNOOP",
  "KEYWORD", "ELEMENTAL", "IMPURE", "PURE", "RECURSIVE", "NON_RECURSIVE",
  "SUBROUTINE", "FUNCTION", "PROGRAM", "EOL", "NAMED_LABEL", "STLABEL",
  "TYPE", "ENDTYPE", "CLASS", "BASICTYPE", "TYPEC", "QSTRING", "HSTRING",
  "LR", "LRB", "DOTOPERATOR", "I_NUMBER", "UNCLASSIFIED", "ERROR", "OMP",
  "SCANOMPFIXED", "SCANOMPFREE", "LAST_TOKEN", "'%'", "','", "'*'", "'='",
  "':'", "$accept", "lline", "labels", "line", "blank", "stlabel",
  "named_label", "module", "use", "include", "identifiers",
  "abstractinterface", "contains", "interface", "moduleprocedure",
  "procedure", "program_stmt", "subroutine_stmt", "subroutine",
  "subroutine_spec", "subroutinename", "subroutineprefix",
  "subroutineprefix_spec", "function_stmt", "function", "function_spec",
  "functionname", "submodule", "intrinsic_type_spec", "kind_selector",
  "entry", "endassociate", "endblock", "endblockdata", "endcritical",
  "enddo", "endenum", "endforall", "endfunction", "endif", "endinterface",
  "endmodule", "endprocedure", "endprogram", "endselect", "endsubmodule",
  "endsubroutine", "endteam", "endtype", "endsegment", "endwhere",
  "simple_end", "gidentifier", "assignment", "else", "elseif", "elsewhere",
  "if_construct", "where_construct", "forall_construct", "do_construct",
  "do", "docomma", "selectcase", "selecttype", "case", "casedefault",
  "classdefault", "classis", "typeis", "changeteam", "block", "blockdata",
  "associate", "critical", "enum", "type", "type1", "segment", "lvalue",
  "construct_name", "lr_construct_name", "skipall", "skipnoop",
  "enable_identifier", "enable_skip", "enable_skipall", "enable_skipnoop",
  "getname", "getstlabel", "getdolabel", "getstring", "getlr", "empty", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,    37,    44,    42,    61,
      58
};
# endif

#define YYPACT_NINF -299

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-299)))

#define YYTABLE_NINF -8

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -62,  -299,  -299,    14,   272,   -91,  -299,  -299,  -299,  -299,
    -299,  -299,   -80,   -65,  -299,  -299,  -299,  -299,  -299,   -64,
    -299,   -60,  -299,   -59,  -299,   -52,  -299,  -299,  -299,  -299,
     -48,   -46,  -299,   -44,   -42,  -299,  -299,  -299,   -38,   -35,
    -299,  -299,   -55,  -299,   -31,   -30,  -299,  -299,  -299,   -33,
    -299,   -93,  -299,   -32,  -299,   -39,   -20,   -25,  -299,  -299,
    -299,  -299,  -299,   -27,  -299,  -299,   -17,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,     0,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,    -9,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,   -40,   -51,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,   -87,  -299,   -92,  -299,  -299,     3,    13,
    -299,  -299,   -85,    15,   -84,   -78,     4,     8,    93,    10,
     103,    19,    20,    21,    22,    23,    24,   -83,  -299,  -299,
      25,    26,    27,    28,  -299,    29,     5,    30,  -299,  -299,
      31,  -299,    43,  -299,  -299,  -299,  -299,    33,    34,    35,
      36,    37,  -299,    39,    41,    42,    44,  -299,  -299,    64,
      56,    58,   -77,  -299,    59,    60,  -299,   -82,  -299,    48,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,    40,
    -101,    46,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,   -51,  -299,  -299,  -299,
    -299,  -299,    51,  -299,  -299,  -299,    53,  -299,    54,  -299,
    -299,    55,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,    70,  -299,  -299,  -299,  -299,  -299,  -299,  -299,   -81,
    -299,    61,    62,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,    38,  -299,  -299,
      63,    65,  -299,    67,  -299,  -299,  -299,  -299,  -299,   -69,
    -299,  -299,  -299,    71,    50,    77,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,    79,    73,  -299,    83,  -299,  -299,
    -299,  -299,  -299,    80,  -299,  -299,    81,  -299,  -299,  -299,
     -51,    84,    85,    86,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,    91,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,    87,  -299,  -299,  -299,    94,    96,  -299,  -299,
     100,  -299,    89,  -299,  -299,  -299,  -299,  -299
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     191,    68,   187,     0,   191,     4,     5,     3,    67,     1,
     182,   182,     0,     0,   182,   182,   182,   182,   182,     0,
     182,     0,   182,     0,   182,     0,   182,   182,   182,   182,
       0,     0,   182,     0,     0,   182,   182,   182,     0,     0,
     182,   184,     0,   184,     0,     0,   182,   182,   182,     0,
     182,     0,   182,     0,   182,     0,     0,     0,   182,   182,
     182,   134,    66,     0,   182,   182,     0,   133,   182,   182,
     182,     2,    11,    50,    62,    48,     8,    19,    49,    51,
      53,    52,    57,     0,    58,    59,    44,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    65,    43,    56,   171,     9,
      22,    23,    24,    47,    63,    46,    21,     0,     0,    54,
      55,    14,    15,    17,    18,    61,    16,    12,    13,    10,
      20,    45,    60,     0,    64,     0,    86,     6,     0,     0,
     190,   132,     0,   191,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   191,   149,   150,
       0,     0,     0,     0,   184,     0,     0,     0,   182,   182,
       0,    76,     0,    74,   118,    75,   160,     0,     0,     0,
       0,     0,   163,     0,     0,     0,     0,   184,   113,     0,
       0,     0,     0,   189,     0,     0,   130,     0,   169,     0,
      84,    99,    88,    89,    90,    91,    92,    83,    98,     0,
     102,     0,   182,    82,    87,   182,    97,    93,   172,   146,
     188,   184,   184,   184,   184,   184,     0,   185,   186,   184,
     182,   126,     0,   186,   174,   115,     0,   122,     0,   119,
     125,     0,   137,   182,   117,   141,   131,   142,   114,   139,
     186,   177,   176,   147,   148,   112,   151,   152,   124,     0,
     155,     0,     0,   156,   180,   109,   161,   110,   162,   108,
     164,   111,   159,   128,   165,   182,    72,   186,   186,   120,
       0,     0,   186,     0,   186,    80,   129,    95,   106,     0,
     103,    94,   183,     0,     0,     0,   184,   144,   145,   168,
     166,   167,   173,   135,     0,     0,   107,     0,   127,   175,
     116,   123,   140,     0,   178,   186,     0,   153,   158,   157,
       0,     0,     0,     0,   121,    71,   184,   170,   183,   105,
     104,     0,   186,   183,   186,   143,   181,    69,   186,   138,
     179,   154,     0,    73,    77,    78,     0,     0,    81,    85,
       0,   100,     0,   136,    70,    79,    96,   101
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -299,  -299,  -299,  -299,  -299,  -299,   191,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -114,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,   -29,
      45,   144,   -41,  -299,   -10,  -298,  -127,  -299,  -160,  -299,
    -299,  -299,  -299,     1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    71,    72,     5,     6,    73,    74,    75,
     277,    76,    77,    78,    79,    80,    81,    82,   212,   213,
     292,    83,   214,    84,   215,   216,   294,    85,   217,   290,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     142,   156,   171,   303,   143,   331,   172,   304,   305,     8,
     296,   281,   230,     7
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     138,   139,   174,   221,   222,   136,   223,   200,   201,    61,
     250,   284,   316,   182,     9,   288,     1,   157,   158,   159,
      61,   231,   235,   183,   285,   317,   166,   289,   237,   279,
     347,   232,   236,   251,   226,   350,   140,   227,   238,   280,
     224,   141,    67,   225,   157,     1,     2,   329,   190,   191,
     330,   173,   148,    67,   194,   195,   150,   152,   197,   198,
     144,   145,   146,   147,   154,   149,   219,   151,   160,   153,
     161,   155,   163,   309,   164,   175,   176,   162,   168,   220,
     165,   169,   167,   180,   185,   170,   188,   193,   187,   196,
     314,   177,   178,   179,   189,   181,   228,   184,   202,   203,
     204,   205,   206,   207,   208,   192,   229,   218,   233,   241,
     239,   209,   210,   211,   240,   199,   242,   322,   323,   243,
     275,   259,   326,   257,   328,   244,   245,   246,   247,   248,
     249,   253,   254,   255,   256,   258,   260,   263,   264,   265,
     266,   267,   268,   269,   234,   270,   274,   271,   272,   276,
     273,   278,   282,   283,   286,   340,   287,   308,   252,   310,
     311,   312,   291,   315,   332,   321,   333,   318,   319,   324,
     334,   325,   349,   327,   351,   336,   338,   343,   352,   337,
     297,   298,   299,   300,   301,   348,   339,   341,   306,   354,
     355,   344,   345,   353,   356,   357,   137,   302,   186,   346,
       0,     0,   293,     0,     0,   295,   342,     0,     0,     0,
       0,     0,     0,   261,   262,     0,     0,     0,     0,     0,
     307,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   335,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   320,     0,     0,     0,     0,
       0,     0,    -7,     0,     0,    10,     0,    11,    12,     0,
       0,    13,    14,    15,    16,    17,    18,    19,   313,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,     0,    57,     0,    58,
      59,    60,    61,    62,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,     0,     0,     0,
       0,    64,    65,    66,     0,    67,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    68,     0,     0,
       0,    69,    70
};

static const yytype_int16 yycheck[] =
{
      10,    11,    43,   117,   118,     4,    93,     7,     8,    60,
      93,    93,    93,   106,     0,   116,   107,    27,    28,    29,
      60,   106,   106,   116,   106,   106,    36,   128,   106,   106,
     328,   116,   116,   116,   126,   333,   116,   129,   116,   116,
     127,   106,    93,   130,    54,   107,   108,   116,    58,    59,
     119,   106,   116,    93,    64,    65,   116,   116,    68,    69,
      15,    16,    17,    18,   116,    20,   106,    22,   116,    24,
     116,    26,   116,   233,   116,   106,   106,    32,   116,   119,
      35,   116,    37,   116,   116,    40,   106,   114,   127,   106,
     250,    46,    47,    48,   119,    50,    93,    52,    98,    99,
     100,   101,   102,   103,   104,    60,    93,   116,    93,    16,
     106,   111,   112,   113,   106,    70,   106,   277,   278,    16,
      56,   116,   282,   164,   284,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,    95,   106,
     106,   106,   106,   106,   143,   106,   187,   106,   106,    93,
     106,    93,    93,    93,   106,   315,   116,   106,   157,   106,
     106,   106,   116,    93,    93,   127,   116,   106,   106,   106,
      93,   106,   332,   106,   334,    96,    93,    93,   338,   106,
     221,   222,   223,   224,   225,    94,   106,   106,   229,    95,
      94,   106,   106,   106,    94,   106,     5,   226,    54,   326,
      -1,    -1,   212,    -1,    -1,   215,   320,    -1,    -1,    -1,
      -1,    -1,    -1,   168,   169,    -1,    -1,    -1,    -1,    -1,
     230,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   275,    -1,    -1,    -1,    -1,
      -1,    -1,     0,    -1,    -1,     3,    -1,     5,     6,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,   243,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    -1,    55,    -1,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      -1,    89,    90,    91,    -1,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,
      -1,   109,   110
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   107,   108,   132,   133,   136,   137,   224,   220,     0,
       3,     5,     6,     9,    10,    11,    12,    13,    14,    15,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    55,    57,    58,
      59,    60,    61,    84,    89,    90,    91,    93,   105,   109,
     110,   134,   135,   138,   139,   140,   142,   143,   144,   145,
     146,   147,   148,   152,   154,   158,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   224,   137,   215,   215,
     116,   106,   211,   215,   211,   211,   211,   211,   116,   211,
     116,   211,   116,   211,   116,   211,   212,   215,   215,   215,
     116,   116,   211,   116,   116,   211,   215,   211,   116,   116,
     211,   213,   217,   106,   213,   106,   106,   211,   211,   211,
     116,   211,   106,   116,   211,   116,   212,   127,   106,   119,
     215,   215,   211,   114,   215,   215,   106,   215,   215,   211,
       7,     8,    98,    99,   100,   101,   102,   103,   104,   111,
     112,   113,   149,   150,   153,   155,   156,   159,   116,   106,
     119,   183,   183,    93,   127,   130,   126,   129,    93,    93,
     223,   106,   116,    93,   224,   106,   116,   106,   116,   106,
     106,    16,   106,    16,   106,   106,   106,   106,   106,   106,
      93,   116,   224,   106,   106,   106,   106,   213,   106,   116,
     106,   211,   211,   106,    95,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   213,    56,    93,   141,    93,   106,
     116,   222,    93,    93,    93,   106,   106,   116,   116,   128,
     160,   116,   151,   215,   157,   215,   221,   213,   213,   213,
     213,   213,   210,   214,   218,   219,   213,   215,   106,   219,
     106,   106,   106,   211,   219,    93,    93,   106,   106,   106,
     215,   127,   219,   219,   106,   106,   219,   106,   219,   116,
     119,   216,    93,   116,    93,   213,    96,   106,    93,   106,
     219,   106,   183,    93,   106,   106,   217,   216,    94,   219,
     216,   219,   219,   106,    95,    94,    94,   106
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   131,   132,   133,   133,   133,   133,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   135,   136,   137,   138,
     139,   140,   141,   141,   142,   143,   144,   145,   146,   147,
     147,   148,   149,   150,   150,   151,   152,   152,   153,   153,
     153,   153,   153,   153,   153,   153,   154,   155,   156,   156,
     157,   158,   159,   159,   160,   160,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   169,   170,   171,   172,
     173,   173,   174,   174,   175,   176,   177,   177,   178,   179,
     180,   181,   182,   183,   183,   184,   184,   185,   186,   187,
     188,   189,   190,   191,   191,   191,   191,   191,   191,   192,
     193,   194,   195,   196,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   205,   206,   207,   207,   207,   208,
     209,   210,   210,   210,   211,   211,   212,   212,   212,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     2,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     5,
       6,     4,     1,     3,     2,     2,     2,     5,     5,     6,
       3,     5,     1,     1,     1,     3,     1,     2,     1,     1,
       1,     1,     1,     1,     2,     2,     6,     1,     1,     1,
       3,     7,     1,     2,     2,     2,     1,     4,     3,     3,
       3,     3,     3,     2,     3,     3,     4,     3,     2,     3,
       3,     4,     3,     4,     3,     3,     3,     4,     3,     3,
       2,     3,     2,     1,     1,     3,     6,     3,     5,     3,
       4,     3,     3,     4,     3,     3,     2,     3,     3,     2,
       2,     3,     3,     4,     5,     3,     3,     4,     4,     3,
       2,     3,     3,     2,     3,     3,     3,     3,     3,     2,
       4,     1,     2,     3,     2,     3,     2,     2,     3,     4,
       2,     2,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 8:
#line 69 "parser.y"
    { properties.kind = ABSTRACTINTERFACE; }
#line 1647 "parser.cpp"
    break;

  case 9:
#line 70 "parser.y"
    { properties.kind = ASSIGNMENT;        }
#line 1653 "parser.cpp"
    break;

  case 10:
#line 71 "parser.y"
    { properties.kind = ASSOCIATE;         }
#line 1659 "parser.cpp"
    break;

  case 11:
#line 72 "parser.y"
    { properties.kind = BLANK;             }
#line 1665 "parser.cpp"
    break;

  case 12:
#line 73 "parser.y"
    { properties.kind = BLOCK;             }
#line 1671 "parser.cpp"
    break;

  case 13:
#line 74 "parser.y"
    { properties.kind = BLOCKDATA;         }
#line 1677 "parser.cpp"
    break;

  case 14:
#line 75 "parser.y"
    { properties.kind = CASE;              }
#line 1683 "parser.cpp"
    break;

  case 15:
#line 76 "parser.y"
    { properties.kind = CASEDEFAULT;       }
#line 1689 "parser.cpp"
    break;

  case 16:
#line 77 "parser.y"
    { properties.kind = CHANGETEAM;        }
#line 1695 "parser.cpp"
    break;

  case 17:
#line 78 "parser.y"
    { properties.kind = CLASSDEFAULT;      }
#line 1701 "parser.cpp"
    break;

  case 18:
#line 79 "parser.y"
    { properties.kind = CLASSIS;           }
#line 1707 "parser.cpp"
    break;

  case 19:
#line 80 "parser.y"
    { properties.kind = CONTAINS;          }
#line 1713 "parser.cpp"
    break;

  case 20:
#line 81 "parser.y"
    { properties.kind = CRITICAL;          }
#line 1719 "parser.cpp"
    break;

  case 21:
#line 82 "parser.y"
    { properties.kind = DO;                }
#line 1725 "parser.cpp"
    break;

  case 22:
#line 83 "parser.y"
    { properties.kind = ELSE;              }
#line 1731 "parser.cpp"
    break;

  case 23:
#line 84 "parser.y"
    { properties.kind = ELSEIF;            }
#line 1737 "parser.cpp"
    break;

  case 24:
#line 85 "parser.y"
    { properties.kind = ELSEWHERE;         }
#line 1743 "parser.cpp"
    break;

  case 25:
#line 86 "parser.y"
    { properties.kind = ENDASSOCIATE;      }
#line 1749 "parser.cpp"
    break;

  case 26:
#line 87 "parser.y"
    { properties.kind = ENDBLOCK;          }
#line 1755 "parser.cpp"
    break;

  case 27:
#line 88 "parser.y"
    { properties.kind = ENDBLOCKDATA;      }
#line 1761 "parser.cpp"
    break;

  case 28:
#line 89 "parser.y"
    { properties.kind = ENDCRITICAL;       }
#line 1767 "parser.cpp"
    break;

  case 29:
#line 90 "parser.y"
    { properties.kind = ENDDO;             }
#line 1773 "parser.cpp"
    break;

  case 30:
#line 91 "parser.y"
    { properties.kind = ENDENUM;           }
#line 1779 "parser.cpp"
    break;

  case 31:
#line 92 "parser.y"
    { properties.kind = ENDFORALL;         }
#line 1785 "parser.cpp"
    break;

  case 32:
#line 93 "parser.y"
    { properties.kind = ENDFUNCTION;       }
#line 1791 "parser.cpp"
    break;

  case 33:
#line 94 "parser.y"
    { properties.kind = ENDIF;             }
#line 1797 "parser.cpp"
    break;

  case 34:
#line 95 "parser.y"
    { properties.kind = ENDINTERFACE;      }
#line 1803 "parser.cpp"
    break;

  case 35:
#line 96 "parser.y"
    { properties.kind = ENDMODULE;         }
#line 1809 "parser.cpp"
    break;

  case 36:
#line 97 "parser.y"
    { properties.kind = ENDPROCEDURE;      }
#line 1815 "parser.cpp"
    break;

  case 37:
#line 98 "parser.y"
    { properties.kind = ENDPROGRAM;        }
#line 1821 "parser.cpp"
    break;

  case 38:
#line 99 "parser.y"
    { properties.kind = ENDSELECT;         }
#line 1827 "parser.cpp"
    break;

  case 39:
#line 100 "parser.y"
    { properties.kind = ENDSUBMODULE;      }
#line 1833 "parser.cpp"
    break;

  case 40:
#line 101 "parser.y"
    { properties.kind = ENDSUBROUTINE;     }
#line 1839 "parser.cpp"
    break;

  case 41:
#line 102 "parser.y"
    { properties.kind = ENDTEAM;           }
#line 1845 "parser.cpp"
    break;

  case 42:
#line 103 "parser.y"
    { properties.kind = ENDTYPE;           }
#line 1851 "parser.cpp"
    break;

  case 43:
#line 104 "parser.y"
    { properties.kind = ENDWHERE;          }
#line 1857 "parser.cpp"
    break;

  case 44:
#line 105 "parser.y"
    { properties.kind = ENTRY;             }
#line 1863 "parser.cpp"
    break;

  case 45:
#line 106 "parser.y"
    { properties.kind = ENUM;              }
#line 1869 "parser.cpp"
    break;

  case 46:
#line 107 "parser.y"
    { properties.kind = FORALL;            }
#line 1875 "parser.cpp"
    break;

  case 47:
#line 108 "parser.y"
    { properties.kind = IF;                }
#line 1881 "parser.cpp"
    break;

  case 48:
#line 109 "parser.y"
    { properties.kind = INCLUDE;           }
#line 1887 "parser.cpp"
    break;

  case 49:
#line 110 "parser.y"
    { properties.kind = INTERFACE;         }
#line 1893 "parser.cpp"
    break;

  case 50:
#line 111 "parser.y"
    { properties.kind = MODULE;            }
#line 1899 "parser.cpp"
    break;

  case 51:
#line 112 "parser.y"
    { properties.kind = PROCEDURE;         }
#line 1905 "parser.cpp"
    break;

  case 52:
#line 113 "parser.y"
    { properties.kind = PROGRAM;           }
#line 1911 "parser.cpp"
    break;

  case 53:
#line 114 "parser.y"
    { properties.kind = PROCEDURE;         }
#line 1917 "parser.cpp"
    break;

  case 54:
#line 115 "parser.y"
    { properties.kind = SELECTCASE;        }
#line 1923 "parser.cpp"
    break;

  case 55:
#line 116 "parser.y"
    { properties.kind = SELECTTYPE;        }
#line 1929 "parser.cpp"
    break;

  case 56:
#line 117 "parser.y"
    { properties.kind = END;               }
#line 1935 "parser.cpp"
    break;

  case 57:
#line 118 "parser.y"
    { properties.kind = SUBROUTINE;        }
#line 1941 "parser.cpp"
    break;

  case 58:
#line 119 "parser.y"
    { properties.kind = FUNCTION;          }
#line 1947 "parser.cpp"
    break;

  case 59:
#line 120 "parser.y"
    { properties.kind = SUBMODULE;         }
#line 1953 "parser.cpp"
    break;

  case 60:
#line 121 "parser.y"
    { properties.kind = TYPE;              }
#line 1959 "parser.cpp"
    break;

  case 61:
#line 122 "parser.y"
    { properties.kind = TYPEIS;            }
#line 1965 "parser.cpp"
    break;

  case 62:
#line 123 "parser.y"
    { properties.kind = USE;               }
#line 1971 "parser.cpp"
    break;

  case 63:
#line 124 "parser.y"
    { properties.kind = WHERE;             }
#line 1977 "parser.cpp"
    break;

  case 64:
#line 125 "parser.y"
    { properties.kind = SEGMENT;           }
#line 1983 "parser.cpp"
    break;

  case 65:
#line 126 "parser.y"
    { properties.kind = ENDSEGMENT;        }
#line 1989 "parser.cpp"
    break;

  case 71:
#line 137 "parser.y"
    {D(O("include"););}
#line 1995 "parser.cpp"
    break;

  case 182:
#line 300 "parser.y"
    {lexer_enable(IDENTIFIER);}
#line 2001 "parser.cpp"
    break;

  case 183:
#line 302 "parser.y"
    {lexer_enable(SKIP);}
#line 2007 "parser.cpp"
    break;

  case 184:
#line 304 "parser.y"
    {lexer_enable(SKIPALL);}
#line 2013 "parser.cpp"
    break;

  case 185:
#line 306 "parser.y"
    {lexer_enable(SKIPNOOP);}
#line 2019 "parser.cpp"
    break;

  case 186:
#line 308 "parser.y"
    {properties.name=lexer_getname();}
#line 2025 "parser.cpp"
    break;

  case 187:
#line 310 "parser.y"
    {properties.label=lexer_getstlabel();}
#line 2031 "parser.cpp"
    break;

  case 188:
#line 312 "parser.y"
    {properties.dolabel=lexer_geti_number();}
#line 2037 "parser.cpp"
    break;

  case 189:
#line 314 "parser.y"
    {properties.stringvalue=lexer_getstring();}
#line 2043 "parser.cpp"
    break;

  case 190:
#line 316 "parser.y"
    {properties.lrvalue=lexer_getlr();}
#line 2049 "parser.cpp"
    break;


#line 2053 "parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 321 "parser.y"


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
