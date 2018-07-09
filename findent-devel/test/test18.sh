#!/bin/sh
if test -e prelude ; then
   . ./prelude
else
   . ./debian/tests/prelude
fi
rc=0
doit=../doit
cat << eof > prog
      program main
      contains
      #ifdef foo
      subroutine sub()
      #elif bar==1
      subroutine sub(a)
      #else
      subroutine sub(a,b)
      #endif
      continue
      end subroutine
      end program
eof
cat << eof > expect
      program main
      contains
#ifdef foo
         subroutine sub()
#elif bar==1
         subroutine sub(a)
#else
         subroutine sub(a,b)
#endif
            continue
         end subroutine
      end program
eof

$doit "-iauto --input_format=auto -ifixed --input_format=fixed" "-I0 -i3" "for fixed input"
rc=`expr $rc + $?`

cat << eof > expect
program main
contains
#ifdef foo
   subroutine sub()
#elif bar==1
   subroutine sub(a)
#else
   subroutine sub(a,b)
#endif
      continue
   end subroutine
end program
eof

$doit "-ifree --input_format=free" "-I0 -i3" "for fixed input"
rc=`expr $rc + $?`

cat << eof > prog
      program main
      contains
      ??if(foo)
      subroutine sub()
      ??else  if(bar)
      subroutine sub(a)
      ??else
      subroutine sub(a,b)
      ??endif
      continue
      end subroutine
      end program
eof
cat << eof > expect
      program main
      contains
??if(foo)
         subroutine sub()
??else  if(bar)
         subroutine sub(a)
??else
         subroutine sub(a,b)
??endif
            continue
         end subroutine
      end program
eof

$doit "-iauto --input_format=auto -ifixed --input_format=fixed" "-I0 -i3" "for fixed input"
rc=`expr $rc + $?`

cat << eof > expect
program main
contains
??if(foo)
   subroutine sub()
??else  if(bar)
   subroutine sub(a)
??else
   subroutine sub(a,b)
??endif
      continue
   end subroutine
end program
eof

$doit "-ifree --input_format=free" "-I0 -i3" "for fixed input"
rc=`expr $rc + $?`
. ../postlude
exit $rc
