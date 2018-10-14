#!/bin/sh
if test -e prelude ; then
   . ./prelude
else
   . ./debian/tests/prelude
fi
rc=0
cat << eof > prog
        program prog

          continue
!  comment
eof
cat << eof > expect
3
eof

../doit "-lastusable --last_usable" "-ifree -Ia" "" 
rc=`expr $rc + $?`

../doit "-lastusable --last_usable" "-ifixed -Ia" "" 
rc=`expr $rc + $?`

. ../postlude
exit $rc
