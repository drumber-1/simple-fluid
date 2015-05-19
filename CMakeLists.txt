cmake_minimum_required(VERSION 3.2)
project(simple_fluid)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(simple_fluid ${SOURCE_FILES} src/util/ArrayN.hpp src/Grid.hpp src/operators/diffusion.hpp src/util/Array2.hpp src/operators/common.hpp src/operators/advection.hpp src/operators/projection.hpp src/FluidVariable.hpp src/boundary.hpp)