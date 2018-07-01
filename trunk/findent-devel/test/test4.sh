#!/bin/sh
. ./prelude
../test-compile.sh ../progfixedfree.f
rc=$?
. ../postlude
exit $rc
