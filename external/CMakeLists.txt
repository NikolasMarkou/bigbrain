# ./external/CMakeLists.txt
##################################################################
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
##################################################################
## glog
add_subdirectory( glog )
message(STATUS "Using glog via add_subdirectory.")
##################################################################
##  grpc
add_subdirectory( grpc EXCLUDE_FROM_ALL)
message(STATUS "Using grpc via add_subdirectory.")
set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
set(_GRPC_GRPCPP_UNSECURE grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
##################################################################



