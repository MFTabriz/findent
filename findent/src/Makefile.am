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
	@echo ""
	@echo "**********************************************************"
	@echo "*** Apparently, parser.y has been changed, so we need  ***"
	@echo "*** to re-create the parser. However, at configuration ***"
	@echo "*** time, bison (or yacc) was not available, or it was ***"
	@echo "*** specified not to use bison.                        ***"
	@echo "*** I will use the pre-build parser.                   ***"
	@echo "**********************************************************"
	@echo sleeping 10 seconds so you can read this.
	@sleep 10
	touch $@

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
	@echo ""
	@echo "*********************************************************"
	@echo "*** Apparently, lexer.l has been changed, so we need  ***"
	@echo "*** to re-create the lexer. However, at configuration ***"
	@echo "*** time, flex (or lex) was not available, or it was  ***"
	@echo "*** specified not to use flex.                        ***"
	@echo "*** I will use the pre-build lexer.                   ***"
	@echo "*********************************************************"
	@echo sleeping 10 seconds so you can read this.
	@sleep 10
	touch $@

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
