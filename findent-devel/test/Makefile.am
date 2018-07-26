TESTS = test1.sh test2.sh          test4.sh test5.sh test6.sh \
	test7.sh test8.sh \
	test9.sh test10.sh test11.sh test12.sh \
	test13.sh test14.sh test15.sh test16.sh test17.sh test18.sh \
	test19.sh

EXTRA_DIST = test1.sh test2.sh test3.sh test4.sh test5.sh \
	test6.sh test7.sh test8.sh \
	test9.sh test10.sh test11.sh test12.sh \
	test13.sh test14.sh test15.sh test16.sh test17.sh test18.sh \
	test19.sh

export SRCDIR = $(top_srcdir)
if MAKEWIN
   export WINDOWS = yes
else
   export WINDOWS = no
endif
clean-local:
	rm -rf *.tmpdir
