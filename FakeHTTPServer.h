#ifndef FKEHTTPSERVER_H
#define FKEHTTPSERVER_H

#include <QTcpServer>

class FakeHTTPServer : public QObject
{
    Q_OBJECT
private:
    QTcpServer server;
    int socketcounts;

public:
    explicit FakeHTTPServer(quint16 listeningPort, QObject *parent = 0);

signals:

public slots:
    // handle new qtcpsocket
    void haveNewClient();

    // destroy qtcpsocket
    void endConnection(QTcpSocket *zombie);
    void decrement();

    // make fake answer
    void readAndRespond();
};

#endif // FKEHTTPSERVER_H
