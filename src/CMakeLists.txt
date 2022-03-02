include_directories(${CMAKE_SOURCE_DIR}/src)
file(GLOB_RECURSE JAZZ_CORE ${CMAKE_SOURCE_DIR}/src/jazz/core/*.cpp)
add_library(jazz ${JAZZ_CORE} jazz/core/ValArray.cpp jazz/core/ValArray.h jazz/core/Vector3.h)