#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "msvc_macro.h"
#include "historyimage.h"
#include "password.h"
#include "cameradisplay.h"
#include "debugMode.h"
#include "mainwindow.h"
#include "TIS_Camera.h"
#include "Listener1.h"//回调头文件
#include "LineRotate.h"
#include "easyModbus02.h"
#include "sysdate.h"
#include <QDialog>
#include <QTimer>
#include <QTime>
#include <QStatusBar>

#define image_path "C:/Users/Administrator/Desktop/1/"  //存放图片的路径
namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();
    HistoryImage w1;
    Password w2;
    debugMode w3;
//    MainWindow w4;
//    CameraDisplay *ca;
    DShowLib::Grabber *pGrabber;
    TIS_Camera cam;
//    Listener1 *pListener1; //回调对象
    easyModbus2 easymodbus;
    SysDate p; //数据类
public slots:
    void normal();
    void show1(int l);
    void grab1();
    void caculate1();
    void outcome1();
    void outcome2(int val);  //直接输出角度
    void set_deflection(int val);  //设置偏转角度
private slots:
    void fun();
    void historyimage();
    void debug();
    void password();
    void password1();
//    void modbus();
    void onTimerOut();
private:
    Ui::MainDialog *ui;
    QTimer *timer; //时间
    int num=0;  //本次检测数量
    QString num1; //本次检测数量的显示值
    int i=10;  //已无用
    int l1;  //上次检测角度
    Mat grab_img; //抓图
    int rotate = 0; //调试时的检测角度
};

#endif // MAINDIALOG_H
