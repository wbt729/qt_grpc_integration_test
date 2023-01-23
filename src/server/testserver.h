#pragma once

#include "test.grpc.pb.h"

class TestServer : public grpc::test::Greeter::Service
{
public:
    TestServer();

    grpc::Status SayHello(grpc::ServerContext* context, const grpc::test::HelloRequest* request,
                          grpc::test::HelloReply* reply) override;
    grpc::Status SayGoodbye(grpc::ServerContext* context, const grpc::test::GoodbyeRequest* request,
                          grpc::test::GoodbyeReply* reply) override;
    grpc::Status Multiply(grpc::ServerContext* context, const grpc::test::MultiplicationRequest* request,
                          grpc::test::MultiplicationReply* reply) override;
};

