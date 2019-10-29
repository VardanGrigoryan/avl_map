@echo off
setlocal

:loop
if x%1 equ x goto done
set arg=%1
if %arg:~0,1% equ - goto check_arguments
:Incorrect_Argument
echo Error:: Incorrect argument %1

:next
shift /1
goto loop

:check_arguments
if "%1" equ "-l" goto get_limit
goto Incorrect_Argument

:get_limit
shift /1
set limit=%1
goto next

:done

if exist "build" (
	rmdir /s /q build build
)
mkdir build && cd build

cmake -G "Visual Studio 15 2017" -D_LIMIT_=%limit% ..
cd ..

