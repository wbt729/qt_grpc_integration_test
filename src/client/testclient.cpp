#include "testclient.h"
#include "clientworker.h"

TestClient::TestClient(std::shared_ptr<grpc::ChannelInterface> channel, QObject *parent)
    : QObject{parent},
      stub(grpc::test::Greeter::NewStub(channel))
{
    qDebug() << Q_FUNC_INFO;
    worker = new ClientWorker(&cq);
    connect(worker, &ClientWorker::receivedReply, this, &TestClient::handleReply);
    connect(worker, &ClientWorker::receivedReply, this, &TestClient::cleanupCall);
    QThreadPool::globalInstance()->start(worker);
}

void TestClient::handleReply(AsyncClientCall *call)
{
    qDebug() << Q_FUNC_INFO << call;
    lastReply = QString::fromStdString(call->reply->DebugString());
    emit lastReplyChanged();

    switch(call->function)
    {
    case(RpcFunction::SayHello):
        qDebug() << "reply say hello";
        break;
    case(RpcFunction::SayGoodbye):
        qDebug() << "reply say goodbye";
        break;
    case(RpcFunction::Multiply):
        qDebug() << "reply say goodbye";
        break;
    default:
        qDebug() << "greeter unknown function";
    }
}

void TestClient::setLastReply(QString lastReply)
{
    this->lastReply = lastReply;
    emit lastReplyChanged();
}


// lifetime of call ends here
// this can not be managed through shared pointers, since we're
// passing around void pointers as per the API of gRpc
void TestClient::cleanupCall(AsyncClientCall *call)
{
    qDebug() << Q_FUNC_INFO;
    delete call;
}

void TestClient::sendHello(const QString name)
{
    qDebug() << Q_FUNC_INFO;
    grpc::test::HelloRequest request;
    request.set_name(name.toStdString());
    AsyncClientCall* call = new AsyncClientCall(RpcFunction::SayHello);
    call->reply = new grpc::test::HelloReply;

    std::unique_ptr<grpc::ClientAsyncResponseReader<grpc::test::HelloReply>> responseReader =
            stub->PrepareAsyncSayHello(&call->context, request, &cq);

    responseReader->StartCall();
    responseReader->Finish(dynamic_cast<grpc::test::HelloReply*>(call->reply), &call->status, (void*) call);
}

QString TestClient::getLastReply()
{
    qDebug() << Q_FUNC_INFO;
    return lastReply;
}

void TestClient::sendGoodbye(const QString name)
{
    qDebug() << Q_FUNC_INFO;
    grpc::test::GoodbyeRequest request;
    request.set_name(name.toStdString());
    AsyncClientCall* call = new AsyncClientCall(RpcFunction::SayGoodbye);
    call->reply = new grpc::test::GoodbyeReply;

    std::unique_ptr<grpc::ClientAsyncResponseReader<grpc::test::GoodbyeReply>> responseReader =
            stub->PrepareAsyncSayGoodbye(&call->context, request, &cq);

    responseReader->StartCall();
    responseReader->Finish(dynamic_cast<grpc::test::GoodbyeReply*>(call->reply), &call->status, (void*) call);
}

void TestClient::sendMultiply(int factorA, int factorB)
{
    qDebug() << Q_FUNC_INFO;
    grpc::test::MultiplicationRequest request;
    request.set_factora(factorA);
    request.set_factorb(factorB);
    AsyncClientCall* call = new AsyncClientCall(RpcFunction::Multiply);
    call->reply = new grpc::test::MultiplicationReply;

    std::unique_ptr<grpc::ClientAsyncResponseReader<grpc::test::MultiplicationReply>> responseReader =
            stub->PrepareAsyncMultiply(&call->context, request, &cq);

    responseReader->StartCall();
    responseReader->Finish(dynamic_cast<grpc::test::MultiplicationReply*>(call->reply), &call->status, (void*) call);
}
