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

cat << eof > prog
program prog
include "a.inc"
include 'b.inc'
?? include 'c.inc'
??include "d.inc"
#include "e.inc"
# include <f.inc>
    end
eof
cat << eof > expect
inc a.inc
inc b.inc
cpp e.inc
std f.inc
coc c.inc
coc d.inc
eof

../doit "--deps" "-ifree" ""
rc=`expr $rc + $?`

cat << eof > prog
       program prog
       include "a.inc"
       include 'b.inc'
?? include 'c.inc'
??include "d.inc"
#include "e.inc"
# include <f.inc>
 end
eof
cat << eof > expect
inc a.inc
inc b.inc
cpp e.inc
std f.inc
coc c.inc
coc d.inc
eof

../doit "--deps" "-ifixed" ""
rc=`expr $rc + $?`

cat << eof > main.f90
module mm
integer i
end
program main
use mymod
use mm
include "file.inc"
#include "one.inc"
continue
end
eof
cat << eof > sub.f90
module mymod
integer x
contains
subroutine sub
continue
end subroutine
end module
module mymod1
interface
real module function f(a)
real a
end function
end interface
end module
eof
cat << eof > sub1.f90
submodule (mymod1) mymod2
contains
module procedure f
f = 10.0
end procedure
end submodule
eof
cat << eof |sort >  expect
sub1.lo: sub.lo
main.lo: sub.lo
main.lo: file.inc one.inc
eof
touch file.inc one.inc
# remove '\r' to facilitate dos executable
$FINDENT --makefdeps | tr -d '\r' > makefdeps.sh
chmod +x makefdeps.sh
./makefdeps.sh -s .lo main.f90 sub.f90 sub1.f90 | tr -d '\r' | sort > result
if cmp -s expect result ; then
   echo "--makefdeps : OK"
else
   echo "--makefdeps : NOT OK"
   echo "expected:"
   cat expect
   echo "got:"
   cat result
   rc=`expr $rc + 1`
fi

. ../postlude
exit $rc
