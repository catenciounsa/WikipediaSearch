add_executable(WikipediaSearch main.cpp)
  
add_subdirectory(search)
add_subdirectory(indexing)
add_subdirectory(words)


target_link_libraries(WikipediaSearch
  PRIVATE
    search
    indexing
  )