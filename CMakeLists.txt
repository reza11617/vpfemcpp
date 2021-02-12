cmake_minimum_required(VERSION 3.9.1)

project(VpfemTest)

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    message("Debug Build")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -ggdb3 -DDEBUG -std=c++17 -Wall")
elseif(${CMAKE_BUILD_TYPE} MATCHES Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++17 -O3")
    message("Release Build")
endif()


INCLUDE_DIRECTORIES( ./includes ./VPFEM ./VPFEM/vendor/spdlog/include ./VPFEM/vendor/eigen)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

message(${CMAKE_BINARY_DIR})

set(SOURCES Sandbox/src/SandboxApp.cpp)

add_subdirectory(VPFEM)

add_executable(vpfem_test ${SOURCES})

target_link_libraries(vpfem_test VPFEM)
