#include "clientworker.h"
#include <QDebug>

ClientWorker::ClientWorker(grpc::CompletionQueue* cq) :
    cq(cq)
{
}

void ClientWorker::run()
{
    qDebug() << Q_FUNC_INFO;

    void* got_tag;
    bool ok = false;

    while (cq->Next(&got_tag, &ok))
    {
        // The tag in this example is the memory location of the call object
        auto call = static_cast<AsyncClientCall*>(got_tag);

        // Verify that the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        if (call->status.ok())
            std::cout << "Received: " << call->reply->DebugString() << std::endl;
        else
            std::cout << "RPC failed" << std::endl;

        emit receivedReply(call);
    }
}

AsyncClientCall::AsyncClientCall(RpcFunction function) :
    function(function)
{

}

AsyncClientCall::~AsyncClientCall()
{
    qDebug() << Q_FUNC_INFO;
    delete reply;
}
