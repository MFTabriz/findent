#!/bin/sh
if test -e prelude ; then
   . ./prelude
else
   . ./debian/tests/prelude
fi
../test-compile.sh ../progfixed1.f
rc=$?
. ../postlude
exit $rc
