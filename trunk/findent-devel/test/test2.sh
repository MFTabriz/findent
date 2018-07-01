#!/bin/sh
. ./prelude
../test-compile.sh ../progfixed.f
rc=$?
. ../postlude
exit $rc
