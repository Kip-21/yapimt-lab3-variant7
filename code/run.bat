@echo off
call "%~dp0build.bat"
if errorlevel 1 (
    pause
    exit /b 1
)
"%~dp0build\lab3.exe"
set "LAB3_EXIT=%ERRORLEVEL%"
echo.
echo Exit code: %LAB3_EXIT%
pause
exit /b %LAB3_EXIT%
