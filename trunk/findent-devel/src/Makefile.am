AM_LDFLAGS =

if MAKEWIN
AM_CXXFLAGS = -static
else
AM_CXXFLAGS = -fPIC
endif

if USEESOPE
AM_CXXFLAGS += -DUSEESOPE
endif

if USEBISON
parser.cpp: parser.y
	$(YACC) -o parser.cpp -d $<
	if test -f parser.cpp.h ; then mv parser.cpp.h parser.h ; fi
	if test -f parser.hpp ; then mv parser.hpp parser.h ; fi
	
parser.h: parser.cpp

builtparser: parser.cpp
	mv parser.cpp builtparser.cpp
	mv parser.h builtparser.h

else

parser.cpp: builtparser.cpp 
	@echo ""
	@echo "********************************************************"
	@echo "*** At configuration time, bison (or yacc) was not   ***"
	@echo "*** available, or it was specified not to use bison. ***"
	@echo "*** I will use the pre-built parser.                 ***"
	@echo "********************************************************"
	cp $< $@

parser.h: builtparser.h
	cp $< $@
endif

if USEFLEX
lexer.cpp: lexer.l
	$(LEX) -i -o lexer.cpp $<

builtlexer: lexer.cpp
	mv $< builtlexer.cpp

else

lexer.cpp: builtlexer.cpp
	@echo ""
	@echo "*******************************************************"
	@echo "*** At configuration time, flex (or lex) was not    ***"
	@echo "*** available, or it was specified not to use flex. ***"
	@echo "*** I will use the pre-built lexer.                 ***"
	@echo "*******************************************************"
	cp $< $@
endif

MOSTLYCLEANFILES =

CLEANFILES = findent findent.exe findent.1 \
	     parser.cpp.h parser.hpp parser_report.txt \
	     parser.cpp parser.h lexer.cpp


MAINTAINERCLEANFILES = builtparser.cpp builtparser.h builtlexer.cpp

if MAKEMAN

man1_MANS = findent.1

findent.1: findent
	: | ./findent -H > $@

endif

findent.o: parser.h

vim_plugin.o: vim_fortran.inc vim_findent.inc vim_help.inc


gedit_plugin.o: gedit_external.inc gedit_plugin.inc gedit_plugin_py.inc \
   gedit_help.inc

emacs_plugin.o: emacs_findent.inc emacs_help.inc

readme_plugin.o: readme.inc

docs.o:    vim_fortran.inc vim_findent.inc vim_help.inc \
	   gedit_external.inc gedit_plugin.inc gedit_plugin_py.inc gedit_help.inc \
           emacs_findent.inc emacs_help.inc \
	   readme.inc makefdeps.inc

DEPSDIR   = $(top_srcdir)/deps
EMACSDIR  = $(top_srcdir)/emacs
GEDITDIR  = $(top_srcdir)/gedit
READMEDIR = $(top_srcdir)/doc
TOCPP     = $(top_srcdir)/src/tocpp.sh
VIMDIR    = $(top_srcdir)/vim

vim_fortran.inc: $(VIMDIR)/fortran.vim $(TOCPP)
	$(TOCPP) < $(VIMDIR)/fortran.vim > $@

vim_findent.inc: $(VIMDIR)/findent.vim $(TOCPP)
	$(TOCPP) < $(VIMDIR)/findent.vim > $@

vim_help.inc: $(VIMDIR)/README $(TOCPP)
	$(TOCPP) < $(VIMDIR)/README > $@

gedit_external.inc: $(GEDITDIR)/findent-gedit $(TOCPP)
	$(TOCPP) < $(GEDITDIR)/findent-gedit > $@

gedit_plugin.inc: $(GEDITDIR)/findent.plugin $(TOCPP)
	$(TOCPP) < $(GEDITDIR)/findent.plugin > $@

gedit_plugin_py.inc: $(GEDITDIR)/findent.py $(TOCPP)
	$(TOCPP) < $(GEDITDIR)/findent.py > $@

gedit_help.inc: $(GEDITDIR)/README $(TOCPP)
	$(TOCPP) < $(GEDITDIR)/README > $@

emacs_findent.inc: $(EMACSDIR)/findent.el $(TOCPP)
	$(TOCPP) < $(EMACSDIR)/findent.el > $@

emacs_help.inc: $(EMACSDIR)/README $(TOCPP)
	$(TOCPP) < $(EMACSDIR)/README > $@

readme.inc: $(READMEDIR)/README $(TOCPP)
	$(TOCPP) < $(READMEDIR)/README > $@

makefdeps.inc: $(DEPSDIR)/makefdeps $(TOCPP)
	$(TOCPP) < $(DEPSDIR)/makefdeps > $@

INCS = vim_fortran.inc vim_findent.inc vim_help.inc gedit_external.inc gedit_plugin.inc \
       gedit_plugin_py.inc gedit_help.inc emacs_findent.inc emacs_help.inc readme.inc makefdeps.inc

includes: $(INCS)

bin_PROGRAMS    = findent

findent_SOURCES = \
		  debug.cpp              debug.h           \
		  docs.cpp               docs.h            \
		  findent.cpp            findent.h         \
		                         findent_types.h   \
		  findentclass.cpp       findentclass.h    \
		  findentrun.cpp         findentrun.h      \
		  fixed.cpp              fixed.h           \
		  flags.cpp              flags.h           \
		  fortran.cpp            fortran.h         \
		  fortranline.cpp        fortranline.h     \
		  free.cpp               free.h            \
		  functions.cpp          functions.h       \
		  globals.cpp            globals.h         \
		                         lexer.h           \
		  line_prep.cpp          line_prep.h       \
		  mylexer.cpp                              \
		  myparser.cpp                             \
		                         parser.h          \
		  pre_analyzer.cpp       pre_analyzer.h    \
		  prop.cpp               prop.h            \
		  simpleostream.h        simpleostream.cpp \
                  version.h


BUILT_SOURCES = parser.cpp parser.h lexer.cpp

EXTRA_DIST  = lexer.l parser.y tocpp.sh builtparser.cpp \
	      builtparser.h builtlexer.cpp $(INCS)
