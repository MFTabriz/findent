SRCS = main.f90 sub1.f90 sub2.f90
OBJS = $(SRCS:.f90=.o)
%.o: %.f90
	gfortran -c -o $@ $<
program: $(OBJS)
	gfortran -o $@ $(OBJS)
include deps
dep deps:
	findent --makefdeps < /dev/null > makefdeps.sh
	@if [ "`head -n 1 makefdeps.sh`" != "#!/bin/bash" ] ; then \
	   findent -v 1>&2; \
	   echo "Use findent version >= 3.0.0" 1>&2 ; exit 1 ; fi
	chmod +x makefdeps.sh
	./makefdeps.sh $(SRCS) > deps
clean: 
	rm -f *.o *.mod *.smod program deps
