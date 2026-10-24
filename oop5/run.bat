@echo off
cd /d "%~dp0"
g++ optimization.cpp -o optimization.exe
if errorlevel 1 (
    echo.
    echo Build that bai, xem loi o tren.
    pause
    exit /b 1
)
optimization.exe
pause
