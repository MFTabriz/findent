#!/bin/bash
# vim: indentexpr=none
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

# test 2018 critical(stat = istat)
cat << eof > prog 
program pcritical
critical(stat=istat)
continue
end critical
end
eof

cat << eof > expect
program pcritical
   critical(stat=istat)
       continue
   end critical
end
eof

../doit "--indent-critical=4 -x4" "-ifree"
rc=`expr $rc + $?`

# test 2018 change team(), end team [()]
cat << eof > prog 
program pchangeteam
change team(newteam)
continue
end team
continue
change team(newteam)
continue
end team (stat=istat)
l: change team(newteam)
continue
end team (stat=istat) l
k: change team(newteam)
continue
end team k
end
eof

cat << eof > expect
program pchangeteam
   change team(newteam)
       continue
   end team
   continue
   change team(newteam)
       continue
   end team (stat=istat)
   l: change team(newteam)
       continue
   end team (stat=istat) l
   k: change team(newteam)
       continue
   end team k
end
eof

../doit "--indent-changeteam=4 --indent_changeteam=4" "-ifree"
rc=`expr $rc + $?`

. ../postlude

exit $rc
