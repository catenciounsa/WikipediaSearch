add_library(search "")

target_sources(search
  PRIVATE
  search.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/search.hpp
  )
target_include_directories(search
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )