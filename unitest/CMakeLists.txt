find_package(GTest)

include_directories(${CMAKE_SOURCE_DIR}/src/)

if (${GTest_FOUND})
    file(GLOB GTEST_TEST *.cpp)
    add_executable(unit_gtest ${GTEST_TEST} vector3_test.cpp)
    target_link_libraries(unit_gtest jazz GTest::GTest GTest::Main)
    include(GoogleTest)
    gtest_discover_tests(unit_gtest)
endif ()