add_library(indexing "")

target_sources(indexing
  PRIVATE
    indexing.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/indexing.hpp
  )
target_include_directories(indexing
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )