# bigbrain

A extendible and robust way of deploying production level deep learning models

## Dependencies

* gflags for passing arguments
* glog for logging
* protobuf for messaging and serialization
* gRPC for providing RPC functionality

To load all dependencies

```bash
git submodule update --init --recursive
```

## Notes

### Generating gRPC code

To always build ```grpc_ccp_plugin```. I've added the ```grpc_ccp_plugin``` as a dependency for the ```libbigbrain```.

The gRPC plugin ```grpc_ccp_plugin``` will be created in the directory ```${BUILD_DIR}/grpc``` 

To use it from the project'ss ```${ROOT_DIR}``` : 

```bash
protoc \
    -I=./library/protos/ \
    --grpc_out=./library/src/generated \
    --plugin=protoc-gen-grpc=./build/external/grpc/grpc_cpp_plugin \
    ./library/protos/bigbrain.proto

protoc \
    -I=./library/protos/ \
    --cpp_out=./library/src/generated \
    ./library/protos/bigbrain.proto
```
