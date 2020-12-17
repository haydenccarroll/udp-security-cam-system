cmake_minimum_required(VERSION 2.9 FATAL_ERROR)
SET(projectName networkingProject)

project(projectName)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_STANDARD_REQUIRED true)
set(EXECUTABLE_NAME projectName)

find_package(OpenCV REQUIRED)
find_package( Boost 1.40 COMPONENTS program_options REQUIRED )
file(GLOB SOURCES src/*.cpp) #stores all .cpp files in SOURCES
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable (${EXECUTABLE_NAME} ${SOURCES})

TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${OpenCV_LIBS} ${Boost_LIBRARIES})

