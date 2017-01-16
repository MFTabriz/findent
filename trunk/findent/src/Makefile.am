AM_LDFLAGS =

PARFILES      =      parser.cpp      parser.h
BUILDPARFILES = buildparser.cpp buildparser.h

LEXFILES      =      lexer.cpp
BUILDLEXFILES = buildlexer.cpp

if USEBISON
parser.h: parser.cpp

parser.cpp: parser.y
	$(YACC) -o $@ -d $<
	if test -f parser.cpp.h ; then mv parser.cpp.h parser.h ; fi
	if test -f parser.hpp ; then mv parser.hpp parser.h ; fi
	cp parser.cpp buildparser.cpp.in
	cp parser.h buildparser.h.in
	touch dummyparser
else
dummyparser: parser.y
	@echo "***************************************************************"
	@echo "*** Need to create parser, but during configuration was     ***"
	@echo "*** specified not to use bison, or bison was not available. ***"
	@echo "*** Please correct this, and configure again.               ***"
	@echo "***************************************************************"
	exit 1

parser.cpp: buildparser.cpp dummyparser 
	cp $< $@

parser.h: buildparser.h dummyparser
	cp $< $@
endif

if USEFLEX
lexer.cpp: lexer.l
	$(LEX) -i -o $@ $<
	cp lexer.cpp buildlexer.cpp.in
	touch dummylexer
else
dummylexer: lexer.l
	@echo "*************************************************************"
	@echo "*** Need to create lexer, but during configuration was    ***"
	@echo "*** specified not to use flex, or flex was not available. ***"
	@echo "*** Please correct this, and configure again.             ***"
	@echo "*************************************************************"
	exit 1

lexer.cpp: buildlexer.cpp dummylexer
	cp $< $@
endif

MOSTLYCLEANFILES =

CLEANFILES = $(LEXFILES) $(PARFILES) findent findent.exe test/*.try.f test/a.out test/*.mod findent.1 parser.cpp.h parser.hpp parser_report.txt


DISTCLEANFILES = 

MAINTAINERCLEANFILES = $(BUILDPARFILES) $(BUILDLEXFILES)

if MAKEMAN

man1_MANS = findent.1

findent.1: findent
	./findent -H > $@

endif

findent.o: parser.h

bin_PROGRAMS    = findent
findent_SOURCES = findent.cpp lexer.cpp parser.cpp line_prep.cpp pre_analyzer.cpp
