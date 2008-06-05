@echo off
setlocal

set tmpbin=tmp.bin
set comport=COM1

if "%1" == "" goto help
if not "%2" == "" set comport=%2

if not exist %tmpbin% goto compile
del %tmpbin%

:compile
echo compile %1...
tools\jsc -Btmp.bin %1

if exist %tmpbin% goto write
goto end

:write
echo connect the target board on %comport% and
echo power off/on it then press any key as soon as possible!
pause
tools\avrdude -v -p m128 -c stk500 -b 9600 -P %comport% -U eeprom:w:%tmpbin%:r

goto end

:help
echo usage:   build[.bat] source_filename [comport]
echo          source_file      path to js source file
echo          comport          string "COMx" for write bytecode
echo                           default is COM1

:end
endlocal
