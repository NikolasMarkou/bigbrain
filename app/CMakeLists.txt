# ./app/CMakeLists.txt

# Requires CMake 3.12
cmake_minimum_required( VERSION 3.12 )

project( bigbrainapp
         VERSION 0.0.1
         DESCRIPTION "Deploying production ready ai models" )

# Freely available calculator app.
add_executable( bigbrainapp )
target_sources( bigbrainapp PRIVATE "src/main.cpp" )
target_link_libraries( bigbrainapp
    PRIVATE bigbrain::bigbrain )


