# bigbrain

A extendible and robust way of deploying production level deep learning models.

I have two basic target frameworks that i want to support in mind

* tensorflow 
* pytorch

## Dependencies

I tried to use ```CMake``` best practises however if you have any trouble building, please open an issue

All dependencies are included as ```submodules```

To load all dependencies

```bash
git submodule update --init --recursive
```

* gflags for passing arguments
* glog for logging
* protobuf for messaging and serialization
* gRPC for providing RPC functionality

To build (in the project root)

```bash
mkdir build
cd build
cmake ../
make bigbrain_client
```

## Notes

### Generating gRPC code

To always build ```grpc_ccp_plugin```. I've added the ```grpc_ccp_plugin``` as a dependency for the ```libbigbrain```.

The gRPC plugin ```grpc_ccp_plugin``` will be created in the directory ```${BUILD_DIR}/grpc``` 

To use it from the project's ```${ROOT_DIR}``` : 

```bash
./build/external/grpc/third_party/protobuf/protoc \
    -I=./library/protos/ \
    --grpc_out=./library/src/generated \
    --plugin=protoc-gen-grpc=./build/external/grpc/grpc_cpp_plugin \
    ./library/protos/bigbrain.proto

./build/external/grpc/third_party/protobuf/protoc \
    -I=./library/protos/ \
    --cpp_out=./library/src/generated \
    ./library/protos/bigbrain.proto
```
