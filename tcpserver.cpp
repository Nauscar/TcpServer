#include "tcpserver.h"

TcpServer::TcpServer()
{
    QNetworkConfigurationManager manager;
    networkSession = new QNetworkSession(manager.defaultConfiguration(), this);
    connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));
    networkSession->open();

    tcpServer = new QTcpServer(this);
    startConnection();
}

TcpServer::~TcpServer()
{
    delete tcpServer;
}

void TcpServer::startConnection()
{
    if (!tcpServer->listen(QHostAddress::Any, 27015)) {
        qCritical() << "Unable to start the server: " << tcpServer->errorString();
        tcpServer->close();
        return;
    }

    QTextStream qOut(stdout);
    qOut << "The server is running on IP(s): ";

    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int c = 0; c < ipAddressesList.length(); c++) {
        if(ipAddressesList.at(c).toIPv4Address()){
            qOut << ipAddressesList.at(c).toString() << " ";
        }
    }

    qOut << "Port: " << tcpServer->serverPort() << endl;
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newClient()));
}

void TcpServer::sendData(QByteArray reply)
{
    /*QTextStream qOut(stdout);
    QDateTime dateTime = QDateTime(QDate::currentDate(), QTime::currentTime());
    qOut << "(" << dateTime.date().toString() << " " << dateTime.time().toString() << "): request received" << endl;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << fortunes.at(qrand() % fortunes.size());
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    QTcpSocket* clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));
    qDebug() << clientConnection->write(block);
    clientConnection->disconnectFromHost();*/
}

void TcpServer::newClient()
{
    QTcpSocket* tcpClient = tcpServer->nextPendingConnection();
    qDebug() << "Client connected: " << tcpClient->localAddress().toString();
    connect(tcpClient, SIGNAL(disconnected()), tcpClient, SLOT(deleteLater()));
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(readData()));
}

void TcpServer::readData()
{
    QTcpSocket* myClient = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = myClient->readAll();
    qDebug() << QString(data);
}

void TcpServer::sessionOpened()
{
    //TODO: Add configuration settings here.
}
