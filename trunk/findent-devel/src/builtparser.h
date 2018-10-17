/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
