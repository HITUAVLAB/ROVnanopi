cmake_minimum_required(VERSION 2.8)

set(ROVnanopi_VERSION_MAJOR 1)
set(ROVnanopi_VERSION_MINOR 0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(ROVnanopi CXX)

#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "Debug")

IF (CMAKE_BUILD_TYPE STREQUAL Debug)
    ADD_DEFINITIONS(-DDEBUG)
ENDIF()

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
find_package (Threads)

INCLUDE_DIRECTORIES(
    inc
    inc/main
    inc/thread
    inc/repeater
    inc/videostream
    inc/comm
    inc/projectdebug

    #mavlink include directory
    inc/mavlink/ROV

    usr/local/include
    usr/include)

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

add_subdirectory(src)
add_subdirectory(inc)

link_libraries (thread comm videostream repeater init)
add_executable(${PROJECT_NAME} ${DIR_SRCS} )

target_link_libraries (ROVnanopi ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (ROVnanopi thread comm videostream repeater init)
