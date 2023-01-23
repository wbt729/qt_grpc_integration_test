#pragma once
#include <QObject>
#include <QVariant>
#include <QRunnable>

#include <grpcpp/grpcpp.h>
#include <google/protobuf/message.h>

enum class RpcFunction
{
    SayHello,
    SayGoodbye,
    Multiply
};

class AsyncClientCall
{
public:
    AsyncClientCall(RpcFunction);
    ~AsyncClientCall();
    google::protobuf::Message* reply;
    grpc::ClientContext context;
    grpc::Status status;
    RpcFunction function;
};

class ClientWorker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit ClientWorker(grpc::CompletionQueue* cq);

    void run() override;

signals:
    void receivedReply(AsyncClientCall* call);

private:
    grpc::CompletionQueue* cq;
};
