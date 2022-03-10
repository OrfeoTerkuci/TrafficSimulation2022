cmake_minimum_required(VERSION 3.6)
project(TrafficSimulation2022)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set tinyxml sources
set(tinySources
        tinystr.cpp
        tinyxmlerror.cpp
        tinystr.h
        tinyxml.h
        tinyxml.cpp
        tinyxmlparser.cpp
        )

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES TrafficSimulationMain.cpp TrafficSimulationReader.cpp TrafficLight.cpp Vehicle.cpp ${tinysources})

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES TrafficSimulationMain.cpp TrafficSimulationReader.cpp TrafficLight.cpp Vehicle.cpp ${tinysources})

# Create RELEASE target
add_executable(ts ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(ts_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(ts_debug gtest)
