cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17) # C++17...
set(CMAKE_CXX_COMPILER g++)

project(CommandGroupComposer CXX)

set(CGC_src
    src/main.cpp
)
set(CGCout_src
    src/OutputViewer.cpp
)

## Define the executable
add_executable(CGC-run ${CGC_src})
add_executable(Graphview ${CGCout_src})

install(TARGETS CGC-run
        DESTINATION bin)
# for windows
# cmake -G "MinGW Makefiles" ..