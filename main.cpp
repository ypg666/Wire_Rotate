#include "maindialog.h"
#include <QFile>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(style1);

    QFile qss("style.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

    MainDialog w;
    w.show();

    return a.exec();
}
