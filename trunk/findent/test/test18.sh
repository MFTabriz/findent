#!/bin/sh
# test wfindent
# like wfindent, search for a suitable getopt. If no one available,
# return 77 (i.e. test skipped)

GETOPT=""
if [ "$WFINDENT_GETOPT" ]; then
   GETOPT="$WFINDENT_GETOPT"
else
   a=`getopt -T`
   if [ "$?" -eq 4 ] ; then
      GETOPT=getopt
   else
      tries="/usr/local/opt/gnu-getopt/bin/getopt /usr/local/bin/getopt /usr/local/bin/gnugetopt"
      for i in $tries ; do
         if [ -x "$i" ] ; then
            a=`"$i" -T`
            if [ "$?" -eq 4 ] ; then
               GETOPT="$i"
               break
            fi
         fi
      done
      if [ -z "$GETOPT" ] ; then
         exit 77
      fi
   fi
fi

if test -e prelude ; then
   . ./prelude
else
   unset FINDENT
   . ./debian/tests/prelude
fi
cat <<eof > prog1.f || exit 1
program prog1
continue
end program prog1
eof
cat << eof > prog2.f || exit 1
module modprog2
integer i
end module
program prog2
use modprog2
continue
end program prog2
eof
cat << eof > prog1.f.ref || exit 1
program prog1
     continue
end program prog1
eof
cat << eof > prog2.f.ref || exit 1
module modprog2
     integer i
end module
program prog2
     use modprog2
     continue
end program prog2
eof

$WFINDENT -i5 prog1.f prog2.f
tmpfile=`mktemp`
tr -d '\r' < prog1.f > $tmpfile
mv $tmpfile prog1.f
tmpfile=`mktemp`
tr -d '\r' < prog2.f > $tmpfile
mv $tmpfile prog2.f
for i in 1 2 ; do
   cmp -s prog$i.f prog$i.f.ref
   if [ $? -ne 0 ] ; then
      echo "prog$i.f and prog$i.f.ref are not equal"
      exit 1
   fi
done

. ../postlude
exit 0
