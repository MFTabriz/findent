   module mymod1
   contains
      subroutine sub1
         print *,'this is sub1'
      end
   end
   module mymod
      interface
         module subroutine sub
         end subroutine
      end interface
   end module
