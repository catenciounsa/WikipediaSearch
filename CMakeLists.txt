cmake_minimum_required(VERSION 3.0.0)
project(WikipediaSearch)

include(CTest)
enable_testing()

find_package(Threads)

#file(GLOB SOURCES "*.cpp" )
#file(GLOB HEADERS "*.h" )


#add_executable( ${PROJECT_NAME}
#${HEADERS}
#${SOURCES})

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#include(CPack)

add_subdirectory(src)
add_subdirectory(test)