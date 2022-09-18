cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17) # C++17...
set(CMAKE_CXX_COMPILER g++)

project(CommandGroupComposer CXX)

set(CGC_src
    src/main.cpp
)

## Define the executable
add_executable(CGC-run ${CGC_src})

install(TARGETS CGC-run
        DESTINATION bin)
# for windows
# cmake -G "MinGW Makefiles" ..