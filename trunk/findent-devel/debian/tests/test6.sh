#!/bin/sh
. ./prelude
../test-compile.sh ../progfree.f
rc=$?
. ../postlude
exit $rc
