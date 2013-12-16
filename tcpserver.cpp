#include "tcpserver.h"

TcpServer::TcpServer()
{
    tcpServer = new QTcpServer(this);
    setFortunes(); //to be deleted
    startConnection();
}

TcpServer::~TcpServer()
{
    delete tcpServer;
}

void TcpServer::setFortunes()
{
    fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
             << tr("You've got to think about tomorrow.")
             << tr("You will be surprised by a loud noise.")
             << tr("You will feel hungry again in another hour.")
             << tr("You might have mail.")
             << tr("You cannot kill time without injuring eternity.")
             << tr("Computers are not intelligent. They only think they are.");
}

void TcpServer::startConnection()
{
    if (!tcpServer->listen(QHostAddress::Any, 27015)) {
        qCritical() << "Unable to start the server: " << tcpServer->errorString();
        //close();
        return;
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int c = 0; c < ipAddressesList.length(); c++) {
        if (ipAddressesList.at(c) != QHostAddress::LocalHost &&
                ipAddressesList.at(c).toIPv4Address()) {
            ipAddress = ipAddressesList.at(c).toString();
            break;
        }
    }

    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    QTextStream qOut(stdout);
    qOut << "The server is running on IP: " << ipAddress << " Port: " << tcpServer->serverPort() << endl;

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendFortune()));
}

void TcpServer::sendFortune()
{
    qDebug() << "New Connection." << endl;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << fortunes.at(qrand() % fortunes.size());
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),
            clientConnection, SLOT(deleteLater()));

    clientConnection->write(block);
    clientConnection->disconnectFromHost();
    //clientConnection->deleteLater();
}
