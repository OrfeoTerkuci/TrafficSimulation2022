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
        tinyxml/tinystr.cpp
        tinyxml/tinyxmlerror.cpp
        tinyxml/tinystr.h
        tinyxml/tinyxml.h
        tinyxml/tinyxml.cpp
        tinyxml/tinyxmlparser.cpp
        )

# Set Help Libraries
set(AdditionalSources
        Standard_Values.h
        DesignByContract.h
        )

# Set Parsers
set(parsers
        ParserJSON.cpp
        ParserXML.cpp)

# Set Sources
set(sources
        TrafficSimulation.cpp
        TrafficLight.cpp
        Vehicle.cpp
        Road.cpp
        VehicleGenerator.cpp
        )


# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES TrafficSimulationMain.cpp ${sources} ${AdditionalSources} ${tinySources} ${parsers})

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES TrafficSimulationTests.cpp ${sources} ${AdditionalSources} ${tinySources} ${parsers})

# Create RELEASE target
add_executable(ts ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(ts_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(ts_debug gtest)
