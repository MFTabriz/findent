#!/bin/sh
if test -e prelude ; then
   . ./prelude
else
   . ./debian/tests/prelude
fi
rc=0
doit=../doit
cat << eof > prog
      program fixed001
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
      program free001
 continue
      end
eof

cat << eof > expect
free
eof

$doit "-q --query_fix_free" "" "for free input"
rc=`expr $rc + $?`

cat << eof > prog
      program p001
      do i=1,10
      continue
      enddo
      end
eof

cat << eof > expect
program p001
  do i=1,10
  continue
  enddo
end
eof

$doit "-M2 --max_indent=2" "-ifree -i8" "for free input"
rc=`expr $rc + $?`

cat << eof > expect
      program p001
        do i=1,10
        continue
        enddo
      end
eof

$doit "-M2 --max_indent=2" "-ifixed -i8" "for fixed input"
rc=`expr $rc + $?`

cat << eof > prog
program p002
x=x+ &
10+ &
& 20+ &
30 
end
eof

cat << eof > expect
      program p002
         x=x+
     1   10+
     2    20+
     3   30
      end
eof

$doit "--continuation=0" "-ofixed" "--continuation=0 for free input"
rc=`expr $rc + $?`

cat << eof > expect
      program p002
         x=x+
     &   10+
     &    20+
     &   30
      end
eof

$doit "--continuation= " "-ofixed" "--continuation=' ' for free input"
rc=`expr $rc + $?`

cat << eof > expect
      program p002
         x=x+
     +   10+
     +    20+
     +   30
      end
eof

$doit "--continuation=+" "-ofixed" "--continuation=+ for free input"
rc=`expr $rc + $?`

cat << eof > prog
      program p003
       x=9+
     +   20 +
     ! abc
     ! abc
     ! abc
     +  30
      end
eof

cat << eof > expect
      program p003
         x=9+
     +     20 +
         ! abc
         ! abc
         ! abc
     +    30
      end
eof

$doit "--continuation= " "" "--continuation=' ' for fixed input"
rc=`expr $rc + $?`

cat << eof > expect
      program p003
         x=9+
     9     20 +
         ! abc
         ! abc
         ! abc
     9    30
      end
eof

$doit "--continuation=9" "" "--continuation=9 for fixed input"
rc=`expr $rc + $?`
. ../postlude
exit $rc
