add_executable(cpp_test test.cpp)

target_link_libraries(cpp_test search)

add_test(
  NAME
    test_search
  COMMAND
    $<TARGET_FILE:cpp_test>
  )