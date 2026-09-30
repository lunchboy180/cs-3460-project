@echo off
setlocal

if "%VCPKG_ROOT%"=="" (
    echo Error: VCPKG_ROOT is not set.
    echo Example:
    echo   set VCPKG_ROOT=C:\dev\vcpkg
    exit /b 1
)

cmake --preset default
if errorlevel 1 exit /b 1

cmake --build --preset default
if errorlevel 1 exit /b 1
