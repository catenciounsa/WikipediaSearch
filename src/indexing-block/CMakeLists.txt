add_library(indexingblocks "")

target_sources(indexingblocks
  PRIVATE
    indexingblocks.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/indexingblocks.hpp
  )
target_include_directories(indexing
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

project( IndexBlock )
message( "Configuring subproject application:  ${PROJECT_NAME} " )

file(GLOB SOURCES "*.cpp" )
file(GLOB HEADERS "*.h" )

add_executable( ${PROJECT_NAME}
                                ${HEADERS}
                                ${SOURCES})
