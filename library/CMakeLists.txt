# ./library/CMakeLists.txt

# Requires CMake 3.12
cmake_minimum_required( VERSION 3.12 )

project( BigBrainLibs
         VERSION 0.0.1
         LANGUAGES C CXX
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
    ${CMAKE_SOURCE_DIR}/external/grpc/include
    ${CMAKE_SOURCE_DIR}/external/glog )

target_compile_features( bigbrain_objlib
    PUBLIC cxx_constexpr )

add_library( bigbrainlib SHARED )
target_link_libraries( bigbrainlib 
    PRIVATE
        glog::glog
        bigbrain_objlib 
        protobuf::libprotobuf)

# Add dependncies to th grpc target
add_dependencies(
    bigbrainlib
    grpc++
    grpc_cpp_plugin)

# Create ALIAS targets.
add_library( bigbrain::bigbrain ALIAS bigbrainlib )