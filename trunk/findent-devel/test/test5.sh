#!/bin/sh
. ./prelude
../test-compile.sh ../progfree-dos.f
rc=$?
. ../postlude
exit $rc
