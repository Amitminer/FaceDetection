@echo off
setlocal

REM Define the generator variable
REM Visual Studio 17 2022 or MinGW Makefiles
set "generator=Visual Studio 17 2022"
set "toolchainPath=P:\AppData\Roaming\ProgrammingTools\vcpkg\scripts\buildsystems\vcpkg.cmake"
REM Run CMake configuration for main project
echo Running CMake configuration for main project...
if not exist build (
    mkdir build
)
cd build

REM Path to the vcpkg toolchain file. (DCMAKE_TOOLCHAIN_FILE="path of toolchain")
REM Make sure this path is correct and points to the vcpkg toolchain file.
REM This toolchain file is used by CMake to integrate with vcpkg for package management.
REM Choose desired generator
cmake .. -G "%generator%" -DCMAKE_TOOLCHAIN_FILE="%toolchainPath%"
if %errorlevel% neq 0 (
    echo CMake configuration failed.
    cd ..
    goto :error
)

REM Build the main project using CMake
echo Building the main project...
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo Build failed.
    goto :error
)

echo Script completed successfully
goto :end

:error
echo An error occurred during script execution
:end
endlocal
