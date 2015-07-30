AM_LDFLAGS =

PARREPORTFILE  = parser_report.txt

PARYFILE   = parser.y
PARCFILE   = parser.cpp
PARHFILE   = parser.h
PARCFILES  = $(PARCFILE) $(PARHFILE)

LEXLFILE   = lexer.l
LEXCFILE   = lexer.cpp
LEXCFILES  = $(LEXCFILE)

$(PARHFILE): $(PARCFILE)

$(PARCFILE): $(PARYFILE)
	$(YACC) -o $@ --report=all --report-file=$(PARREPORTFILE) --defines=$(PARHFILE) $<

$(LEXCFILES): $(LEXLFILE)
	$(LEX) -i -o $@ $<

MOSTLYCLEANFILES =

CLEANFILES = $(LEXCFILES) $(PARCFILES) $(PARREPORTFILE) findent findent.exe test/*.try.f test/a.out test/*.mod 

DISTCLEANFILES = 

MAINTAINERCLEANFILES = $(CLEANFILES)

findent.o: parser.h

f_sources = findent.cpp lexer.cpp parser.cpp line_prep.cpp

bin_PROGRAMS        = findent
findent_SOURCES     = $(f_sources)

TESTS = test.sh
