@echo off
setlocal
cd /d "%~dp0"

rem Use the x86 C++ compiler and MASM from Visual Studio.
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" goto noTools
set "LAB3_VS="
for /f "usebackq delims=" %%I in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "LAB3_VS=%%I"
if not defined LAB3_VS goto noTools
call "%LAB3_VS%\VC\Auxiliary\Build\vcvars32.bat"
if errorlevel 1 exit /b 1

if not exist build mkdir build
ml /nologo /c /coff /Fo"build\palindrome.obj" palindrome.asm
if errorlevel 1 exit /b 1
cl /nologo /W4 /EHsc /utf-8 /std:c++17 /Fo"build\main.obj" /Fe"build\lab3.exe" main.cpp build\palindrome.obj /link /MACHINE:X86 /INCREMENTAL:NO
if errorlevel 1 exit /b 1
echo Built build\lab3.exe
exit /b 0

:noTools
echo Install Visual Studio or Build Tools with Desktop development with C++.
exit /b 1
