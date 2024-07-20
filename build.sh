#!/bin/bash

# Define the generator variable
# On Linux, you don't need to specify a generator for CMake as it defaults to Unix Makefiles.
# However, if you are using a different build system like Ninja, you can specify it here.
generator="Ninja"

# Path to the vcpkg toolchain file.
# Make sure this path is correct and points to the vcpkg toolchain file.
toolchain_path="vcpkg\scripts\buildsystems\vcpkg.cmake"

# Create a build directory if it doesn't exist
echo "Running CMake configuration for the main project..."
if [ ! -d build ]; then
    mkdir build
fi
cd build

# Run CMake configuration for the main project
# -G "$generator" specifies the build system generator (e.g., Ninja or Unix Makefiles).
# -DCMAKE_TOOLCHAIN_FILE specifies the path to the vcpkg toolchain file.
cmake .. -G "$generator" -DCMAKE_TOOLCHAIN_FILE="$toolchain_path"
if [ $? -ne 0 ]; then
    echo "CMake configuration failed. Check the toolchain path and other settings."
    cd ..
    exit 1
fi

# Build the main project using CMake
# --config Release specifies the build configuration (e.g., Release or Debug).
echo "Building the main project..."
cmake --build . --config Release
if [ $? -ne 0 ]; then
    echo "Build failed. Review the build output for errors."
    cd ..
    exit 1
fi

echo "Script completed successfully"
cd ..
