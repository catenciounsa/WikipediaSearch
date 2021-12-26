add_library(words "")

target_sources(words
  PRIVATE
  words.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/words.hpp
  )
target_include_directories(words
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

project( Words )
message( "Configuring subproject application:  ${PROJECT_NAME} " )

file(GLOB SOURCES "*.cpp" )
file(GLOB HEADERS "*.h" )

add_executable( ${PROJECT_NAME}
                                ${HEADERS}
                                ${SOURCES})

