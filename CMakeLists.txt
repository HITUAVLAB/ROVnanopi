cmake_minimum_required(VERSION 3.5.1)

project(ROVNANOPI)

aux_source_directory(. DIRSRCS)

include_directories(./ ./inc )

add_subdirectory(./src)

add_executable(ROVnanopi ${DIRSRCS})

target_link_libraries(ROVnanopi src)
