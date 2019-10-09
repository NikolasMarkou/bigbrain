#include <memory>
#include <string>
#include <iostream>
//#include <glog/logging.h>

#include <grpcpp/grpcpp.h>

#include "generated/bigbrain.grpc.pb.h"

using grpc::Status;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;

using bigbrain::AIService;
using bigbrain::AICapabilityRequest;
using bigbrain::AICapabilityResponse;

// Logic and data behind the server's behavior.
class AIServiceImpl final : public AIService::Service {
    Status ReportCapabilities(
        ServerContext* context, 
        const AICapabilityRequest* request,
        AICapabilityResponse* reply) override 
    {
        auto model_information = reply->add_models_information();
        {
            std::string name = "test_name";
            model_information->set_allocated_name(&name);

            std::string description = "test_description";
            model_information->set_allocated_description(&description);
        }

        return Status::OK;
    }
};

void run_server(
    const std::string url = "0.0.0.0:50051")
{
    std::string server_address(url);
    AIServiceImpl service;
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    //LOG(INFO) << "Server listening on " << server_address;
    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}
