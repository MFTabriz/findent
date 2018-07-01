#!/bin/sh
. ./prelude
../test-compile.sh ../progfixedfree-dos.f
rc=$?
. ../postlude
exit $rc
