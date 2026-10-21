@echo off
setlocal

set "VSDEV_CMD="
for %%P in (
    "%ProgramFiles%\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat"
    "%ProgramFiles%\Microsoft Visual Studio\18\Professional\Common7\Tools\VsDevCmd.bat"
    "%ProgramFiles%\Microsoft Visual Studio\18\Enterprise\Common7\Tools\VsDevCmd.bat"
    "%ProgramFiles%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
    "%ProgramFiles%\Microsoft Visual Studio\2022\Professional\Common7\Tools\VsDevCmd.bat"
    "%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat"
    "%ProgramFiles%\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat"
    "%ProgramFiles%\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat"
    "%ProgramFiles(x86)%\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat"
    "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat"
) do if not defined VSDEV_CMD if exist "%%~P" set "VSDEV_CMD=%%~P"

if not defined VSDEV_CMD (
    echo Error: Visual Studio C++ build tools were not found.
    echo Install the Desktop development with C++ workload and try again.
    exit /b 1
)

call "%VSDEV_CMD%" -arch=x64 -host_arch=x64
if errorlevel 1 exit /b 1

if "%VCPKG_ROOT%"=="" (
    echo Error: VCPKG_ROOT is not set.
    echo Example:
    echo   set VCPKG_ROOT=C:\dev\vcpkg
    exit /b 1
)

cmake --preset default
if errorlevel 1 exit /b 1

cmake --build --preset default --clean-first
if errorlevel 1 exit /b 1
