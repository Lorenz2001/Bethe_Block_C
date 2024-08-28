#!/bin/bash

#Project Directory configuration
PROJECT_DIT=$(pwd)

#Creation build directory 
mkdir -p build
cd build

#CMake esecution
cmake ..

#Project compilation
cmake --build .

#Project Esecution
./Bethe_Block