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
eof
cat << eof > expect
5
eof

../doit "-lastindent --last_indent" "-ifree -Ia -i3"
rc=`expr $rc + $?`


cat << eof > prog
     endif
eof
cat << eof > expect
5
eof

../doit "-lastindent --last_indent" "-ifree -Ia -i3"
rc=`expr $rc + $?`

. ../postlude

exit $rc
