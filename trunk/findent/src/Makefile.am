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
else
parser.cpp: buildparser.cpp 
	cp $< $@

parser.h: buildparser.h
	cp $< $@
endif

if USEFLEX
lexer.cpp: lexer.l
	$(LEX) -i -o $@ $<
	cp lexer.cpp buildlexer.cpp.in
else
lexer.cpp: buildlexer.cpp
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
