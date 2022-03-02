find_package(GTest)

include_directories(${CMAKE_SOURCE_DIR}/src/)

if (${GTest_FOUND})
    file(GLOB GTEST_TEST *.cpp)
    add_executable(unit_gtest ${GTEST_TEST})
    target_link_libraries(unit_gtest GTest::gtest GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(unit_gtest)
endif ()