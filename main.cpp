#include <QCoreApplication>
#include <FakeHTTPServer.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FakeHTTPServer myserver(8080);

    return a.exec();
}
