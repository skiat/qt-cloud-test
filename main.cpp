#include <QCoreApplication>
#include <FakeHTTPServer.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    quint16 port = 8080;
    if (qEnvironmentVariableIsSet("PORT") && !qEnvironmentVariableIsEmpty("PORT")) {
        port = qgetenv("PORT").toUInt();
    }

    if (qEnvironmentVariableIsSet("MAR_APP_ID") && !qEnvironmentVariableIsEmpty("MAR_APP_ID")) {
        qDebug() << "Running on cloud MAR_APP_ID" << qgetenv("MAR_APP_ID");
    }


    FakeHTTPServer myserver(port);

    return a.exec();
}
