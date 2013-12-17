#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDebug>
#include <QObject>
#include <QDateTime>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QNetworkSession>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QStringList>
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>

class TcpServer : QObject
{
    Q_OBJECT
public:
    TcpServer();
    virtual ~TcpServer();
private:
    QTcpServer* tcpServer;
    QNetworkSession* networkSession;
private:
    void startConnection(void);
    void sendData(QByteArray reply);
private slots:
    void sessionOpened(void);
    void newClient(void);
    void readData(void);
};

#endif // TCPSERVER_H
