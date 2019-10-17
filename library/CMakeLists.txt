# ./library/CMakeLists.txt

# Requires CMake 3.12
cmake_minimum_required( VERSION 3.12 )

project( libbigbrain
         VERSION 0.1.0
         LANGUAGES CXX
         DESCRIPTION "The internal bigbrain libraries." )

# An OBJECT-library
add_library( bigbrain SHARED )

file(GLOB SRC_FILES src/generated/*.cc)

target_sources( bigbrain
    PRIVATE   
        src/bigbrain.cpp 
        src/AIServiceImpl.cpp
        ${SRC_FILES}
    PUBLIC    
        ${CMAKE_CURRENT_SOURCE_DIR}/include/bigbrain.h
    INTERFACE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/bigbrainAPI.h )

target_include_directories(bigbrain
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add library dependencies
target_link_libraries( bigbrain
    PRIVATE  
        glog::glog 
        grpc++
        leveldb
        libprotobuf)

target_compile_features(
    bigbrain 
    PRIVATE cxx_std_11
    PUBLIC cxx_constexpr)

target_compile_options(
    bigbrain PRIVATE -Werror)

# Add dependncies to th grpc target
add_dependencies(bigbrain
    protoc
    grpc_cpp_plugin)

# Create ALIAS targets.
add_library( bigbrain::bigbrain ALIAS bigbrain )