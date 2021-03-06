cmake_minimum_required(VERSION 2.8)
project(simple_fluid)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# sfml
find_package(SFML COMPONENTS system window graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIR} ${PROJECT_SOURCE_DIR})

# resources
configure_file(res/colourmap.png ${CMAKE_CURRENT_BINARY_DIR}/res/colourmap.png COPYONLY)

set(SOURCE_FILES src/main.cpp)
add_executable(simple_fluid ${SOURCE_FILES} src/fluid/Grid.hpp src/fluid/operators/diffusion.hpp src/util/Array2.hpp src/fluid/common.hpp src/fluid/operators/advection.hpp src/fluid/operators/projection.hpp src/fluid/FluidVariable.hpp src/fluid/boundary.hpp src/fluid/operators/misc.hpp src/graphics/GridRenderer.hpp src/input/InputHandler.hpp src/SimpleFluid.hpp src/parameters.hpp src/input/InputState.hpp src/input/FluidInteractor.hpp src/util/wrap.hpp src/util/util.hpp)

target_link_libraries(simple_fluid ${SFML_LIBRARIES})