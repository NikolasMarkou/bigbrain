# ./library/CMakeLists.txt

# Requires CMake 3.12
cmake_minimum_required( VERSION 3.12 )

project( BigBrainLibs
         VERSION 1.0.0
         DESCRIPTION "The internal bigbrain libraries." )

# An OBJECT-library
add_library( bigbrain_objlib OBJECT )

file(GLOB SRC_FILES src/generated/*.cc)

target_sources( bigbrain_objlib
    PRIVATE   src/bigbrain.cpp ${SRC_FILES}
    PUBLIC    ${CMAKE_CURRENT_SOURCE_DIR}/include/bigbrain.h
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/bigbrainAPI.h )

# Required include search-paths and constexpr support.
target_include_directories( bigbrain_objlib
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/grpc/include )

target_compile_features( bigbrain_objlib
    PUBLIC cxx_constexpr )

# A shared library for basic-math functionality.
add_library( bigbrainlib SHARED )
target_link_libraries( 
    bigbrainlib 
    PUBLIC 
    bigbrain_objlib 
    grpc++
    glog::glog
    protobuf::libprotobuf)

# Add dependncies to th grpc target
add_dependencies(
    bigbrainlib
    grpc++
    grpc_cpp_plugin)

# Create ALIAS targets.
add_library( bigbrain::bigbrain ALIAS bigbrainlib )