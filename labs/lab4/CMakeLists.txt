add_subdirectory(lib)

add_executable(array_test tests/array_test.cpp)
target_link_libraries(array_test PRIVATE arrayLib gtest gtest_main)

add_executable(compare_test tests/compare_test.cpp)
target_link_libraries(compare_test PRIVATE compareLib gtest gtest_main)

add_executable(figure_test tests/figure_test.cpp)
target_link_libraries(figure_test PRIVATE arrayLib figuresLib gtest gtest_main)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE arrayLib figuresLib)