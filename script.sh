#!/bin/bash

# Project Directory configuration
PROJECT_DIR=$(pwd)

# Creation of the build directory
mkdir -p build
cd build || exit 1

# CMake execution
cmake .. || { echo "CMake configuration failed"; exit 1; }

# Project compilation
cmake --build . || { echo "Compilation failed"; exit 1; }

# Project execution in background
./Bethe_Block &

# Optional: If you want to wait for the execution to finish
# wait $!

echo "Project is running in the background with PID $!"