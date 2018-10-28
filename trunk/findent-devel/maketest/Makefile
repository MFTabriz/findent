SRCS = main.f90 sub1.f90 sub2.f90
OBJS = $(SRCS:.f90=.o)
%.o: %.f90
	gfortran -c -o $@ $<
program: $(OBJS)
	gfortran -o $@ $(OBJS)
include deps
dep deps:
	bash -c "bash <( findent --makefdeps ) $(SRCS)" > deps
clean: 
	rm -f *.o *.mod *.smod program deps
