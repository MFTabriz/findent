#!/bin/sh
if test -e prelude ; then
   . ./prelude
else
   . ./debian/tests/prelude
fi
rc=0
doit=../doit
cat << eof > prog
      program fixed
      continue
      # if xyz || \
abc
      x=1
      # endif
      end
eof

cat << eof > expect
fixed
eof

$doit "-q --query_fix_free" "" "for fixed input"
rc=`expr $rc + $?`

cat << eof > prog
      program free
 continue
      end
eof

cat << eof > expect
free
eof

$doit "-q --query_fix_free" "" "for free input"
rc=`expr $rc + $?`

cat << eof > prog
      program pqr
      do i=1,10
      continue
      enddo
      end
eof

cat << eof > expect
program pqr
  do i=1,10
  continue
  enddo
end
eof

$doit "-M2 --max_indent=2" "-ifree -i8" "for free input"
rc=`expr $rc + $?`

cat << eof > expect
      program pqr
        do i=1,10
        continue
        enddo
      end
eof

$doit "-M2 --max_indent=2" "-ifixed -i8" "for fixed input"
rc=`expr $rc + $?`

. ../postlude
exit $rc
