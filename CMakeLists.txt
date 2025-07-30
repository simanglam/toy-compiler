cmake_minimum_required(VERSION 4.0.0)

project(toycompiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES arm64)
set(COMPILE_FLAGS debug)

find_package(LLVM REQUIRED CONFIG)

option(LLVM_LIB_PATH "LLVM_LIB_PATH" OFF)
option(LLVM_LIB "LLVM_LIB" OFF)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

message(STATUS "LLVM LIB ${LLVM_LIB}")
message(STATUS "LLVM LIB PATH ${LLVM_LIB_PATH}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

include_directories(include)

find_library(name llvm)

llvm_map_components_to_libnames(llvm_libs support core irreader)

add_subdirectory(compiler)

add_executable(CommandLineMain CommandLineMain.cpp)
target_link_libraries(CommandLineMain compiler)