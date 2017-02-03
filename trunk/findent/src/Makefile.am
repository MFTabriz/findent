AM_LDFLAGS =

PARFILES      =      parser.cpp      parser.h
BUILDPARFILES = buildparser.cpp buildparser.h

LEXFILES      =      lexer.cpp
BUILDLEXFILES = buildlexer.cpp

if USEBISON
parser.cpp parser.h: parser.y
	$(YACC) -o parser.cpp -d $<
	if test -f parser.cpp.h ; then mv parser.cpp.h parser.h ; fi
	if test -f parser.hpp ; then mv parser.hpp parser.h ; fi
	if test -f buildparser.cpp.in ; \
	   then  cp parser.cpp buildparser.cpp.in ; fi
	if test -f buildparser.h.in ; \
	   then cp parser.h buildparser.h.in ; fi
	if test -f dummyparser ; then touch dummyparser ; fi
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
	@echo sleeping 5 seconds so you can read this.
	@sleep 5
	touch $@

parser.cpp: buildparser.cpp dummyparser 
	cp $< $@

parser.h: buildparser.h dummyparser
	cp $< $@
endif

if USEFLEX
lexer.cpp: lexer.l
	$(LEX) -i -o $@ $<
	if test -f buildlexer.cpp.in ; \
	   then cp lexer.cpp buildlexer.cpp.in ; fi
	if test -f dummylexer ; then touch dummylexer ; fi
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
	@echo sleeping 5 seconds so you can read this.
	@sleep 5
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
findent_SOURCES = findent.cpp lexer.cpp parser.cpp \
		  line_prep.cpp pre_analyzer.cpp debug.h \
		  line_prep.h pre_analyzer.h version.h \
		  findent.h simpleostream.h

EXTRA_DIST  = lexer.l parser.y
