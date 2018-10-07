#!/bin/sh
# vim: indentexpr=none
# tests according to "Modern Fortran explaned" ISBN 978-0-19-881188-6
if test -e prelude ; then
   . ./prelude
else
   . ./debian/tests/prelude
fi
rc=0
cat << eof > prog
! if statement and if construct. pp 55-57
  program p_if
logical a,b

  if(a) continue

  if(a) then
  continue
  endif

  if (a) then
  continue
  else
  continue
  endif

  if (a) then
  continue
  elseif (b) then
  continue
  else
  continue
  endif

  l1: if(a) then
  continue
  endif l1

  l2: if (a) then
  continue
  else l2
  continue
  endif l2

  l3: if (a) then
  continue
  else if (b) then l3
  continue
  else l3
  continue
  endif l3
  continue
  end
eof
cat << eof > expect
! if statement and if construct. pp 55-57
  program p_if
     logical a,b

     if(a) continue

     if(a) then
          continue
     endif

     if (a) then
          continue
     else
          continue
     endif

     if (a) then
          continue
     elseif (b) then
          continue
     else
          continue
     endif

     l1: if(a) then
          continue
     endif l1

     l2: if (a) then
          continue
     else l2
          continue
     endif l2

     l3: if (a) then
          continue
     else if (b) then l3
          continue
     else l3
          continue
     endif l3
     continue
  end
eof

../doit "-f5 --indent-if=5 --indent_if=5 " "-ifree -Ia"
rc=`expr $rc + $?`

cat << eof > prog
! case construct pp 57-59
    program p_case
    integer i
    select case (i)
    case (3)
    continue
    case (4)
    continue
    case default
    continue
    end select

    l1: select case (i)
    case (3) l1
    continue
    case (4) l1
    continue
    case default l1
    continue
    end select l1
    end
eof
cat << eof > expect
! case construct pp 57-59
    program p_case
       integer i
       select case (i)
          case (3)
            continue
          case (4)
            continue
          case default
            continue
       end select

       l1: select case (i)
          case (3) l1
            continue
          case (4) l1
            continue
          case default l1
            continue
       end select l1
    end
eof

../doit "-s5 --indent-select=5 --indent_select=5 " "-ifree -Ia"
rc=`expr $rc + $?`

cat << eof > prog
! do construct pp 59-63
    program p_do
    do i=1,10
    continue
    enddo

    l1: do i=1,10,2
    continue
    enddo l1

    do , i=1,10
    continue
    end do

    l2: do, i=1,10,2
    continue
    end do l2

continue
    end
eof
cat << eof > expect
! do construct pp 59-63
    program p_do
       do i=1,10
            continue
       enddo

       l1: do i=1,10,2
            continue
       enddo l1

       do , i=1,10
            continue
       end do

       l2: do, i=1,10,2
            continue
       end do l2

       continue
    end
eof

../doit "-d5 --indent-do=5 --indent_do=5 " "-ifree -Ia"
rc=`expr $rc + $?`

cat << eof > prog
! Main program pp 70-71
    program p_main
    continue
    end program main
    program p_main1
    continue
    end program
    program p_main2
    continue
    contains
    subroutine mysub
    continue
    end
    end
eof
cat << eof > expect
! Main program pp 70-71
    program p_main
         continue
    end program main
    program p_main1
         continue
    end program
    program p_main2
         continue
      contains
         subroutine mysub
              continue
         end
    end
eof

../doit "-r5 --indent-procedure=5 --indent_procedure=5 " "-ifree -Ia"
rc=`expr $rc + $?`

cat << eof > prog
! External subprograms pp 72-73
   subroutine p_sub1
   continue
   contains
   subroutine mysub
   continue
   end
   end subroutine p_sub1

   real function myfunc()
   continue
   contains
   subroutine asub(x)
   continue
   end subroutine asub
   end function myfunc
eof
cat << eof > expect
! External subprograms pp 72-73
   subroutine p_sub1
        continue
     contains
        subroutine mysub
             continue
        end
   end subroutine p_sub1

   real function myfunc()
        continue
     contains
        subroutine asub(x)
             continue
        end subroutine asub
   end function myfunc
eof

../doit "-r5 --indent-procedure=5 --indent_procedure=5 " "-ifree -Ia"
rc=`expr $rc + $?`

cat << eof > prog
! Modules pp 73-75
   module p_module
   integer i
   contains
   subroutine mysub
   continue
   end subroutine mysub
   end

   module p_module1
   integer j
   contains
   real function myfunc(x)
   continue
   myfunc=x
   end function
   end module p_module1

   module p_module2
   integer k
   contains
   real function afunc(x)
   continue
   myfunc=x*k
   end function
   end module
eof
cat << eof > expect
! Modules pp 73-75
   module p_module
        integer i
     contains
        subroutine mysub
           continue
        end subroutine mysub
   end

   module p_module1
        integer j
     contains
        real function myfunc(x)
           continue
           myfunc=x
        end function
   end module p_module1

   module p_module2
        integer k
     contains
        real function afunc(x)
           continue
           myfunc=x*k
        end function
   end module
eof

../doit "-m5 --indent-module=5 --indent_module=5 " "-ifree -Ia"
rc=`expr $rc + $?`

cat << eof > prog
! Arguments of procedures pp 76-83
      subroutine s_arguments(x,y)
  integer, intent(inout) :: x,y
  continue
  end

    integer function f_arguments(x,y,z)
    integer x,y,z
    f_arguments = x+y+z
    end
eof
cat << eof > expect
! Arguments of procedures pp 76-83
      subroutine s_arguments(x,y)
           integer, intent(inout) :: x,y
           continue
      end

      integer function f_arguments(x,y,z)
           integer x,y,z
           f_arguments = x+y+z
      end
eof

../doit "-r5 --indent-procedure=5 --indent_procedure=5 " "-ifree -Ia"
rc=`expr $rc + $?`

cat << eof > prog
! Explicit and implicit interfaces pp 83-84
      program p_interface
      interface inter
      subroutine s(x)
      real x
      end
      end interface inter

      interface
      subroutine y(x)
      real x
      end
      end interface
      end program
eof
cat << eof > expect
! Explicit and implicit interfaces pp 83-84
      program p_interface
         interface inter
              subroutine s(x)
                 real x
              end
         end interface inter

         interface
              subroutine y(x)
                 real x
              end
         end interface
      end program
eof

../doit "-j5 --indent-interface=5 --indent_interface=5 " "-ifree -Ia"
rc=`expr $rc + $?`

cat << eof > prog
! Direct recursion pp 92-93
     recursive function f_recur(n) result(i)
     integer i,n
     i = n
     end function
eof
cat << eof > expect
! Direct recursion pp 92-93
     recursive function f_recur(n) result(i)
          integer i,n
          i = n
     end function
eof

../doit "-r5 --indent-procedure=5 --indent_procedure=5 " "-ifree -Ia"
rc=`expr $rc + $?`

cat << eof > prog
! Overloading and generic interfaces pp 94-99
  program p_overload
  interface doit
  real function doit1(x)
  real x
  end function doit1
  real function doit2(x,y)
  real x,y
  end function doit2
  end interface doit
  interface operator(*)
  logical function myand(a,b)
  logical, intent(in) :: a,b
  end function myand
  end interface operator(*)
  end
eof
cat << eof > expect
! Overloading and generic interfaces pp 94-99
  program p_overload
     interface doit
          real function doit1(x)
             real x
          end function doit1
          real function doit2(x,y)
             real x,y
          end function doit2
     end interface doit
     interface operator(*)
          logical function myand(a,b)
             logical, intent(in) :: a,b
          end function myand
     end interface operator(*)
  end
eof

../doit "-j5 --indent-interface=5 --indent_interface=5 " "-ifree -Ia"
rc=`expr $rc + $?`

cat << eof > prog
! The subroutine and function statements pp 99-101
      program p_subroutine
end
      integer(4), pure elemental function myfunc(x)
      integer, intent(in) ::  x
      myfunc = x
      end function

      pure function pfunc(x) result(y)
      real*8, intent(in) :: x
      real*8 y
      y=x
      end

      elemental subroutine mysub(i)
      integer, intent(inout) :: i
      i = 2*i
      continue
      end subroutine mysub

      pure subroutine psub(x,y)
      real, intent(inout) :: x
      real, intent(in) :: y
      x = x*y
      continue
      end
eof
cat << eof > expect
! The subroutine and function statements pp 99-101
      program p_subroutine
      end
      integer(4), pure elemental function myfunc(x)
      integer, intent(in) ::  x
      myfunc = x
   end function

   pure function pfunc(x) result(y)
        real*8, intent(in) :: x
        real*8 y
        y=x
   end

   elemental subroutine mysub(i)
        integer, intent(inout) :: i
        i = 2*i
        continue
   end subroutine mysub

   pure subroutine psub(x,y)
        real, intent(inout) :: x
        real, intent(in) :: y
        x = x*y
        continue
   end
eof

../doit "-r5 --indent-procedure=5 --indent_procedure=5 " "-ifree -Ia"
rc=`expr $rc + $?`

cat << eof > prog
! The where statement and construct pp 123-126
    program p_where
    real a(10)
    where(a /= 0) a=1/a

    where (a /= 0)
    a=1/a
    end where

       where (a /= 0)
            a=1/a
         elsewhere
            a=9
       end where

    where (a == 0)
    a = 1
    elsewhere (a > -1)
    a=0.5
    elsewhere (a > 4)
    a=3
    end where

    l1: where (a /= 0)
    a=1/a
    end where l1

    l2: where (a == 0)
    a = 1
    elsewhere (a /= 24 )l2
    a=0.5
    elsewhere (a > 4) l2
    a=3
    end where l2 

       l3:where (a /= 0)
            a=1/a
            elsewhere l3
            a=9
         end where l3

    end
eof
cat << eof > expect
! The where statement and construct pp 123-126
    program p_where
       real a(10)
       where(a /= 0) a=1/a

       where (a /= 0)
            a=1/a
       end where

       where (a /= 0)
            a=1/a
       elsewhere
            a=9
       end where

       where (a == 0)
            a = 1
       elsewhere (a > -1)
            a=0.5
       elsewhere (a > 4)
            a=3
       end where

       l1: where (a /= 0)
            a=1/a
       end where l1

       l2: where (a == 0)
            a = 1
       elsewhere (a /= 24 )l2
            a=0.5
       elsewhere (a > 4) l2
            a=3
       end where l2

       l3:where (a /= 0)
            a=1/a
       elsewhere l3
            a=9
       end where l3

    end
eof

../doit "-w5 --indent-where=5 --indent_where=5 " "-ifree -Ia"
rc=`expr $rc + $?`
. ../postlude

exit $rc
