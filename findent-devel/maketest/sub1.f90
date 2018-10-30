   module mymod1
   contains
      subroutine sub1
         print *,'this is sub1'
      end subroutine sub1
   end module mymod1
   module mymod
      interface
         module subroutine sub
         end subroutine sub
      end interface
   end module mymod
