! -Ia -i5 -a1 -b2 -d3 -f4 -m5 -ifree -ofixed
   module m1
        integer k
        enum, bind(c)

             enumerator :: red =1, blue, black =5
             enumerator yellow
             enumerator gold, silver, bronze
             enumerator :: purple
             enumerator :: pink, lavender

        endenum
   contains
        function f(x)
             print *,'abc&
             &      def'
             print *,"abcd&
#ifdef foo
   garbage &
#endif
             &        efgh"
             return
        end function
#ifdef usempi
        function f1(x,m)
             real x,m
#elif defined(useopenmp)
        function f1(x,m,n)
             real x,m,n
#else
        function f1(x)
             real x
#endif
             continue
        end function f1
   end module

   program progfixed
        type mytype  ! mytype
             integer i
! a comment
             ! a floating comment
             real x
        end type mytype
#ifdef abcde
        real klm@@@(10)
#endif
        real do(100)
        integer x(100)
        type(mytype)  xyz
        character*1000 astring
        continue
        a_ap: do i=1,20
           continue
        enddo a_ap
        end = 10
        if ( e .eq. n .and.&
        &     e .eq. m    )then
            npar   = npar   + 1
        endif
        do i=1,&
! a comment
! a comment
        &1&
! a comment
        &0
           continue
        enddo
        do 123 i=1,2
           continue
123     continue
        print *,'; function ',indx," function "
        continue
99880   FORMAT ('  function ')
99870   FORMAT(1X,'Invalid species name',2X,A8)
        do i=1,10
           do (i) = 5
           continue
           do(i) = 5
           continue
        enddo
        x = y   ! function values
        continue

        astring = " ! this&
        & is&
        & no comment!"
        print *,a,b,&
        &        c,d&
        &       ,e,f
        continue
        print *,a,b,&
        &        c,d&
        &       ,e,f
        loop: do i=1,20
           block
             do 90 k=1,90
                do 90 k1=1,4
                   call one(a)
                   do 7 j=1,20
                      call two(a)
7                  x=x+j
                   continue
90           continue
             continue
           end block
        enddo loop

        bbb: block
          continue
        end block bbb

        sc: select case(ja)
          case(1)
             continue
          case(2)
             continue
        end select sc
        continue
        do i=1,20
           block
             continue
           end block
        enddo
        critical
             x=y
        endcritical
        critical
             x=y
        endcritical
        critical
             x=y
        end critical
        wv: if ( a.eq.b) then
            continue
        endif wv
        if (.false.) goto 88
        if (.false.) goto 99999
88      if ('x' .eq. "abc''d") l=1
99999   continue
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
!d         print *,'debug i=',i
!
!D         print *,'debug j=',j
        x = 4 +&
! next line starts with <tab>
	&5 +&
! next line starts with <sp><tab>
 	&5+&
! next line starts with <sp><sp><tab>
  	&5+&
! next line starts with <sp><sp><sp><tab>
   	&5+&
! next line starts with <sp><sp><sp><sp><tab>
    	&5+&
! next line starts with <sp><sp><sp><sp><sp><tab>
     	&5
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
   subroutine seven
        a = 1&
        &+ 2   &! comment 1
        &+ 3   &! comment 2
        &+ 4&
        &+ 5&
        &+ 6
        a = 1&
        &+ 2   &! comment 1
        &+ 3   &! comment 2
#ifdef klm
        &+ 4 syntax error&
        &+ 5 syntax error&
#endif
        &+ 6
   end

   subroutine multiline_preproc

#ifdef one\
two\
three
        do i=1,10
#elif \
defined(q)
        do i=1,5
#else
        do i=1,7
#endif
           x=x+4
        enddo
   end

  subroutine omp
 integer i,j,k
!$ integer m,n, &
!$ o,p
print *,i,j,k
!$ print*, m,n,o,p
!$ do 100 i=1,20
!$ do 100 j=1,i
continue
!$ 100 enddo
end
