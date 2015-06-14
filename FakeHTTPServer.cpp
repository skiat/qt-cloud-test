#include "FakeHTTPServer.h"
#include <QTcpSocket>
#include <QTcpServer>

FakeHTTPServer::FakeHTTPServer(quint16 listeningPort, QObject *parent) :
    QObject(parent), socketcounts(0)
{
    if (server.listen(QHostAddress::Any, listeningPort)) {
        qDebug("Fake HTTP server is listening on port %d", listeningPort);

        connect(&server, SIGNAL(newConnection()), this, SLOT(haveNewClient()));
    }else{
        qDebug("Unbale to listen on port %d", listeningPort);
    }
}

void FakeHTTPServer::haveNewClient()
{

    if (server.hasPendingConnections()) {
        QTcpSocket *tmpSock = server.nextPendingConnection();
        socketcounts++;

        qDebug("%d New Fake HTTP connection c(%s:%d) -> s(%s:%d)",
               socketcounts,
               tmpSock->peerAddress().toString().toLatin1().constData(),
               tmpSock->peerPort(),
               tmpSock->localAddress().toString().toLatin1().constData(),
               tmpSock->localPort()
               );

        connect(tmpSock, SIGNAL(readyRead()), this, SLOT(readAndRespond()));
        // self destroing
        connect(tmpSock, SIGNAL(disconnected()), tmpSock, SLOT(deleteLater()));

        connect(tmpSock, SIGNAL(disconnected()), this, SLOT(decrement()));

    }else{
        qDebug("what is this ? ");
    }
}

void FakeHTTPServer::endConnection(QTcpSocket *zombie)
{
    zombie->disconnectFromHost();


    qDebug("serverChilds %d", server.children().size());
}

void FakeHTTPServer::decrement()
{
    socketcounts--;
}


void FakeHTTPServer::readAndRespond()
{
    QTcpSocket *tmpSock = qobject_cast<QTcpSocket*>(sender());
    QByteArray allRequest = tmpSock->readAll();

    // make HTTP Header
    QByteArray response = "HTTP/1.0 200 OK\r\n"
            "Content-Type: text/plain; charset=UTF-8\r\n"
            "Content-Length: " + QByteArray::number(allRequest.size()) + "\r\n"
            "\r\n";

    response.append(allRequest);

    // respond with "echo"
    tmpSock->write(response);

    // kill conn
    endConnection(tmpSock);
}
