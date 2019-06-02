#!/bin/bash
# if checking windows executables, we start the wineserver here
# and make it persistent for 3 seconds to speed things up
echo "$WINDOWS" > /tmp/aap
if test xyes = x"$WINDOWS" ; then
   wineserver -p3
fi
exit 0
