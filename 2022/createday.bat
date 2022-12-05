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
rem wip
if exist %CD%\days\day%folderCount%.h (
    rem file exists
        
    SETLOCAL DisableDelayedExpansion

    del test.txt
        
    for /f "usebackq delims=" %%a in (%CD%\days\day%folderCount%.h) do (
        SETLOCAL EnableDelayedExpansion
        set str=%%a 
        set str=!str:REPLACENUM=%folderCount%!

        if !str! == "" (
            echo( >> test.txt
        )
        else (
            echo !str! >> test.txt
        )
    )


) 
else (
    copy %CD%\days\daytemplate.h %CD%\days\day%folderCount%.h       
)
exit

:invalidargs
echo Invalid number
exit