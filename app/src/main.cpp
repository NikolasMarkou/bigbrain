#include <iostream>
#include <glog/logging.h>
#include <gflags/gflags.h>

DEFINE_bool(debug, true, "Show extra debug messages");

int main(int argc, char** argv)
{
    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    
    LOG(INFO) << "Working";
    return 0;
}