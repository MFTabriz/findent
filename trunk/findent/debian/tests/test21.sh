#!/bin/sh
if test -e prelude ; then
   . ./prelude
else
   . ./debian/tests/prelude
fi
if test xyes = "x$ESOPE" ; then
   ../test-compile.sh ../esope.f
   rc=$?
else
   rc=0
fi
. ../postlude
exit $rc
