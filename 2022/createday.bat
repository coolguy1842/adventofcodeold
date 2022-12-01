@echo off

IF 1%1 NEQ +1%1 goto invalidargs

if "%1" == "" goto noargs
goto args

:args
set folderCount=%1
goto createday

:noargs
SETLOCAL EnableDelayedExpansion

set folderCount=1
for /d %%d in (dayinputs\*.*) do (
    set /A folderCount=folderCount+1
)

goto createday

:createday
if not exist "%CD%\dayinputs\%folderCount%" mkdir %CD%\dayinputs\%folderCount% > nul

.\aoc read -o -p %CD%\dayinputs\%folderCount%\puzzle.md -d %folderCount% > nul
.\aoc download -o -i %CD%\dayinputs\%folderCount%\input -d %folderCount%
exit

:invalidargs
echo Invalid number
exit