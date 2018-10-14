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
    FINDFORMAT = 317,
    UNKNOWN = 318,
    FREE = 319,
    FIXED = 320,
    UNSURE = 321,
    PROBFREE = 322,
    FINDENTFIX = 323,
    FIXFINDENTFIX = 324,
    P_ON = 325,
    P_OFF = 326,
    SCANFIXPRE = 327,
    CPP_IF = 328,
    CPP_ENDIF = 329,
    CPP_ELSE = 330,
    CPP_ELIF = 331,
    CPP = 332,
    COCO_IF = 333,
    COCO_ENDIF = 334,
    COCO_ELSE = 335,
    COCO_ELIF = 336,
    COCO = 337,
    INCLUDE = 338,
    INCLUDE_CPP = 339,
    INCLUDE_CPP_STD = 340,
    INCLUDE_COCO = 341,
    INCFILENAME = 342,
    IDENTIFIER = 343,
    SKIP = 344,
    SKIPALL = 345,
    SKIPNOOP = 346,
    KEYWORD = 347,
    ELEMENTAL = 348,
    IMPURE = 349,
    PURE = 350,
    RECURSIVE = 351,
    SUBROUTINE = 352,
    FUNCTION = 353,
    PROGRAM = 354,
    EOL = 355,
    NAMED_LABEL = 356,
    STLABEL = 357,
    TYPE = 358,
    ENDTYPE = 359,
    CLASS = 360,
    BASICTYPE = 361,
    TYPEC = 362,
    QSTRING = 363,
    HSTRING = 364,
    LR = 365,
    LRB = 366,
    DOTOPERATOR = 367,
    I_NUMBER = 368,
    UNCLASSIFIED = 369,
    ERROR = 370,
    OMP = 371,
    SCANOMPFIXED = 372,
    SCANOMPFREE = 373,
    LAST_TOKEN = 374
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
