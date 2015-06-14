#ifndef FKEHTTPSERVER_H
#define FKEHTTPSERVER_H

#include <QTcpServer>

class FakeHTTPServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit FakeHTTPServer(QObject *parent = 0);

signals:

public slots:

};

#endif // FKEHTTPSERVER_H
