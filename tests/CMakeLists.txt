enable_testing()

add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest-1.16.0 ${CMAKE_BINARY_DIR}/external/googletest-build)

add_executable(tests 
            main.cpp
            test_circle.cpp
            test_ellipse.cpp
            test_helix.cpp
            )

target_link_libraries(tests PRIVATE gtest_main curves)

target_compile_features(tests PRIVATE cxx_std_20)

add_test(NAME all_tests COMMAND tests)