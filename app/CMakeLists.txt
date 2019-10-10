# ./app/CMakeLists.txt

# Requires CMake 3.12
cmake_minimum_required( VERSION 3.12 )

project( bigbrain_use
         VERSION 0.0.1
         LANGUAGES C CXX
         DESCRIPTION "Deploying production ready AI models" )

# Setup executable and dependencies
add_executable( bigbrain_client )

# Add sources
target_sources( bigbrain_client 
    PRIVATE src/main.cpp )

# Add library dependencies
target_link_libraries( bigbrain_client
    PRIVATE  
        glog::glog 
        gflags::gflags
        bigbrain::bigbrain)


