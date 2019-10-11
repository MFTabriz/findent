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
      #define foo \\
bar \\
  a
      contains
      #ifdef foo \\
  bar \\
 a
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
#define foo \\
bar \\
  a
      contains
#ifdef foo \\
  bar \\
 a
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

$doit "-ifixed --input_format=fixed" "-I0 -i3" "for fixed input"
rc=`expr $rc + $?`

cat << eof > expect
program main
#define foo \\
bar \\
  a
contains
#ifdef foo \\
  bar \\
 a
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

$doit "-ifree --input_format=free" "-I0 -i3" "for free input"
rc=`expr $rc + $?`

cat << eof > prog
      program main
      ??logical::foo = .true. &
      ?? .or. &
      ?? .or. .false.
      contains
      ??if(foo) &
      ?? then
      subroutine sub()
      ??else  if(bar) then
      subroutine sub(a)
      ??else
      subroutine sub(a,b)
      ??endif
      continue
      end subroutine
      ?? logical a= &
      ?? .true.
      end program
eof
cat << eof > expect
      program main
??logical::foo = .true. &
?? .or. &
?? .or. .false.
      contains
??if(foo) &
?? then
         subroutine sub()
??else  if(bar) then
         subroutine sub(a)
??else
         subroutine sub(a,b)
??endif
            continue
         end subroutine
?? logical a= &
?? .true.
      end program
eof

$doit "-ifixed --input_format=fixed" "-I0 -i3" "for fixed input"
rc=`expr $rc + $?`

cat << eof > expect
program main
??logical::foo = .true. &
?? .or. &
?? .or. .false.
contains
??if(foo) &
?? then
   subroutine sub()
??else  if(bar) then
   subroutine sub(a)
??else
   subroutine sub(a,b)
??endif
      continue
   end subroutine
?? logical a= &
?? .true.
end program
eof

$doit "-ifree --input_format=free" "-I0 -i3" "for free input"
rc=`expr $rc + $?`
. ../postlude
exit $rc
