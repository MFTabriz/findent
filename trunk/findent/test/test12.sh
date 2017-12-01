#!/bin/sh
rc=0
for flag in -h --help ; do
   ../src/findent "$flag" | head -n 1 > help.try
   cmp -s help.ref help.try
   r=$?
   if [ $r -eq 0 ] ; then
      echo "$flag : works OK"
   else
      echo "$flag : works NOT OK, compare help.try and help.ref"
   fi
   rc=`expr $rc + $r` 
done

for flag in -H --manpage ; do
   ../src/findent "$flag" | head -n 1 > manpage.try
   cmp -s manpage.ref manpage.try
   r=$?
   if [ $r -eq 0 ] ; then
      echo "$flag : OK"
   else
      echo "$flag : NOT OK, compare manpage.try and manpage.ref"
   fi
   rc=`expr $rc + $r` 
done

for flag in -v --version ; do
   ../src/findent $flag > result
   if grep -q "^findent version" result ; then
      echo "$flag: OK"
   else
      echo "$flag : NOT OK"
      echo "expected : findent version ..."
      echo "got:"
      cat result
      rc=`expr $rc + 1`
   fi
done

exit $rc
