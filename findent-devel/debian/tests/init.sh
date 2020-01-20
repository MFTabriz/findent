#!/bin/sh
# if checking windows executables, we start the wineserver here
# and make it persistent for some seconds to speed things up
if test xyes = "x$WINDOWS" ; then
   wineserver -p10
fi
exit 0
