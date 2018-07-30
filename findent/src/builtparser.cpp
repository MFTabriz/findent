/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

// $Id: parser.y 307 2018-07-20 15:03:22Z willem_vermin $
#include <iostream>

#include "debug.h"
#include "lexer.h"
#include "line_prep.h"
#include "prop.h"

struct propstruct properties;

#line 78 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
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
    ENUM = 305,
    ENDENUM = 306,
    ASSIGNMENT = 307,
    ASSIGN = 308,
    TO = 309,
    MODULEPROCEDURE = 310,
    PROCEDURE = 311,
    ENDPROCEDURE = 312,
    TIDENTIFIER = 313,
    BLANK = 314,
    FINDFORMAT = 315,
    UNKNOWN = 316,
    FREE = 317,
    FIXED = 318,
    UNSURE = 319,
    PROBFREE = 320,
    FINDENTFIX = 321,
    FIXFINDENTFIX = 322,
    SCANFIXPRE = 323,
    CPP_IF = 324,
    CPP_ENDIF = 325,
    CPP_ELSE = 326,
    CPP_ELIF = 327,
    CPP = 328,
    COCO_IF = 329,
    COCO_ENDIF = 330,
    COCO_ELSE = 331,
    COCO_ELIF = 332,
    COCO = 333,
    IDENTIFIER = 334,
    SKIP = 335,
    SKIPALL = 336,
    SKIPNOOP = 337,
    KEYWORD = 338,
    ELEMENTAL = 339,
    IMPURE = 340,
    PURE = 341,
    RECURSIVE = 342,
    SUBROUTINE = 343,
    FUNCTION = 344,
    PROGRAM = 345,
    EOL = 346,
    NAMED_LABEL = 347,
    STLABEL = 348,
    TYPE = 349,
    ENDTYPE = 350,
    CLASS = 351,
    BASICTYPE = 352,
    TYPEC = 353,
    QSTRING = 354,
    HSTRING = 355,
    LR = 356,
    LRB = 357,
    DOTOPERATOR = 358,
    I_NUMBER = 359,
    UNCLASSIFIED = 360,
    ERROR = 361,
    LAST_TOKEN = 362
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

/* Copy the second part of user declarations.  */

#line 237 "parser.cpp" /* yacc.c:358  */

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
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
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
#  define YYSIZE_T unsigned int
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

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYLAST   321

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  113
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  84
/* YYNRULES -- Number of rules.  */
#define YYNRULES  165
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  303

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   362

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   108,     2,     2,
       2,     2,   109,     2,   111,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   112,     2,
       2,   110,     2,     2,     2,     2,     2,     2,     2,     2,
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
     105,   106,   107
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    56,    56,    58,    59,    60,    61,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     117,   119,   120,   122,   124,   125,   126,   127,   128,   141,
     142,   145,   146,   147,   148,   150,   151,   152,   154,   155,
     156,   157,   158,   159,   160,   163,   164,   165,   166,   168,
     170,   172,   173,   175,   176,   177,   180,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   205,   206,
     209,   210,   211,   212,   215,   216,   217,   219,   220,   221,
     222,   223,   225,   229,   230,   232,   233,   235,   236,   237,
     238,   239,   242,   243,   244,   245,   246,   248,   249,   250,
     252,   254,   255,   256,   258,   259,   261,   263,   265,   267,
     269,   271,   273,   275,   277,   279
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
  "ENUM", "ENDENUM", "ASSIGNMENT", "ASSIGN", "TO", "MODULEPROCEDURE",
  "PROCEDURE", "ENDPROCEDURE", "TIDENTIFIER", "BLANK", "FINDFORMAT",
  "UNKNOWN", "FREE", "FIXED", "UNSURE", "PROBFREE", "FINDENTFIX",
  "FIXFINDENTFIX", "SCANFIXPRE", "CPP_IF", "CPP_ENDIF", "CPP_ELSE",
  "CPP_ELIF", "CPP", "COCO_IF", "COCO_ENDIF", "COCO_ELSE", "COCO_ELIF",
  "COCO", "IDENTIFIER", "SKIP", "SKIPALL", "SKIPNOOP", "KEYWORD",
  "ELEMENTAL", "IMPURE", "PURE", "RECURSIVE", "SUBROUTINE", "FUNCTION",
  "PROGRAM", "EOL", "NAMED_LABEL", "STLABEL", "TYPE", "ENDTYPE", "CLASS",
  "BASICTYPE", "TYPEC", "QSTRING", "HSTRING", "LR", "LRB", "DOTOPERATOR",
  "I_NUMBER", "UNCLASSIFIED", "ERROR", "LAST_TOKEN", "'%'", "'*'", "'='",
  "','", "':'", "$accept", "lline", "labels", "line", "blank", "stlabel",
  "named_label", "module", "abstractinterface", "contains", "interface",
  "moduleprocedure", "procedure", "program_stmt", "subroutine_stmt",
  "subroutine", "subroutine_spec", "subroutinename", "subroutineprefix",
  "subroutineprefix_spec", "function_stmt", "function", "function_spec",
  "functionname", "submodule", "intrinsic_type_spec", "kind_selector",
  "entry", "endassociate", "endblock", "endblockdata", "endcritical",
  "enddo", "endenum", "endforall", "endfunction", "endif", "endinterface",
  "endmodule", "endprocedure", "endprogram", "endselect", "endsubmodule",
  "endsubroutine", "endtype", "endwhere", "simple_end", "gidentifier",
  "assignment", "else", "elseif", "elsewhere", "if_construct",
  "where_construct", "forall_construct", "do_construct", "do", "docomma",
  "selectcase", "selecttype", "case", "casedefault", "classdefault",
  "classis", "typeis", "block", "blockdata", "associate", "critical",
  "enum", "type", "type1", "lvalue", "construct_name", "skipall",
  "skipnoop", "enable_identifier", "enable_skip", "enable_skipall",
  "enable_skipnoop", "getname", "getstlabel", "getdolabel", "empty", YY_NULLPTR
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
     355,   356,   357,   358,   359,   360,   361,   362,    37,    42,
      61,    44,    58
};
# endif

#define YYPACT_NINF -258

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-258)))

#define YYTABLE_NINF -8

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -42,  -258,  -258,    20,   226,   -61,  -258,  -258,  -258,  -258,
    -258,  -258,   -59,   -52,  -258,  -258,  -258,  -258,  -258,   -56,
    -258,   -44,  -258,   -39,  -258,   -38,  -258,   -37,  -258,  -258,
     -36,   -34,  -258,   -33,   -32,  -258,   -27,  -258,   -26,   -25,
    -258,  -258,   -14,  -258,   -13,   -12,  -258,  -258,  -258,   -21,
    -258,    -9,  -258,   -30,    -8,   -55,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,     2,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,   -17,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,   -43,   -46,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,   -68,   -94,  -258,  -258,   -20,     6,  -258,  -258,
       1,    14,     4,    10,    11,    12,    78,    13,    81,    15,
      16,    18,    21,    22,  -258,    23,  -258,  -258,    24,    25,
      28,    30,  -258,  -258,    43,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,    34,    35,    36,    37,    38,
    -258,    39,  -258,  -258,    51,    32,    52,    41,   -62,  -258,
      42,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,    40,
     -88,    44,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,   -46,  -258,  -258,  -258,
      56,  -258,  -258,  -258,  -258,  -258,  -258,  -258,    45,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,    47,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,   -63,  -258,  -258,  -258,    60,    46,    61,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,    62,    55,
    -258,  -258,  -258,  -258,    57,  -258,   -46,    58,    59,  -258,
    -258,  -258,    63,  -258,  -258,  -258,  -258,  -258,  -258,    64,
    -258,    65,  -258,  -258,    71,  -258,  -258,    73,  -258,  -258,
    -258,  -258,  -258
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     165,    62,   163,     0,   165,     4,     5,     3,    61,     1,
     158,   158,     0,     0,   158,   158,   158,   158,   158,     0,
     158,     0,   158,     0,   158,     0,   158,   158,   158,   158,
       0,     0,   158,     0,     0,   160,     0,   160,     0,     0,
     160,   160,     0,   160,     0,     0,   158,   158,   158,     0,
     158,     0,   158,     0,     0,     0,   158,   158,   158,   117,
      60,   116,   158,   158,   158,     2,    11,    47,     8,    18,
      46,    48,    50,    49,    54,     0,    55,    56,    42,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    53,   151,     9,
      21,    22,    23,    45,    59,    44,    20,     0,     0,    51,
      52,    14,    15,    16,    17,    58,    12,    13,    10,    19,
      43,    57,     0,     0,    76,     6,     0,     0,   158,   115,
       0,   165,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   158,     0,   133,   134,     0,     0,
       0,     0,   160,   110,     0,   160,   138,   160,   160,   139,
      66,    64,   106,    65,   142,     0,     0,     0,     0,     0,
     145,     0,   160,   102,     0,     0,     0,     0,     0,   150,
       0,    74,    88,    78,    79,    80,    81,    73,    87,     0,
      91,     0,   158,    72,    77,   158,    86,    82,   152,   130,
     164,   160,   160,   160,   160,   160,     0,   161,   162,   160,
       0,   112,   162,   154,   104,   109,   107,   111,     0,   120,
     158,   105,   125,   114,   126,   103,     0,   123,   131,   132,
     101,   135,   136,   156,   137,   141,   140,    98,   143,    99,
     144,    97,   100,   146,   158,   162,   162,   108,   162,    70,
     113,    84,    95,     0,    92,    83,   159,     0,     0,     0,
     160,   128,   129,   149,   147,   148,   153,   118,     0,     0,
      96,   162,   155,   124,     0,   122,     0,     0,     0,   159,
      94,    93,     0,   162,   159,   162,   127,   157,    63,     0,
     121,     0,    67,    68,     0,    71,    75,     0,    89,    90,
     119,    69,    85
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -258,  -258,  -258,  -258,  -258,  -258,   137,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -104,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,   -49,     8,   -35,  -258,   -10,  -257,  -258,  -258,
    -175,  -258,  -258,     3
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    65,    66,     5,     6,    67,    68,    69,
      70,    71,    72,    73,    74,   192,   193,   256,    75,   194,
      76,   195,   196,   258,    77,   197,   254,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   130,   153,   267,   131,   282,   154,   268,
     269,     8,   260,     7
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     126,   127,   156,   201,   202,   159,   160,   124,   162,   181,
     182,   203,    59,   252,   206,    59,   207,   248,   146,   147,
       9,   253,   294,   132,   133,   134,   135,   297,   137,   249,
     139,     1,   141,    61,   143,   145,    61,   272,   280,   129,
     150,   281,   128,   204,   205,   136,   175,   176,   199,   174,
       1,     2,   178,   179,   165,   166,   167,   138,   169,   208,
     171,   200,   140,   142,   144,   148,   177,   149,   151,   152,
     277,   278,   180,   279,   155,   157,   158,   161,   163,   164,
     168,   172,   170,   173,   198,   209,   183,   184,   185,   186,
     187,   188,   211,   212,   218,   214,   289,   220,   189,   190,
     191,   215,   216,   217,   219,   244,   221,   222,   296,   223,
     298,   245,   224,   225,   227,   228,   229,   232,   210,   230,
     234,   231,   235,   236,   233,   237,   238,   239,   240,   241,
     242,   246,   247,   250,   213,   271,   273,   243,   275,   283,
     285,   251,   125,   295,   287,   255,   288,   284,   290,   292,
     293,   301,   226,   302,     0,   299,   300,   266,     0,     0,
       0,     0,     0,     0,     0,     0,   261,   262,   263,   264,
     265,     0,   291,     0,   270,     0,     0,     0,     0,     0,
       0,     0,   257,     0,     0,   259,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   286,    -7,     0,   274,    10,
       0,    11,    12,     0,   276,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,     0,    55,
       0,    56,    57,    58,    59,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    62,     0,     0,     0,
      63,    64
};

static const yytype_int16 yycheck[] =
{
      10,    11,    37,   107,   108,    40,    41,     4,    43,     7,
       8,    79,    58,   101,   108,    58,   110,    79,    28,    29,
       0,   109,   279,    15,    16,    17,    18,   284,    20,    91,
      22,    92,    24,    79,    26,    27,    79,   212,   101,    91,
      32,   104,   101,   111,   112,   101,    56,    57,    91,   104,
      92,    93,    62,    63,    46,    47,    48,   101,    50,    79,
      52,   104,   101,   101,   101,   101,    58,   101,   101,   101,
     245,   246,    64,   248,   101,   101,   101,    91,    91,    91,
     101,   111,    91,    91,   101,    79,    84,    85,    86,    87,
      88,    89,    91,    79,    16,    91,   271,    16,    96,    97,
      98,    91,    91,    91,    91,    54,    91,    91,   283,    91,
     285,    79,    91,    91,    91,    91,    91,   152,   128,    91,
     155,    91,   157,   158,    81,    91,    91,    91,    91,    91,
      91,    79,    91,    91,   131,    79,    91,   172,    91,    79,
      79,   101,     5,    80,    82,   101,    91,   101,    91,    91,
      91,    80,   144,    80,    -1,    91,    91,   206,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   201,   202,   203,   204,
     205,    -1,   276,    -1,   209,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   192,    -1,    -1,   195,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   260,     0,    -1,   220,     3,
      -1,     5,     6,    -1,   244,     9,    10,    11,    12,    13,
      14,    15,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    -1,    53,
      -1,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,
      94,    95
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    92,    93,   114,   115,   118,   119,   196,   194,     0,
       3,     5,     6,     9,    10,    11,    12,    13,    14,    15,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    53,    55,    56,    57,    58,
      59,    79,    90,    94,    95,   116,   117,   120,   121,   122,
     123,   124,   125,   126,   127,   131,   133,   137,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   196,   119,   189,   189,   101,    91,
     186,   189,   186,   186,   186,   186,   101,   186,   101,   186,
     101,   186,   101,   186,   101,   186,   189,   189,   101,   101,
     186,   101,   101,   187,   191,   101,   187,   101,   101,   187,
     187,    91,   187,    91,    91,   186,   186,   186,   101,   186,
      91,   186,   111,    91,   104,   189,   189,   186,   189,   189,
     186,     7,     8,    84,    85,    86,    87,    88,    89,    96,
      97,    98,   128,   129,   132,   134,   135,   138,   101,    91,
     104,   160,   160,    79,   111,   112,   108,   110,    79,    79,
     189,    91,    79,   196,    91,    91,    91,    91,    16,    91,
      16,    91,    91,    91,    91,    91,   186,    91,    91,    91,
      91,    91,   187,    81,   187,   187,   187,    91,    91,    91,
      91,    91,    91,   187,    54,    79,    79,    91,    79,    91,
      91,   101,   101,   109,   139,   101,   130,   189,   136,   189,
     195,   187,   187,   187,   187,   187,   185,   188,   192,   193,
     187,    79,   193,    91,   186,    91,   189,   193,   193,   193,
     101,   104,   190,    79,   101,    79,   187,    82,    91,   193,
      91,   160,    91,    91,   190,    80,   193,   190,   193,    91,
      91,    80,    80
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   113,   114,   115,   115,   115,   115,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     126,   127,   128,   129,   129,   130,   131,   131,   132,   132,
     132,   132,   132,   132,   132,   133,   134,   135,   135,   136,
     137,   138,   138,   139,   139,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   160,   161,   161,
     162,   163,   164,   164,   165,   166,   167,   168,   168,   168,
     168,   168,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   183,   183,
     184,   185,   185,   185,   186,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196
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
       1,     2,     1,     5,     2,     2,     2,     5,     5,     6,
       3,     5,     1,     1,     1,     3,     1,     2,     1,     1,
       1,     1,     1,     2,     2,     6,     1,     1,     1,     3,
       6,     1,     2,     2,     2,     1,     4,     3,     3,     3,
       3,     3,     2,     3,     3,     3,     2,     3,     3,     3,
       2,     3,     3,     3,     3,     2,     1,     1,     3,     6,
       3,     5,     4,     3,     4,     3,     3,     4,     3,     3,
       2,     3,     3,     2,     2,     3,     3,     3,     2,     2,
       3,     3,     2,     3,     3,     2,     3,     3,     3,     3,
       2,     1,     2,     3,     2,     3,     2,     2,     0,     0,
       0,     0,     0,     0,     0,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
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
  unsigned long int yylno = yyrline[yyrule];
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
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
            /* Fall through.  */
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

  return yystpcpy (yyres, yystr) - yyres;
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
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
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
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
| yyreduce -- Do a reduction.  |
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
#line 64 "parser.y" /* yacc.c:1646  */
    { properties.kind = ABSTRACTINTERFACE; }
#line 1576 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 65 "parser.y" /* yacc.c:1646  */
    { properties.kind = ASSIGNMENT;        }
#line 1582 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 66 "parser.y" /* yacc.c:1646  */
    { properties.kind = ASSOCIATE;         }
#line 1588 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 67 "parser.y" /* yacc.c:1646  */
    { properties.kind = BLANK;             }
#line 1594 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 68 "parser.y" /* yacc.c:1646  */
    { properties.kind = BLOCK;             }
#line 1600 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 69 "parser.y" /* yacc.c:1646  */
    { properties.kind = BLOCKDATA;         }
#line 1606 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 70 "parser.y" /* yacc.c:1646  */
    { properties.kind = CASE;              }
#line 1612 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 71 "parser.y" /* yacc.c:1646  */
    { properties.kind = CASEDEFAULT;       }
#line 1618 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 72 "parser.y" /* yacc.c:1646  */
    { properties.kind = CLASSDEFAULT;      }
#line 1624 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 73 "parser.y" /* yacc.c:1646  */
    { properties.kind = CLASSIS;           }
#line 1630 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 74 "parser.y" /* yacc.c:1646  */
    { properties.kind = CONTAINS;          }
#line 1636 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 75 "parser.y" /* yacc.c:1646  */
    { properties.kind = CRITICAL;          }
#line 1642 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 76 "parser.y" /* yacc.c:1646  */
    { properties.kind = DO;                }
#line 1648 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 77 "parser.y" /* yacc.c:1646  */
    { properties.kind = ELSE;              }
#line 1654 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 78 "parser.y" /* yacc.c:1646  */
    { properties.kind = ELSEIF;            }
#line 1660 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 79 "parser.y" /* yacc.c:1646  */
    { properties.kind = ELSEWHERE;         }
#line 1666 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 80 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDASSOCIATE;      }
#line 1672 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 81 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDBLOCK;          }
#line 1678 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 82 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDBLOCKDATA;      }
#line 1684 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 83 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDCRITICAL;       }
#line 1690 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 84 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDDO;             }
#line 1696 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 85 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDENUM;           }
#line 1702 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 86 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDFORALL;         }
#line 1708 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 87 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDFUNCTION;       }
#line 1714 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 88 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDIF;             }
#line 1720 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 89 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDINTERFACE;      }
#line 1726 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 90 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDMODULE;         }
#line 1732 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 91 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDPROCEDURE;      }
#line 1738 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 92 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDPROGRAM;        }
#line 1744 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 93 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDSELECT;         }
#line 1750 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 94 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDSUBMODULE;      }
#line 1756 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 95 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDSUBROUTINE;     }
#line 1762 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 96 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDTYPE;           }
#line 1768 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 97 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDWHERE;          }
#line 1774 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 98 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENTRY;             }
#line 1780 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 99 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENUM;              }
#line 1786 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 100 "parser.y" /* yacc.c:1646  */
    { properties.kind = FORALL;            }
#line 1792 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 101 "parser.y" /* yacc.c:1646  */
    { properties.kind = IF;                }
#line 1798 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 102 "parser.y" /* yacc.c:1646  */
    { properties.kind = INTERFACE;         }
#line 1804 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 103 "parser.y" /* yacc.c:1646  */
    { properties.kind = MODULE;            }
#line 1810 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 104 "parser.y" /* yacc.c:1646  */
    { properties.kind = PROCEDURE;         }
#line 1816 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 105 "parser.y" /* yacc.c:1646  */
    { properties.kind = PROGRAM;           }
#line 1822 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 106 "parser.y" /* yacc.c:1646  */
    { properties.kind = PROCEDURE;         }
#line 1828 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 107 "parser.y" /* yacc.c:1646  */
    { properties.kind = SELECTCASE;        }
#line 1834 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 108 "parser.y" /* yacc.c:1646  */
    { properties.kind = SELECTTYPE;        }
#line 1840 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 109 "parser.y" /* yacc.c:1646  */
    { properties.kind = END;               }
#line 1846 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 110 "parser.y" /* yacc.c:1646  */
    { properties.kind = SUBROUTINE;        }
#line 1852 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 111 "parser.y" /* yacc.c:1646  */
    { properties.kind = FUNCTION;          }
#line 1858 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 112 "parser.y" /* yacc.c:1646  */
    { properties.kind = SUBMODULE;         }
#line 1864 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 113 "parser.y" /* yacc.c:1646  */
    { properties.kind = TYPE;              }
#line 1870 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 114 "parser.y" /* yacc.c:1646  */
    { properties.kind = TYPEIS;            }
#line 1876 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 115 "parser.y" /* yacc.c:1646  */
    { properties.kind = WHERE;             }
#line 1882 "parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 265 "parser.y" /* yacc.c:1646  */
    {lexer_enable(IDENTIFIER);}
#line 1888 "parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 267 "parser.y" /* yacc.c:1646  */
    {lexer_enable(SKIP);}
#line 1894 "parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 269 "parser.y" /* yacc.c:1646  */
    {lexer_enable(SKIPALL);}
#line 1900 "parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 271 "parser.y" /* yacc.c:1646  */
    {lexer_enable(SKIPNOOP);}
#line 1906 "parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 273 "parser.y" /* yacc.c:1646  */
    {properties.name=lexer_getname();}
#line 1912 "parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 275 "parser.y" /* yacc.c:1646  */
    {properties.label=lexer_getstlabel();}
#line 1918 "parser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 277 "parser.y" /* yacc.c:1646  */
    {properties.dolabel=lexer_geti_number();}
#line 1924 "parser.cpp" /* yacc.c:1646  */
    break;


#line 1928 "parser.cpp" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
#line 281 "parser.y" /* yacc.c:1906  */


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
   lexer_set(p,IDENTIFIER);
   resetprop();
   yyparse();
   if (properties.kind != UNCLASSIFIED)
      return properties;
   lexer_set(p,KEYWORD);
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

