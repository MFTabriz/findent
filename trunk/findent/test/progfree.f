! -I2 -i5 -a1 -b2 -d3 -f4 -m5
module m1
   integer k
   enum, bind(c)

   enumerator :: red =1, blue, black =5
   enumerator yellow
   enumerator gold, silver, bronze
   enumerator :: purple
   enumerator :: pink, lavender

endenum
   type, public :: mytypea
      integer i
   end type mytypea
   integer, parameter, public :: i8=selected_int_kind(16)
contains
   function f(x)
      print *,'abc &
 def'
 print *,"abcd&
       & efgh"
 return
 end function
 integer(kind=i8) function func1(a, b)
      integer(kind=i8), intent(in) :: a, b
      func1 = a + b
   end function func1
 end module

program progfree
   type mytype  ! mytype
      integer i
      real x
   end type mytype
#ifdef abcde
   real klm(10)
#endif
   integer x(100)
   type(mytype)  xyz
   continue
    x = 3.0*a + 4*b +   &
    &   2  *c +   y
   do i=1,20
      block
         do 90 k=1,90
            do 90 k1=1,4
            call one(a)
            do 7 j=1,20
               call two(a)
             7  x=x+j
            continue
            90 continue
            continue
            end block
         enddo
               do i=1,10; do j=3,5; continue; enddo; enddo 
               do i=1,7; do j=2,2
               continue
               enddo
               continue
               enddo
               do ; enddo
         critical
         x=y
      endcritical
         critical
         x=y
      endcritical
         critical
         x=y
      end critical
            if (.false.) goto 88
            if (.false.) goto 99999
  88            if ('x' .eq. "abc''d") l=1
99999            continue
      if ('x' .eq. "abc''d") l=1
      continue
      if ('x' .eq. "abc''d")then
         continue
      endif
         ASSOCIATE ( Z => EXP(-(a**2+Y**2)) * COS(THETA))
PRINT *, A+Z, A-Z
END ASSOCIATE

      forall(i=1:4) x(i)=5
      continue
      forall(i=1:4)  ! forall
         x(i)=6
      end forall

      where(x.eq.0) x=5 ! where
      continue
      where(x.eq.0)
         x=10
      endwhere
      continue

      where(x.eq.0)
         x=10
      elsewhere
         x=11
      endwhere

      select case(ia)
      case(1)
         print *,3
         do i=1,9
            continue
         enddo
      case(2)
         print*,6
      case default
         print *,0
      endselect

      end program

      subroutine one(a)
         continue
         entry myentry
         continue
         return
      end subroutine
      subroutine two(a)
         continue
         return
      endsubroutine
      subroutine three(a)
         continue
         return
      end
      subroutine four(a)
         continue
         return
      endsubroutine four
      subrou&
            &tine five
      continue
      return 
   end