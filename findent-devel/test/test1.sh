#!/bin/bash
if test -e prelude ; then
   . ./prelude
else
   . ./debian/tests/prelude
fi
../test-compile.sh ../progfixed-dos.f
rc=$?
. ../postlude
exit $rc
