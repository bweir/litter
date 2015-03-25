#include "Litter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("LameStation");
    QCoreApplication::setOrganizationDomain("www.lamestation.com");
#ifdef VERSION
    QCoreApplication::setApplicationVersion(VERSION);
#endif
    QCoreApplication::setApplicationName("litter");



    Litter * w = new Litter();
    w->show();

    return app.exec();
}
