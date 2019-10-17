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

//----------------------------------------------------------------

using grpc::Status;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;

using bigbrain::AIService;
using bigbrain::AIResponse;
using bigbrain::AICapabilityRequest;

//----------------------------------------------------------------

// Logic and data behind the server's behavior.
class AIServiceImpl final : public AIService::Service {
    public:
        AIServiceImpl(
            const std::string db_path, 
            leveldb::Options db_options);

        static AIServiceImpl* create(
                const std::string db_path = std::string());
    private:
        Status ReportCapabilities(
            ServerContext* context, 
            const AICapabilityRequest* request,
            AIResponse* response) override;

        std::unique_ptr<leveldb::DB> m_db = nullptr;

        void report_keys();
};

//----------------------------------------------------------------