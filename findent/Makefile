PROG      = findent

all:        $(PROG)

CPP       = g++
CPPFLAGS  = -Wall -g -O2 
INCLUDES  = $(PROG).h $(PROG)_parser.h version.h
LD        = $(CPP)
YACC      = bison
LEX       = flex

$(PROG): $(PROG)_parser.o $(PROG)_lexer.o
	$(LD) -o $@ $(PROG)_parser.o $(PROG)_lexer.o
	
$(PROG)_parser.cpp $(PROG)_parser.h: $(PROG).y
	$(YACC) -o $(PROG)_parser.cpp --defines=$(PROG)_parser.h $<

$(PROG)_lexer.cpp: $(PROG).l
	$(LEX) -i -o $@ $<

%o:     %cpp $(INCLUDES) 
	$(CPP) -c $(CPPFLAGS) -o $@ $<


clean:
	rm -f $(PROG)_lexer.cpp *.o $(PROG) $(PROG)_parser.h $(PROG)_parser.cpp
	rm -f test/*.f.try.f test/a.out test/*.mod

test:   all
	cd test; ./tester

.SUFFIXES:

.PHONY: test
