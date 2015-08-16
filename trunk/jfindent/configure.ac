#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT(jfindent, 1.2, wvermin@gmail.com)
m4_include([m4/ax_check_class.m4])
m4_include([m4/ax_check_rqrd_class.m4])
m4_include([m4/ax_java_options.m4])
m4_include([m4/ax_java_works.m4])
m4_include([m4/ax_prog_javac.m4])
m4_include([m4/ax_prog_javac_works.m4])
m4_include([m4/ax_prog_java.m4])
m4_include([m4/ax_try_compile_java.m4])
m4_include([m4/ax_try_run_java.m4])
AM_MAINTAINER_MODE
AC_CONFIG_SRCDIR([src/Jfindent.java])
AC_CONFIG_HEADERS([config.h])
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
	//switch (a){
	 //  case "foo": break;
	  // }
	  if ( a.equals("foo")) {
	     }

	}
   ],
   [AC_MSG_NOTICE([Succesfully compiled simple java program])],
   [AC_MSG_ERROR([Cannot compile simple java program: set JAVAC to a java compiler, version >= 1.6])])

AC_OUTPUT(Makefile src/Makefile)
