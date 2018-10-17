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

#include <iostream>

#include "debug.h"
#include "lexer.h"
#include "line_prep.h"
#include "prop.h"

struct propstruct properties;

#line 77 "parser.cpp" /* yacc.c:339  */

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
    IDENTIFIER = 345,
    SKIP = 346,
    SKIPALL = 347,
    SKIPNOOP = 348,
    KEYWORD = 349,
    ELEMENTAL = 350,
    IMPURE = 351,
    PURE = 352,
    RECURSIVE = 353,
    SUBROUTINE = 354,
    FUNCTION = 355,
    PROGRAM = 356,
    EOL = 357,
    NAMED_LABEL = 358,
    STLABEL = 359,
    TYPE = 360,
    ENDTYPE = 361,
    CLASS = 362,
    BASICTYPE = 363,
    TYPEC = 364,
    QSTRING = 365,
    HSTRING = 366,
    LR = 367,
    LRB = 368,
    DOTOPERATOR = 369,
    I_NUMBER = 370,
    UNCLASSIFIED = 371,
    ERROR = 372,
    OMP = 373,
    SCANOMPFIXED = 374,
    SCANOMPFREE = 375,
    LAST_TOKEN = 376
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

#line 250 "parser.cpp" /* yacc.c:358  */

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
#define YYLAST   361

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  129
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  96
/* YYNRULES -- Number of rules.  */
#define YYNRULES  188
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  356

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   376

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   122,     2,     2,
       2,     2,   125,     2,   127,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   128,     2,
     123,   126,   124,     2,     2,     2,     2,     2,     2,     2,
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
     115,   116,   117,   118,   119,   120,   121
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    60,    60,    62,    63,    64,    65,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   128,   130,   131,
     133,   135,   137,   138,   139,   140,   143,   144,   145,   146,
     147,   160,   161,   164,   165,   166,   167,   169,   170,   171,
     173,   174,   175,   176,   177,   178,   179,   182,   183,   184,
     185,   187,   189,   191,   192,   194,   195,   196,   199,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   225,   226,   229,   230,   231,   233,   234,   235,   237,
     238,   239,   240,   241,   243,   247,   248,   250,   251,   253,
     254,   255,   256,   257,   258,   260,   262,   263,   264,   265,
     266,   267,   269,   270,   271,   273,   275,   276,   277,   279,
     280,   282,   283,   284,   285,   287,   289,   291,   293,   295,
     297,   299,   301,   303,   305,   307,   309,   311,   314
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
  "INCLUDE_CPP_STD", "INCLUDE_COCO", "INCFILENAME", "USE", "IDENTIFIER",
  "SKIP", "SKIPALL", "SKIPNOOP", "KEYWORD", "ELEMENTAL", "IMPURE", "PURE",
  "RECURSIVE", "SUBROUTINE", "FUNCTION", "PROGRAM", "EOL", "NAMED_LABEL",
  "STLABEL", "TYPE", "ENDTYPE", "CLASS", "BASICTYPE", "TYPEC", "QSTRING",
  "HSTRING", "LR", "LRB", "DOTOPERATOR", "I_NUMBER", "UNCLASSIFIED",
  "ERROR", "OMP", "SCANOMPFIXED", "SCANOMPFREE", "LAST_TOKEN", "'%'",
  "'<'", "'>'", "'*'", "'='", "','", "':'", "$accept", "lline", "labels",
  "line", "blank", "stlabel", "named_label", "module", "use", "include",
  "include_cpp", "include_cpp_std", "include_coco", "abstractinterface",
  "contains", "interface", "moduleprocedure", "procedure", "program_stmt",
  "subroutine_stmt", "subroutine", "subroutine_spec", "subroutinename",
  "subroutineprefix", "subroutineprefix_spec", "function_stmt", "function",
  "function_spec", "functionname", "submodule", "intrinsic_type_spec",
  "kind_selector", "entry", "endassociate", "endblock", "endblockdata",
  "endcritical", "enddo", "endenum", "endforall", "endfunction", "endif",
  "endinterface", "endmodule", "endprocedure", "endprogram", "endselect",
  "endsubmodule", "endsubroutine", "endteam", "endtype", "endwhere",
  "simple_end", "gidentifier", "assignment", "else", "elseif", "elsewhere",
  "if_construct", "where_construct", "forall_construct", "do_construct",
  "do", "docomma", "selectcase", "selecttype", "case", "casedefault",
  "classdefault", "classis", "typeis", "changeteam", "block", "blockdata",
  "associate", "critical", "enum", "type", "type1", "lvalue",
  "construct_name", "lr_construct_name", "skipall", "skipnoop",
  "enable_char", "enable_identifier", "enable_skip", "enable_skipall",
  "enable_skipnoop", "enable_incfilename", "getname", "getstlabel",
  "getdolabel", "getstring", "getlr", "empty", YY_NULLPTR
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
     375,   376,    37,    60,    62,    42,    61,    44,    58
};
# endif

#define YYPACT_NINF -260

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-260)))

#define YYTABLE_NINF -8

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -37,  -260,  -260,     7,   255,   -89,  -260,  -260,  -260,  -260,
    -260,  -260,   -69,   -34,  -260,  -260,  -260,  -260,  -260,   -42,
    -260,   -38,  -260,   -36,  -260,   -35,  -260,  -260,  -260,  -260,
     -33,   -29,  -260,   -28,   -26,  -260,  -260,  -260,   -23,   -22,
    -260,  -260,   -31,  -260,   -24,   -20,  -260,  -260,  -260,   -21,
    -260,   -39,  -260,   -19,  -260,   -32,    -8,   -12,  -260,  -260,
    -260,  -260,  -260,   -18,   -95,   -14,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,     2,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
      -7,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,   -30,
     -49,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,   -66,   -90,  -260,  -260,    14,
      16,  -260,  -260,     6,    17,    10,    11,    12,    13,   101,
      18,   102,    19,    20,    21,    23,    24,    25,   -78,  -260,
    -260,    26,    27,    28,    30,  -260,    32,    29,    34,  -260,
    -260,    35,  -260,    46,  -260,  -260,  -260,  -260,    38,    40,
      41,    42,    44,  -260,    47,    48,    49,    50,  -260,  -260,
      63,    58,    64,    51,  -260,  -260,  -260,  -260,    65,   -55,
    -260,    54,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
      45,   -79,    52,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,   -49,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,    56,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,    70,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,   -52,  -260,    59,
      60,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,    61,    66,    77,
      67,  -260,  -260,  -260,  -260,  -260,  -260,   -99,  -260,  -260,
    -260,    76,    55,    80,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,    78,    71,  -260,    82,  -260,  -260,    74,  -260,
    -260,    75,  -260,  -260,  -260,   -49,    84,    85,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,    87,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,    86,  -260,  -260,
    -260,    88,    99,  -260,  -260,   100,  -260,    90,  -260,    69,
    -260,  -260,  -260,  -260,    92,  -260
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     188,    69,   184,     0,   188,     4,     5,     3,    68,     1,
     178,   178,     0,     0,   178,   178,   178,   178,   178,     0,
     178,     0,   178,     0,   178,     0,   178,   178,   178,   178,
       0,     0,   178,     0,     0,   178,   178,   178,     0,     0,
     178,   180,     0,   180,     0,     0,   178,   178,   178,     0,
     178,     0,   178,     0,   178,     0,     0,     0,   178,   178,
     178,   130,    67,     0,     0,     0,   178,   129,   178,   178,
     178,     2,    11,    53,    65,    48,    49,    50,    51,     8,
      19,    52,    54,    56,    55,    60,     0,    61,    62,    44,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    59,
     166,     9,    22,    23,    24,    47,    66,    46,    21,     0,
       0,    57,    58,    14,    15,    17,    18,    64,    16,    12,
      13,    10,    20,    45,    63,     0,     0,    88,     6,     0,
       0,   187,   128,     0,   188,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   188,   145,
     146,     0,     0,     0,     0,   180,     0,     0,     0,   178,
     178,     0,    78,     0,    76,   118,    77,   156,     0,     0,
       0,     0,     0,   159,     0,     0,     0,     0,   180,   114,
       0,     0,     0,     0,   186,   186,   182,   186,     0,     0,
     165,     0,    86,   100,    90,    91,    92,    93,    85,    99,
       0,   103,     0,   178,    84,    89,   178,    98,    94,   167,
     142,   185,   180,   180,   180,   180,   180,     0,   181,   183,
     180,   178,   124,   183,   169,   116,   121,   119,   123,     0,
     133,   178,   117,   137,   127,   138,   115,   135,   183,   172,
     171,   143,   144,   113,   147,   148,   122,     0,   151,     0,
       0,   152,   175,   110,   157,   111,   158,   109,   160,   112,
     155,   125,   161,   178,   183,   183,   120,     0,     0,     0,
       0,   183,   183,    82,   126,    96,   107,     0,   104,    95,
     179,     0,     0,     0,   180,   140,   141,   164,   162,   163,
     168,   131,     0,     0,   108,     0,   170,   136,     0,   173,
     183,     0,   149,   154,   153,     0,     0,     0,    72,    73,
     186,    75,   180,   179,   106,   105,     0,   183,   179,   183,
     139,   176,    70,   183,   134,   174,   150,     0,    79,    80,
     177,     0,     0,    83,    87,     0,   101,     0,   132,     0,
      71,    81,    97,   102,     0,    74
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -260,  -260,  -260,  -260,  -260,  -260,   174,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -116,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,   -27,
       5,   141,   -41,  -260,  -260,   -10,  -259,  -126,  -260,  -260,
    -194,  -260,  -260,  -189,  -260,     1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    71,    72,     5,     6,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
     213,   214,   290,    86,   215,    87,   216,   217,   292,    88,
     218,   288,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     143,   157,   172,   301,   349,   144,   326,   173,   302,   279,
     303,     8,   294,   277,   231,     7
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     139,   140,   175,   222,   223,   137,   278,     9,   280,   202,
     203,    61,   248,   324,     1,   195,   325,   158,   159,   160,
     145,   146,   147,   148,   224,   150,   167,   152,   196,   154,
      61,   156,   227,   286,   249,   282,   228,   163,   311,   306,
     166,    67,   168,   141,   158,   171,   287,   283,   191,   192,
     312,   178,   179,   180,   309,   182,   198,   185,   199,   200,
      67,   225,   226,   183,   342,   193,     1,     2,   142,   345,
     149,   174,   220,   184,   151,   201,   153,   155,   176,   161,
     316,   317,   177,   162,   164,   221,   165,   322,   323,   169,
     170,   181,   194,   186,   189,   188,   197,   204,   205,   206,
     207,   208,   209,   190,   229,   219,   230,   233,   232,   210,
     211,   212,   235,   236,   237,   238,   335,   239,   241,   273,
     240,   242,   243,   244,   255,   245,   246,   247,   251,   252,
     253,   340,   254,   344,   256,   346,   258,   261,   262,   347,
     263,   257,   264,   265,   266,   234,   267,   272,   274,   268,
     269,   270,   271,   276,   275,   281,   284,   285,   307,   250,
     310,   313,   314,   318,   289,   320,   327,   328,   319,   321,
     329,   331,   333,   332,   259,   260,   334,   336,   343,   138,
     350,   295,   296,   297,   298,   299,   338,   339,   348,   304,
     351,   352,   353,   354,   355,   187,   341,     0,     0,   337,
     300,     0,     0,   291,     0,     0,   293,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   305,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   308,     0,     0,     0,
       0,     0,     0,   330,     0,    -7,     0,     0,    10,     0,
      11,    12,     0,   315,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,     0,
      57,     0,    58,    59,    60,    61,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    63,
      64,     0,    65,     0,    66,    67,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    68,     0,     0,     0,
      69,    70
};

static const yytype_int16 yycheck[] =
{
      10,    11,    43,   119,   120,     4,   195,     0,   197,     7,
       8,    60,    90,   112,   103,   110,   115,    27,    28,    29,
      15,    16,    17,    18,    90,    20,    36,    22,   123,    24,
      60,    26,   122,   112,   112,    90,   126,    32,    90,   233,
      35,    90,    37,   112,    54,    40,   125,   102,    58,    59,
     102,    46,    47,    48,   248,    50,    66,    52,    68,    69,
      90,   127,   128,   102,   323,    60,   103,   104,   102,   328,
     112,   102,   102,   112,   112,    70,   112,   112,   102,   112,
     274,   275,   102,   112,   112,   115,   112,   281,   282,   112,
     112,   112,   110,   112,   102,   127,   110,    95,    96,    97,
      98,    99,   100,   115,    90,   112,    90,    90,   102,   107,
     108,   109,   102,   102,   102,   102,   310,    16,    16,    56,
     102,   102,   102,   102,   165,   102,   102,   102,   102,   102,
     102,   320,   102,   327,   102,   329,   102,   102,    92,   333,
     102,   112,   102,   102,   102,   144,   102,   188,    90,   102,
     102,   102,   102,   102,    90,    90,   102,   112,   102,   158,
      90,   102,   102,   102,   112,    88,    90,   112,   102,   102,
      90,    93,    90,   102,   169,   170,   102,   102,    91,     5,
      92,   222,   223,   224,   225,   226,   102,   102,   102,   230,
      91,    91,   102,   124,   102,    54,   322,    -1,    -1,   315,
     227,    -1,    -1,   213,    -1,    -1,   216,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   231,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   241,    -1,    -1,    -1,
      -1,    -1,    -1,   294,    -1,     0,    -1,    -1,     3,    -1,
       5,     6,    -1,   273,     9,    10,    11,    12,    13,    14,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      55,    -1,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    -1,    87,    -1,    89,    90,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,
     105,   106
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   103,   104,   130,   131,   134,   135,   224,   220,     0,
       3,     5,     6,     9,    10,    11,    12,    13,    14,    15,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    55,    57,    58,
      59,    60,    61,    84,    85,    87,    89,    90,   101,   105,
     106,   132,   133,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   152,   154,   158,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   224,   135,   214,
     214,   112,   102,   209,   214,   209,   209,   209,   209,   112,
     209,   112,   209,   112,   209,   112,   209,   210,   214,   214,
     214,   112,   112,   209,   112,   112,   209,   214,   209,   112,
     112,   209,   211,   216,   102,   211,   102,   102,   209,   209,
     209,   112,   209,   102,   112,   209,   112,   210,   127,   102,
     115,   214,   214,   209,   110,   110,   123,   110,   214,   214,
     214,   209,     7,     8,    95,    96,    97,    98,    99,   100,
     107,   108,   109,   149,   150,   153,   155,   156,   159,   112,
     102,   115,   182,   182,    90,   127,   128,   122,   126,    90,
      90,   223,   102,    90,   224,   102,   102,   102,   102,    16,
     102,    16,   102,   102,   102,   102,   102,   102,    90,   112,
     224,   102,   102,   102,   102,   211,   102,   112,   102,   209,
     209,   102,    92,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   211,    56,    90,    90,   102,   222,   222,   218,
     222,    90,    90,   102,   102,   112,   112,   125,   160,   112,
     151,   214,   157,   214,   221,   211,   211,   211,   211,   211,
     208,   212,   217,   219,   211,   214,   219,   102,   209,   219,
      90,    90,   102,   102,   102,   214,   219,   219,   102,   102,
      88,   102,   219,   219,   112,   115,   215,    90,   112,    90,
     211,    93,   102,    90,   102,   219,   102,   182,   102,   102,
     222,   216,   215,    91,   219,   215,   219,   219,   102,   213,
      92,    91,    91,   102,   124,   102
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   129,   130,   131,   131,   131,   131,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   147,   148,   149,   150,   150,   151,   152,   152,
     153,   153,   153,   153,   153,   153,   153,   154,   155,   156,
     156,   157,   158,   159,   159,   160,   160,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     182,   183,   183,   184,   185,   186,   187,   188,   189,   190,
     190,   190,   190,   190,   190,   191,   192,   193,   194,   195,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     204,   205,   206,   206,   206,   207,   208,   208,   208,   209,
     209,   210,   210,   210,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224
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
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       5,     6,     4,     4,     8,     4,     2,     2,     2,     5,
       5,     6,     3,     5,     1,     1,     1,     3,     1,     2,
       1,     1,     1,     1,     1,     2,     2,     6,     1,     1,
       1,     3,     7,     1,     2,     2,     2,     1,     4,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     3,     6,     3,     5,     3,     4,     3,     3,     4,
       3,     3,     2,     3,     3,     2,     2,     3,     3,     4,
       5,     3,     3,     4,     4,     3,     2,     3,     3,     2,
       3,     3,     3,     3,     3,     2,     1,     2,     3,     2,
       3,     2,     2,     3,     4,     2,     2,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0
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
#line 68 "parser.y" /* yacc.c:1646  */
    { properties.kind = ABSTRACTINTERFACE; }
#line 1627 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 69 "parser.y" /* yacc.c:1646  */
    { properties.kind = ASSIGNMENT;        }
#line 1633 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 70 "parser.y" /* yacc.c:1646  */
    { properties.kind = ASSOCIATE;         }
#line 1639 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 71 "parser.y" /* yacc.c:1646  */
    { properties.kind = BLANK;             }
#line 1645 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 72 "parser.y" /* yacc.c:1646  */
    { properties.kind = BLOCK;             }
#line 1651 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 73 "parser.y" /* yacc.c:1646  */
    { properties.kind = BLOCKDATA;         }
#line 1657 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 74 "parser.y" /* yacc.c:1646  */
    { properties.kind = CASE;              }
#line 1663 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 75 "parser.y" /* yacc.c:1646  */
    { properties.kind = CASEDEFAULT;       }
#line 1669 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 76 "parser.y" /* yacc.c:1646  */
    { properties.kind = CHANGETEAM;        }
#line 1675 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 77 "parser.y" /* yacc.c:1646  */
    { properties.kind = CLASSDEFAULT;      }
#line 1681 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 78 "parser.y" /* yacc.c:1646  */
    { properties.kind = CLASSIS;           }
#line 1687 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 79 "parser.y" /* yacc.c:1646  */
    { properties.kind = CONTAINS;          }
#line 1693 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 80 "parser.y" /* yacc.c:1646  */
    { properties.kind = CRITICAL;          }
#line 1699 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 81 "parser.y" /* yacc.c:1646  */
    { properties.kind = DO;                }
#line 1705 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 82 "parser.y" /* yacc.c:1646  */
    { properties.kind = ELSE;              }
#line 1711 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 83 "parser.y" /* yacc.c:1646  */
    { properties.kind = ELSEIF;            }
#line 1717 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 84 "parser.y" /* yacc.c:1646  */
    { properties.kind = ELSEWHERE;         }
#line 1723 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 85 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDASSOCIATE;      }
#line 1729 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 86 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDBLOCK;          }
#line 1735 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 87 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDBLOCKDATA;      }
#line 1741 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 88 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDCRITICAL;       }
#line 1747 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 89 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDDO;             }
#line 1753 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 90 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDENUM;           }
#line 1759 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 91 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDFORALL;         }
#line 1765 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 92 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDFUNCTION;       }
#line 1771 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 93 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDIF;             }
#line 1777 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 94 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDINTERFACE;      }
#line 1783 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 95 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDMODULE;         }
#line 1789 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 96 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDPROCEDURE;      }
#line 1795 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 97 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDPROGRAM;        }
#line 1801 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 98 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDSELECT;         }
#line 1807 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 99 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDSUBMODULE;      }
#line 1813 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 100 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDSUBROUTINE;     }
#line 1819 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 101 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDTEAM;           }
#line 1825 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 102 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDTYPE;           }
#line 1831 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 103 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENDWHERE;          }
#line 1837 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 104 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENTRY;             }
#line 1843 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 105 "parser.y" /* yacc.c:1646  */
    { properties.kind = ENUM;              }
#line 1849 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 106 "parser.y" /* yacc.c:1646  */
    { properties.kind = FORALL;            }
#line 1855 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 107 "parser.y" /* yacc.c:1646  */
    { properties.kind = IF;                }
#line 1861 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 108 "parser.y" /* yacc.c:1646  */
    { properties.kind = INCLUDE;           }
#line 1867 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 109 "parser.y" /* yacc.c:1646  */
    { properties.kind = INCLUDE_CPP;       }
#line 1873 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 110 "parser.y" /* yacc.c:1646  */
    { properties.kind = INCLUDE_CPP_STD;   }
#line 1879 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 111 "parser.y" /* yacc.c:1646  */
    { properties.kind = INCLUDE_COCO;   }
#line 1885 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 112 "parser.y" /* yacc.c:1646  */
    { properties.kind = INTERFACE;         }
#line 1891 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 113 "parser.y" /* yacc.c:1646  */
    { properties.kind = MODULE;            }
#line 1897 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 114 "parser.y" /* yacc.c:1646  */
    { properties.kind = PROCEDURE;         }
#line 1903 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 115 "parser.y" /* yacc.c:1646  */
    { properties.kind = PROGRAM;           }
#line 1909 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 116 "parser.y" /* yacc.c:1646  */
    { properties.kind = PROCEDURE;         }
#line 1915 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 117 "parser.y" /* yacc.c:1646  */
    { properties.kind = SELECTCASE;        }
#line 1921 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 118 "parser.y" /* yacc.c:1646  */
    { properties.kind = SELECTTYPE;        }
#line 1927 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 119 "parser.y" /* yacc.c:1646  */
    { properties.kind = END;               }
#line 1933 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 120 "parser.y" /* yacc.c:1646  */
    { properties.kind = SUBROUTINE;        }
#line 1939 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 121 "parser.y" /* yacc.c:1646  */
    { properties.kind = FUNCTION;          }
#line 1945 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 122 "parser.y" /* yacc.c:1646  */
    { properties.kind = SUBMODULE;         }
#line 1951 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 123 "parser.y" /* yacc.c:1646  */
    { properties.kind = TYPE;              }
#line 1957 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 124 "parser.y" /* yacc.c:1646  */
    { properties.kind = TYPEIS;            }
#line 1963 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 125 "parser.y" /* yacc.c:1646  */
    { properties.kind = USE;               }
#line 1969 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 126 "parser.y" /* yacc.c:1646  */
    { properties.kind = WHERE;             }
#line 1975 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 137 "parser.y" /* yacc.c:1646  */
    {D(O("include"););}
#line 1981 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 138 "parser.y" /* yacc.c:1646  */
    {D(O("include_cpp"););}
#line 1987 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 139 "parser.y" /* yacc.c:1646  */
    {D(O("include_cpp <>"););}
#line 1993 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 140 "parser.y" /* yacc.c:1646  */
    {D(O("include_coco"););}
#line 1999 "parser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 291 "parser.y" /* yacc.c:1646  */
    {lexer_enable(CHAR);}
#line 2005 "parser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 293 "parser.y" /* yacc.c:1646  */
    {lexer_enable(IDENTIFIER);}
#line 2011 "parser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 295 "parser.y" /* yacc.c:1646  */
    {lexer_enable(SKIP);}
#line 2017 "parser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 297 "parser.y" /* yacc.c:1646  */
    {lexer_enable(SKIPALL);}
#line 2023 "parser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 299 "parser.y" /* yacc.c:1646  */
    {lexer_enable(SKIPNOOP);}
#line 2029 "parser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 301 "parser.y" /* yacc.c:1646  */
    {lexer_enable(INCFILENAME);}
#line 2035 "parser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 303 "parser.y" /* yacc.c:1646  */
    {properties.name=lexer_getname();}
#line 2041 "parser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 305 "parser.y" /* yacc.c:1646  */
    {properties.label=lexer_getstlabel();}
#line 2047 "parser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 307 "parser.y" /* yacc.c:1646  */
    {properties.dolabel=lexer_geti_number();}
#line 2053 "parser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 309 "parser.y" /* yacc.c:1646  */
    {properties.stringvalue=lexer_getstring();}
#line 2059 "parser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 311 "parser.y" /* yacc.c:1646  */
    {properties.lrvalue=lexer_getlr();}
#line 2065 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2069 "parser.cpp" /* yacc.c:1646  */
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
#line 316 "parser.y" /* yacc.c:1906  */


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
