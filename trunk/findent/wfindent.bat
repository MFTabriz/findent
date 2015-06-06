@echo off
setlocal EnableDelayedExpansion
if -%1-==-- (
  echo wfindent is a wrapper for findent
  echo usage: wfindent [ findent-args ] filenames
  echo example:
  echo wfindent -ifree -i4 *.f90
  echo for a complete list of findent-args, type
  echo   findent -h
  goto bend
)
set fargs=
:astart
if -%1-==-- goto bend
set aa=%1
if %aa:~0,1%==- (
   set fargs=%fargs% %aa%
   shift
   goto astart
)

:bstart
if -%1-==-- goto bend
if exist %1 goto one
echo file %1 does not exist
goto bend
:one
for %%a in (%1) do ( 
   echo indenting %fargs% %%a
   findent %fargs% < %%a  > %%a~
   find /v /c "" < %%a > counter1.cnt
   find /v /c "" < %%a~ > counter2.cnt
   set /p counter1=<counter1.cnt
   set /p counter2=<counter2.cnt
   if !counter1! neq !counter2! ( echo something wrong, file unmodified
   ) else ( copy /Y %%a~ %%a >nul )
   if exist %%a~ del %%a~ 
   if exist counter1.cnt del counter1.cnt
   if exist counter2.cnt del counter2.cnt
)
shift
goto bstart
:bend
pause
