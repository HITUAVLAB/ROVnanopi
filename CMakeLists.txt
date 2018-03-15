cmake_minimum_required(VERSION 2.8)

set(ROVnanopi_VERSION_MAJOR 1)
set(ROVnanopi_VERSION_MINOR 0)

#SET(CMAKE_CXX_COMPILER "/usr/bin/g++-5")

project(ROVnanopi CXX)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
find_package (Threads)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")

INCLUDE_DIRECTORIES(inc)
#INCLUDE_DIRECTORIES(usr/local/include)
INCLUDE_DIRECTORIES(usr/include)
AUX_SOURCE_DIRECTORY(src DIR_SRCS)

add_executable(${PROJECT_NAME} ${DIR_SRCS} )

target_link_libraries (ROVnanopi ${CMAKE_THREAD_LIBS_INIT})

