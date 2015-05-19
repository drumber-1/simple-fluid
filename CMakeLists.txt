cmake_minimum_required(VERSION 3.2)
project(simple_fluid)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(simple_fluid ${SOURCE_FILES} src/fluid/Grid.hpp src/fluid/operators/diffusion.hpp src/fluid/util/Array2.hpp src/fluid/operators/common.hpp src/fluid/operators/advection.hpp src/fluid/operators/projection.hpp src/fluid/FluidVariable.hpp src/fluid/boundary.hpp)