#include <QCoreApplication>

#include "applicationui.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ApplicationUI* app = new ApplicationUI();

    return a.exec();
}
