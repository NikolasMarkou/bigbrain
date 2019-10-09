set(gflags_FOUND)
set(gflags_DIR ${CMAKE_BINARY_DIR}/external/gflags/ CACHE PATH "Directory containing gflags installation" FORCE)
set(gflags_LIBRARY_DIR ${gflags_DIR}/)
set(gflags_INCLUDE_DIR ${gflags_DIR}/include)
set(gflags_LIBRARY ${gflags_DIR}/libgflags_nothreads_static.a)

message(STATUS "gflags_INCLUDE_DIR: ${gflags_INCLUDE_DIR}" )
message(STATUS "gflags_LIBRARY_DIR: ${gflags_LIBRARY_DIR}" )
message(STATUS "gflags_LIBRARY:     ${gflags_LIBRARY}" )