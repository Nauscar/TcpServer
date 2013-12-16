#ifndef APPLICATIONUI_H
#define APPLICATIONUI_H

#include "tcpserver.h"

class ApplicationUI
{
public:
    ApplicationUI();
    ~ApplicationUI();
private:
    TcpServer* tcpServer;
};

#endif // APPLICATIONUI_H
