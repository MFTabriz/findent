#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT(jfindent, 1.2, wvermin@gmail.com)
AM_MAINTAINER_MODE
AC_CONFIG_SRCDIR([src/Jfindent.java])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE

AS_IF( [test "x$JAVAC" = x],[JAVAC=javac])
AS_IF( [test "x$JAVA" = x],[JAVA=java])
AC_MSG_NOTICE([java: $JAVAC $JAVA])
AX_PROG_JAVAC
AX_PROG_JAVA
AC_MSG_NOTICE([java: $JAVAC $JAVA])
AX_TRY_COMPILE_JAVA([],
   [
     public static void main(String[] args){ 
        String a = "foo";
	switch (a){
	   case "foo": break;
	   }
	}
   ],
   [AC_MSG_NOTICE([Succesfully compiled simple java program])],
   [AC_MSG_ERROR([Cannot compile simple java program: set JAVAC to a java compiler, version >= 1.6])])

AC_OUTPUT(Makefile src/Makefile)
