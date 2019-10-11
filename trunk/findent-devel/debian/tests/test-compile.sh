#!/bin/sh
export FINDENT_FLAGS="$TEST_FINDENT_FLAGS"
prog="$1"
echo "$0: $prog"
if test "x$FC" = x ; then
   gfortran=:
   echo "will not try to compile fortran sources"
else
   gfortran="$FC"
   echo "will try to compile fortran sources using $gfortran"
fi
rc=0
exe=${FINDENT:-../src/findent}
$exe -v
bprog="`basename $prog`"
rm -f "bprog.try.f"
echo -n "$bprog: "
case "$bprog" in
   *progfixed*) 
      format="-ffixed-form -ffixed-line-length-none -fd-lines-as-comments"
      ;;
   *) 
      format="-ffree-form -ffree-line-length-none" 
      ;;
esac

$gfortran -fcoarray=single -cpp -fopenmp $format -o prog $prog >/dev/null 2>&1
if [ $? -ne 0 ] ; then
   echo -n " original program does not compile using: -fcoarray=single -cpp -fopenmp $format -o prog $prog "
   rc=1
fi

parms=`head -n1 < $prog | tr '!' ' '|tr '\r' ' '`
$exe $parms < $prog > $bprog.try.f 2>/dev/null
if [ -f $prog.try.f.ref ]; then
   if [ "$WINDOWS" = yes ] ; then
      case $prog in
	 *dos*)
	    :
	    ;;
	 *)
	    tmpfile=`mktemp`
	    tr -d '\r' < $bprog.try.f > $tmpfile
	    mv $tmpfile $bprog.try.f
	    ;;
      esac
   fi
   cmp -s $bprog.try.f $prog.try.f.ref >/dev/null 2>&1
   if [ "$?" -eq 0 ]; then
      echo -n "OK"
   else
      echo -n "WRONG"
      rc=1
   fi
   echo
else
   echo "cannot compare"
   rc=1
fi
case "$bprog" in
   *free.f | *free1.f | *free-dos.f) 
      format="-ffree-form -ffree-line-length-none" 
      ;;
   *) 
      format="-ffixed-form -ffixed-line-length-none -fd-lines-as-comments"
      ;;
esac
$gfortran -fcoarray=single -cpp -fopenmp $format -o prog $bprog.try.f >/dev/null 2>&1
if [ $? -ne 0 ] ; then
   echo "        converted program does not compile using: -fcoarray=single -cpp -fopenmp $format -o prog $bprog.try.f "
   rc=1
fi

echo "END TESTING FINDENT rc=$rc"
if [ $rc -ne 0 ] ; then
   echo "If you are sure $PWD/$bprog.try.f is correct:"
   echo "copy $PWD/$bprog.try.f"
   echo "to the corresponding .in file in the test directory"
   echo " and configure again."
fi
rm -f prog
exit $rc
