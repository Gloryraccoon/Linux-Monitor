#include "rpc_client.h"

namespace monitor{
RpcClient::RpcClient(const std::string& server_address){
    auto channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    stub_ptr_ = monitor::proto::GrpcManager::NewStub(channel);
}

RpcClient::~RpcClient(){}

void RpcClient::SetMonitorInfo(const monitor::proto::MonitorInfo& monitor_info){
    ::grpc::ClientContext context;
    ::google::protobuf::Empty response;
    ::grpc::Status status = 
        stub_ptr_->SetMonitorInfo(&context, monitor_info, &response);
    if(status.ok()){
    }else{
        std::cout << status.error_details() << std::endl;
        std::cout << "failed to connect !!!" << std::endl;
    }
}

void RpcClient::GetMonitorInfo(monitor::proto::MonitorInfo* monitor_info){
    ::grpc::ClientContext context;
    ::google::protobuf::Empty request;

    ::grpc::Status status = stub_ptr_->GetMonitorInfo(&context, request, monitor_info);

    if(status.ok()){}
    else{
        std::cout << status.error_details() << std::endl;
        std::cout << "failed to connect !!!" << std::endl;
    }
}
}