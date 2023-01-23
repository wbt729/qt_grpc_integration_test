#include "testserver.h"
#include <chrono>
#include <thread>

TestServer::TestServer()
{

}

grpc::Status TestServer::SayHello(grpc::ServerContext* context, const grpc::test::HelloRequest *request, grpc::test::HelloReply *reply)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Sleeping for 2 sec" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::string message("Hello ");
    reply->set_message(message + request->name());
    return grpc::Status::OK;
}

grpc::Status TestServer::SayGoodbye(grpc::ServerContext *context, const grpc::test::GoodbyeRequest *request, grpc::test::GoodbyeReply *reply)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Sleeping for 5 sec" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::string message("Goodbye ");
    reply->set_message(message + request->name());
    return grpc::Status::OK;
}

grpc::Status TestServer::Multiply(grpc::ServerContext *context, const grpc::test::MultiplicationRequest *request, grpc::test::MultiplicationReply *reply)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Sleeping for 10 sec, multiplication is hard" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));

    reply->set_result(request->factora() * request->factorb());
    return grpc::Status::OK;
}
