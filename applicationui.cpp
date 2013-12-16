#include "applicationui.h"

ApplicationUI::ApplicationUI()
{
    tcpServer = new TcpServer();
}

ApplicationUI::~ApplicationUI()
{
    delete tcpServer;
}
