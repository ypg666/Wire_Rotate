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
#include <QtWin>
#include <QMessageBox>

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
    //创建对象命名不规范！
    HistoryImage w1;  //历史图像窗口
    Password w2;    //密码窗口
    debugMode w3; //调试窗口
//    MainWindow w4;
//    CameraDisplay *ca;
    DShowLib::Grabber *pGrabber; //抓图
    TIS_Camera cam; //相机
//    Listener1 *pListener1; //回调对象
    easyModbus2 easymodbus;
    SysDate p; //数据类
public slots:
    void normal(); //实时显示图像
    void show1(int l);  //  算法处理完成后续主界面显示处理
    void grab1();   //调试窗口抓图
    void caculate1();   //调试窗口计算
    void outcome1();    //调试输出角度
    void outcome2(int val);  //直接输出角度
    void set_deflection(int val);  //设置偏转角度
private slots:
    void fun(); //开始检测 进入触发模式
    void historyimage();     //历史图像界面
    void debug();   //调试界面
    void password();    //系统设置
    void password1();   //相机设置
    void onTimerOut();  //时钟
private:
    Ui::MainDialog *ui;
    QTimer *timer; //时间
    int num=0;  //本次检测数量
    QString num1; //本次检测数量的显示值
    int i=10;  //已无用
    int l1;  //上次检测角度
    Mat grab_img; //抓图
    int rotate = 0; //调试时的检测角度
    int easy = 0; //串口检测flag
    int temp =0;//偏转角度临时计算

    void detect_IO();//检测串口连接
    void detect_cam(); //检测相机连接
};

#endif // MAINDIALOG_H
