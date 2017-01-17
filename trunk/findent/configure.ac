#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT(findent, 2.7.4~pre1 ,wvermin@gmail.com)
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE
AC_CONFIG_SRCDIR([src/findent.cpp])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([test/progfixed-dos.f])
AC_CONFIG_FILES([test/progfixed-dos.f.try.f.ref])
AC_CONFIG_FILES([test/progfixed.f])
AC_CONFIG_FILES([test/progfixedfree-dos.f])
AC_CONFIG_FILES([test/progfixedfree-dos.f.try.f.ref])
AC_CONFIG_FILES([test/progfixedfree.f])
AC_CONFIG_FILES([test/progfixedfree.f.try.f.ref])
AC_CONFIG_FILES([test/progfixed.f.try.f.ref])
AC_CONFIG_FILES([test/progfree-dos.f])
AC_CONFIG_FILES([test/progfree-dos.f.try.f.ref])
AC_CONFIG_FILES([test/progfree.f])
AC_CONFIG_FILES([test/progfree.f.try.f.ref])

AC_CONFIG_FILES([test/test-compile.sh],[chmod +x test/test-compile.sh])
AC_CONFIG_FILES([test/test1.sh],[chmod +x test/test1.sh])
AC_CONFIG_FILES([test/test2.sh],[chmod +x test/test2.sh])
AC_CONFIG_FILES([test/test3.sh],[chmod +x test/test3.sh])
AC_CONFIG_FILES([test/test4.sh],[chmod +x test/test4.sh])
AC_CONFIG_FILES([test/test5.sh],[chmod +x test/test5.sh])
AC_CONFIG_FILES([test/test6.sh],[chmod +x test/test6.sh])
AC_CONFIG_FILES([test/test10.sh],[chmod +x test/test10.sh])
AC_CONFIG_FILES([test/test11.sh],[chmod +x test/test11.sh])

m4_include([m4/ax_prog_flex.m4])
m4_include([m4/ax_prog_bison.m4])

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

# test if bison available etc...

touch src/dummyparser

AC_ARG_WITH(bison, [AS_HELP_STRING([--with-bison],[Use bison to create parser @<:@default=use-if-bison-available@:>@])],[],[with_bison=use-if-bison-available])

AS_IF( [test "x$with_bison" = "xyes"],
       [AX_PROG_BISON([],AC_MSG_ERROR([No valid bison found. Try --without-bison]))])

AS_IF( [test "x$with_bison" = "xuse-if-bison-available"],
       [AX_PROG_BISON(AC_MSG_NOTICE([Will use bison if necessary to create parser]
        ) 
	[with_bison=yes],
        AC_MSG_NOTICE([No bison found. Will use pre-build parser])
	[with_bison=no])])

AS_IF( [test "x$with_bison" = "xno"],
       [ AC_CONFIG_FILES([src/buildparser.cpp])
         AC_CONFIG_FILES([src/buildparser.h])])

AM_CONDITIONAL([USEBISON],[test "x$with_bison" = "xyes"])

# test if flex available etc...

touch src/dummylexer

AC_ARG_VAR([LEX],[The 'Fast lexical analyser generator' to use])

AC_ARG_WITH(flex, [AS_HELP_STRING([--with-flex],[Use flex to create parser @<:@default=use-if-flex-available@:>@])],[],[with_flex=use-if-flex-available])

AS_IF( [test "x$with_flex" = "xyes"],
       [AX_PROG_FLEX([],AC_MSG_ERROR([No valid flex found. Try --without-flex]))])

AS_IF( [test "x$with_flex" = "xuse-if-flex-available"],
       [AX_PROG_FLEX(AC_MSG_NOTICE([Will use flex if necessary to create lexer]
        ) 
	[with_flex=yes],
        AC_MSG_NOTICE([No flex found. Will use pre-build lexer])
	[with_flex=no])])

AS_IF( [test "x$with_flex" = "xno"],
       [ AC_CONFIG_FILES([src/buildlexer.cpp])])

AM_CONDITIONAL([USEFLEX],[test "x$with_flex" = "xyes"])

AC_PROG_CXX
AC_PROG_AWK
AC_PROG_SED
AC_MSG_NOTICE([yacc: ${YACC}])
AC_MSG_NOTICE([flex: ${LEX}])
AC_MSG_NOTICE([bison: ${BISON}])

AC_LANG([C++])
AC_HEADER_STDC
AC_CHECK_HEADERS([iostream string stack vector cstdio queue algorithm sstream],[],AC_MSG_ERROR([Exiting])) 

AC_OUTPUT(Makefile src/Makefile scripts/Makefile test/Makefile)
