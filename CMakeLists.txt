cmake_minimum_required(VERSION 4.0.0)

project(toycompiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES arm64)

find_package(LLVM REQUIRED CONFIG)

option(MyOption "MyOption" OFF)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

message(STATUS "Using LLVMConfig.cmake in: ${MyOption}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

include_directories(include)

find_library(name llvm)

llvm_map_components_to_libnames(llvm_libs support core irreader)

add_subdirectory(compiler)

add_executable(CommandLineMain CommandLineMain.cpp)
target_link_libraries(CommandLineMain compiler)