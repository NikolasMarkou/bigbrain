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
using bigbrain::AIResponse;
using bigbrain::AICapabilityRequest;

//----------------------------------------------------------------

AIServiceImpl::AIServiceImpl(
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

//----------------------------------------------------------------

AIServiceImpl* AIServiceImpl::create(
        const std::string db_path){
    std::string path = db_path.empty() ? "./bigbrain.leveldb" : db_path;
    leveldb::Options options;
    {
        options.create_if_missing = true;
        options.error_if_exists = false;
        options.paranoid_checks = true;
    }
    return new AIServiceImpl(path, options);
}

//----------------------------------------------------------------

void 
AIServiceImpl::report_keys(){
        LOG(INFO) << "Reporting db entries";
        leveldb::Iterator* it = m_db->NewIterator(leveldb::ReadOptions());
        for (it->SeekToFirst(); it->Valid(); it->Next()) {
            LOG(INFO) << it->key().ToString();
        }
        // Check for any errors found during the scan
        assert(it->status().ok());  
        delete it;
}

//----------------------------------------------------------------

Status 
AIServiceImpl::ReportCapabilities(
    ServerContext* context, 
    const AICapabilityRequest* request,
    AIResponse* response) 
{
    leveldb::Iterator* it = m_db->NewIterator(leveldb::ReadOptions());
    {
        response->set_success(true);

        for (it->SeekToFirst(); it->Valid(); it->Next()) 
        {
            LOG(INFO) << "Loading " << it->key().ToString();

            auto models_information = response->mutable_models_information();
            auto model_information = models_information->add_model_information();

            bigbrain::AICapability tmp_ai_capability;
            
            if (tmp_ai_capability.ParseFromString(it->value().ToString()) == false)
            {
                LOG(ERROR) << "Failed to parse [" << it->key().ToString() << "]";
                response->set_success(false);
                response->set_error(std::string("Failed to parse key"));
                return Status::CANCELLED;
            }
            
            // Check for any errors found during the scan
            if (it->status().ok() == false)
            {
                LOG(ERROR) << it->status().ToString();
                response->set_success(false);
                response->set_error(it->status().ToString());
                return Status::CANCELLED;
            }

            model_information->CopyFrom(tmp_ai_capability.information());
        }

        delete it;
    }

    return Status::OK;
}

//----------------------------------------------------------------