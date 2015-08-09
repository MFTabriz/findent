#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT(findent, 2.3-pre1, wvermin@gmail.com)
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE
AC_CONFIG_SRCDIR([src/findent.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AC_SUBST([make_include], ["include"])

AC_ARG_WITH(windows, [AS_HELP_STRING([--with-windows],[Build findent.exe @<:@default=no@:>@])],[],[with_windows=no])

mingw32="i586-mingw32msvc-g++"
AS_IF( [test "x$with_windows" = xyes],[AC_CHECK_PROG([MINGW32],[$mingw32],[$mingw32],[none])]) 

AS_IF( [test "x$MINGW32" = xnone],
      [AC_MSG_ERROR([Not found: $mingw32, set MINGW32 to a working mingw C++ compiler])])

AS_IF( [test "x$with_windows" = xyes],
       [CXX=$MINGW32
        AC_MSG_NOTICE([mingw c++ compiler: $MINGW32])
        AC_MSG_NOTICE([Will create WINDOWS executable findent.exe])])

AM_CONDITIONAL([MAKEMAN],[test "x$with_windows" != "xyes"])

AC_PROG_CXX
AC_PROG_AWK
AX_PROG_BISON([YACC=$(echo ${YACC} | ${AWK} '{print $1}')],AC_MSG_ERROR([No valid bison found]))
AC_MSG_NOTICE([bison: ${YACC}])
AC_ARG_VAR([LEX],[The 'Fast lexical analyser generator' to use])
AX_PROG_FLEX([],AC_MSG_ERROR([No valid flex found]))
AC_MSG_NOTICE([flex: ${LEX}])

AC_LANG([C++])
AC_HEADER_STDC
AC_CHECK_HEADERS([iostream string stack vector cstdio queue algorithm sstream],[],AC_MSG_ERROR([Exiting])) 

AC_OUTPUT(Makefile src/Makefile scripts/Makefile)
