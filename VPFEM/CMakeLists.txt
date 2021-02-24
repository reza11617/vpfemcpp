cmake_minimum_required(VERSION 3.10)

INCLUDE_DIRECTORIES(./ ./vendor/spdlog/include ./vendor/eigen)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(./vendor/spdlog)

set(SOURCES src/Application.cpp
            src/FiniteElementModel.cpp
            src/Log.cpp
            src/Geometry/Node.cpp
            src/Geometry/Model.cpp
            src/Element/Element.cpp
            src/Element/ElasticBeamElement.cpp
            src/Element/ElasticBeamColumnElement.cpp
            src/Analyze/Analyze.cpp
            src/Analyze/Result.cpp
            src/Analyze/Solver.cpp
            src/Material/Material.cpp)

add_library(VPFEM STATIC ${SOURCES})

target_link_libraries(VPFEM spdlog)
