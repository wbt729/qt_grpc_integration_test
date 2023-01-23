#pragma once

#include <QObject>
#include <QDebug>
#include <QThreadPool>

#include <grpcpp/grpcpp.h>
#include "test.grpc.pb.h"
#include "clientworker.h"

class TestClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lastReply  READ getLastReply NOTIFY lastReplyChanged)
public:
    explicit TestClient(std::shared_ptr<grpc::ChannelInterface> channel, QObject *parent = nullptr);

    Q_INVOKABLE void sendHello(const QString name);
    Q_INVOKABLE QString getLastReply();
    Q_INVOKABLE void sendGoodbye(const QString name);
    Q_INVOKABLE void sendMultiply(int factorA, int factorB);

signals:
    void lastReplyChanged();

private slots:
    void handleReply(AsyncClientCall* call);
    void cleanupCall(AsyncClientCall* call);

private:
    void setLastReply(QString lastReply);
    std::shared_ptr<grpc::test::Greeter::Stub> stub;
    grpc::CompletionQueue cq;
    ClientWorker* worker;
    QString lastReply{"n.A."};
};
