# ./library/CMakeLists.txt

# Requires CMake 3.12
cmake_minimum_required( VERSION 3.12 )

project( bigbrainlib
         VERSION 0.0.1
         LANGUAGES CXX
         DESCRIPTION "The internal bigbrain libraries." )

# An OBJECT-library
add_library( bigbrainlib SHARED )

file(GLOB SRC_FILES src/generated/*.cc)

target_sources( bigbrainlib
    PRIVATE   
        src/bigbrain.cpp ${SRC_FILES}
    PUBLIC    
        ${CMAKE_CURRENT_SOURCE_DIR}/include/bigbrain.h
    INTERFACE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/bigbrainAPI.h )

target_include_directories(bigbrainlib
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add library dependencies
target_link_libraries( bigbrainlib
    PRIVATE  
        glog::glog 
        grpc++
        leveldb
        libprotobuf)

target_compile_features(
    bigbrainlib 
    PRIVATE cxx_std_11
    PUBLIC cxx_constexpr)

target_compile_options(
    bigbrainlib PRIVATE -Werror)

# Add dependncies to th grpc target
add_dependencies(bigbrainlib
    protoc
    grpc_cpp_plugin)

# Create ALIAS targets.
add_library( bigbrain::bigbrain ALIAS bigbrainlib )