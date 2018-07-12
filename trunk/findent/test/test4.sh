#!/bin/sh
if test -e prelude ; then
   . ./prelude
else
   . ./debian/tests/prelude
fi
../test-compile.sh ../progfixedfree.f
rc=$?
. ../postlude
exit $rc
