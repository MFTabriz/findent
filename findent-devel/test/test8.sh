#!/bin/sh
. ./prelude
../test-compile.sh ../progfixed1.f
rc=$?
. ../postlude
exit $rc
