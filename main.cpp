#include "maindialog.h"
#include <QFile>
#include <QApplication>

void appAutoRun(bool bAutoRun);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    appAutoRun(true);

    Q_INIT_RESOURCE(style1);

    QFile qss("style.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

    MainDialog w;
    w.show();

    return a.exec();
}

//开机自启
void appAutoRun(bool bAutoRun)
{
    QString appName = QApplication::applicationName();//程序名称

    QString appPath = QApplication::applicationFilePath();// 程序路径

    appPath = appPath.replace("/","\\");

    //HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
    QSettings  *reg=new QSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);

    if (bAutoRun)
    {
        QString val = reg->value(appName).toString();// 如果此键不存在，则返回的是空字符串
        if(val != appPath)
        reg->setValue(appName,appPath);
    }
    else
    {
        reg->remove(appName);
    }
    reg->deleteLater();
}
