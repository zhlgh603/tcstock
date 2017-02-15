@echo off
for %%i in (./ui_*.*) do (
echo %%i
call :fix %%i
)
pause

goto end

:fix
set n=%1
set n=%n:ui_=%
echo %n%.

ren %1 %n%

goto end

:end