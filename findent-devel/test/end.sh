#!/bin/sh
if test xyes = x"$WINDOWS" ; then
   # wineserver will end spontaneously, no need to kill
   : #wineserver -kill
fi
exit 0
