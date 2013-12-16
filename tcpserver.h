#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDebug>
#include <QObject>
#include <QDateTime>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
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
    QStringList fortunes;
private:
    void setFortunes(void); //to be deleted.
    void startConnection(void);
private slots:
    void sendFortune(void);
};

#endif // TCPSERVER_H
