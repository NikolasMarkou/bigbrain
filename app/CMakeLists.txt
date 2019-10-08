# ./app/CMakeLists.txt

# Requires CMake 3.12
cmake_minimum_required( VERSION 3.12 )

project( bigbrainapp
         VERSION 0.0.1
         LANGUAGES C CXX
         DESCRIPTION "Deploying production ready ai models" )

# Setup executable and dependencies
add_executable( bigbrainapp )
target_sources( bigbrainapp 
    PRIVATE src/main.cpp )
target_link_libraries( bigbrainapp
    PRIVATE bigbrain::bigbrain glog::glog gflags::gflags)


