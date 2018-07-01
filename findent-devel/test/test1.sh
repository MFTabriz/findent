#!/bin/sh
. ./prelude
../test-compile.sh ../progfixed-dos.f
rc=$?
. ../postlude
exit $rc
