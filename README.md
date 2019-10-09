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

## Internal

### Generating gRPC code

```bash
protoc -I ../../protos/ --grpc_out=. --plugin=protoc-gen-grpc=grpc_cpp_plugin ../../protos/helloworld.proto
protoc -I ../../protos/ --cpp_out=. ../../protos/helloworld.proto
```
