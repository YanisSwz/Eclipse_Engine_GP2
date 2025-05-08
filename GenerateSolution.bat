@echo OFF
set BUILD_DIR=Build

call "%~dp0UpdateSubmodules.bat"

REM Deletes the old build folder
if exist %BUILD_DIR% (
    rmdir /s /q %BUILD_DIR%
)

REM Creates a new build folder
mkdir %BUILD_DIR%
cd %BUILD_DIR%

REM Generates the visual studio solution
cmake --preset "VS_2022" ".."

echo Visual Studio 2022 solution generated

pause
