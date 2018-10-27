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

. ../postlude
exit $rc
