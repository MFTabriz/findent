#!/bin/sh
. ./prelude
../test-compile.sh ../progfree1.f
rc=$?
. ../postlude
exit $rc
