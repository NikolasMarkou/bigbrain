# ./external/CMakeLists.txt
##################################################################
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
##################################################################
## gflags
add_subdirectory( gflags )
message(STATUS "Using gflags via add_subdirectory.")
##################################################################
## glog
add_subdirectory( glog )
message(STATUS "Using glog via add_subdirectory.")
##################################################################
## protobuf
add_subdirectory( protobuf/cmake )
message(STATUS "Using protobuf via add_subdirectory.")
##################################################################



