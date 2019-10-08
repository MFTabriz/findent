#!/bin/bash
#
# this script tries to compile findent, without using the
# configure ; make ; make install 
# suite.
#
# definitions:
CPP='g++'               # C++ compiler
CPPFLAGS='-O2'          # compile flags
EXE='findent'           # name of program to create
#
echo "C++ compiler:  $CPP"
echo "compile flags: $CPPFLAGS"
echo "program:       $EXE"
SRCS="
debug.cpp
docs.cpp
findentclass.cpp
findent.cpp
findentrun.cpp
fixed.cpp
flags.cpp
fortran.cpp
fortranline.cpp
free.cpp
functions.cpp
globals.cpp
line_prep.cpp
mylexer.cpp
myparser.cpp
pre_analyzer.cpp
prop.cpp
simpleostream.cpp
"
echo "compiling, this can take some time ..."
cd src                         || exit 1
cp builtparser.h parser.h      || exit 1
cp builtparser.cpp parser.cpp  || exit 1
cp builtlexer.cpp lexer.cpp    || exit 1
$CPP $CPPFLAGS -o $EXE $SRCS   || exit 1
cd ..
cp src/$EXE .                  || exit 1
echo "succesfully created: $EXE"
echo "copy this file to the desired directory, for example"
echo "  cp $EXE \$HOME/bin"
echo "or"
echo "  cp $EXE \$HOME/.local/bin"
echo "or"
echo "  cp $EXE /usr/local/bin"
