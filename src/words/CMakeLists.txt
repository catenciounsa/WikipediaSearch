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