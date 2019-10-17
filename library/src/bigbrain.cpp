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
using bigbrain::AICapabilityRequest;
using bigbrain::AICapabilityResponse;

//----------------------------------------------------------------

// Logic and data behind the server's behavior.
class AIServiceImpl final : public AIService::Service {
private:
    std::unique_ptr<leveldb::DB> m_db = nullptr;

    void report_keys(){
        LOG(INFO) << "Reporting db entries";
        leveldb::Iterator* it = m_db->NewIterator(leveldb::ReadOptions());
        for (it->SeekToFirst(); it->Valid(); it->Next()) {
            LOG(INFO) << it->key().ToString();
        }
        // Check for any errors found during the scan
        assert(it->status().ok());  
        delete it;
    }
public:
    
    AIServiceImpl(
        const std::string db_path, 
        leveldb::Options db_options) : 
            AIService::Service()
    {
        leveldb::DB* db;
        leveldb::Status status = leveldb::DB::Open(db_options, db_path, &db);

        if (status.ok() == false){
            LOG(ERROR) << "Failed to open datatabse [" << db_path << "]";
            std::runtime_error(status.ToString());
        }

        m_db.reset(db);

        this->report_keys();
    }

    static AIServiceImpl* create(
            const std::string db_path = std::string()){
        std::string path = db_path.empty() ? "./bigbrain.leveldb" : db_path;
        leveldb::Options options;
        {
            options.create_if_missing = true;
            options.error_if_exists = false;
            options.paranoid_checks = true;
        }
        return new AIServiceImpl(path, options);
    }
private:
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

        leveldb::Iterator* it = m_db->NewIterator(leveldb::ReadOptions());
        {
            for (it->SeekToFirst(); it->Valid(); it->Next()) {
                LOG(INFO) << "Loading " << it->key().ToString();

                auto model_information = reply->add_models_information();

                bigbrain::AICapability tmp_ai_capability;
                
                if (tmp_ai_capability.ParseFromString(it->value().ToString()) == false){
                    LOG(ERROR) << "Failed to parse [" << it->key().ToString() << "]";
                    continue;
                }
                
                // Check for any errors found during the scan
                if (it->status().ok() == false){
                    LOG(ERROR) << it->status().ToString();
                    continue;
                }

                model_information->CopyFrom(tmp_ai_capability.information());
            }

            delete it;
        }

        return Status::OK;
    }
};

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