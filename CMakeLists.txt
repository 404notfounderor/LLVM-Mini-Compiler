cmake_minimum_required(VERSION 3.10)

project(LLVMCompiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

file(GLOB SRC_FILES
    src/*.cpp
)

add_executable(compiler ${SRC_FILES})

llvm_map_components_to_libnames(llvm_libs
    core
    executionengine
    orcjit
    native
    support
)

target_link_libraries(compiler ${llvm_libs})