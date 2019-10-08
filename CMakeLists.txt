# ./CMakeLists.txt

# Requires CMake 3.12
cmake_minimum_required( VERSION 3.12 )

project( bigbrain
         VERSION 0.0.1
         DESCRIPTION "bigbrain project" )

 # Always use '-fPIC'/'-fPIE' option.
set( CMAKE_POSITION_INDEPENDENT_CODE ON )

# Make external libraries globally available.
add_subdirectory( external )

# Create targets for building the (local) libraries.
add_subdirectory( library )

# Create the targets for the entire example-app.
add_subdirectory( app )