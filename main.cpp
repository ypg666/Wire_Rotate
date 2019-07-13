/*********************************************************************************
  *Copyright(C)
  *ClassName:  main
  *Author:  璞光
  *Version: 1.0
  *Date:  2019.7.12
  *Description: main启动函数
  *Others:   命令行不同指令启动，测试没反应，还没找到原因
  *Function List:  appAutoRun(bool bAutoRun) //写入注册表自启
  *                bool checkOnly(); //判断是否重复启动，返回false重复启动
  *                void IpConfig(); //设置本机IP（与网口相机匹配）
  *History:  //修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介
**********************************************************************************/
#include "maindialog.h"
#include <QFile>
#include <QApplication>
#include <windows.h>
#include <QProcess>

void appAutoRun(bool bAutoRun);
bool checkOnly();
void IpConfig();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //检测程序重复启动
    if(checkOnly()==false)
    {return 0;}

    //设置本机IP（连相机）
    IpConfig();
    //命令行启动方式 是否加自启
  if(argc == 1)
  {
    appAutoRun(true);

    printf("Auto Run ! ");
  }
  //else if (argv[1] == "d")
  else
  {
      appAutoRun(false);
      printf("delete successful ! ");
  }

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
//防止程序重复启动
bool checkOnly()
{
    //  创建互斥量
    HANDLE m_hMutex  =  CreateMutex(NULL, FALSE,  L"fortest_abc123" );
    //  检查错误代码
    if  (GetLastError()  ==  ERROR_ALREADY_EXISTS)  {
      //  如果已有互斥量存在则释放句柄并复位互斥量
     CloseHandle(m_hMutex);
     m_hMutex  =  NULL;
      //  程序退出
      return  false;
    }
    else
        return true;
}

void IpConfig()
{
    QProcess *process = new QProcess();
    //网卡名称
    QString name = "\"以太网\" ";
    QString cmd = "netsh interface ipv4 set address name = " + name + "source = static address = 218.192.162.1 ";

    qDebug()<<"cmd = "<<cmd;
    process->start(cmd);   //执行dos命令
    process->waitForFinished(); //等待执行完成
    delete process;
}
