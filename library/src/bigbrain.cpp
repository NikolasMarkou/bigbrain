#include <memory>
#include <string>
#include <iostream>
#include <stdexcept>
// key value store
#include <leveldb/db.h>
// logging
#include <glog/logging.h>
// rpc calls
#include <grpcpp/grpcpp.h>
// protoc auto generated code
#include "generated/bigbrain.pb.h"
#include "generated/bigbrain.grpc.pb.h"

#include "AIServiceImpl.hpp"

//----------------------------------------------------------------

using grpc::Status;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;

using bigbrain::AIService;
using bigbrain::AICapabilityRequest;
using bigbrain::AICapabilityResponse;

//----------------------------------------------------------------

void run_server(
    const std::string url)
{
    std::string server_address(url);
    std::shared_ptr<AIServiceImpl> service{AIServiceImpl::create()};
    ServerBuilder builder;
    {
        // Listen on the given address without any authentication mechanism.
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        // Register "service" as the instance through which we'll communicate with
        // clients. In this case it corresponds to an *synchronous* service.
        builder.RegisterService(service.get());
    }
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    LOG(INFO) << "Server listening on [" << server_address << "]";
    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

//----------------------------------------------------------------