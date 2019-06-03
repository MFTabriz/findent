TESTS = \
	 test1.sh  test2.sh  test3.sh  test4.sh  test5.sh  test6.sh  \ 
         test7.sh  test8.sh  test9.sh  test10.sh test11.sh test12.sh \ 
	 test13.sh test14.sh test15.sh test16.sh test17.sh test18.sh \
	 test19.sh test20.sh test21.sh 

AM_TESTS_ENVIRONMENT = $(srcdir)/init.sh ;

EXTRA_DIST = $(TESTS)

export SRCDIR = $(top_srcdir)
export FC 

if MAKEWIN
   export WINDOWS = yes
else
   export WINDOWS = no
endif

if USEESOPE
   export ESOPE = yes
else
   export ESOPE = no
endif

clean-local:
	rm -rf *.tmpdir
