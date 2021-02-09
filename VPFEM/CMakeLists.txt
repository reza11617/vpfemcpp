cmake_minimum_required(VERSION 3.10)

INCLUDE_DIRECTORIES(./ ./vendor/spdlog/include)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(./vendor/spdlog)

set(SOURCES src/Application.cpp
            src/Log.cpp
            src/Geometry/Node.cpp)

add_library(VPFEM STATIC ${SOURCES})

target_link_libraries(VPFEM spdlog)
