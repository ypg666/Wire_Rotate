#ifndef MAINDIALOG_H
#define MAINDIALOG_H

//#include "msvc_macro.h"
#include "historyimage.h"
#include "password.h"
#include "cameradisplay.h"
#include "debugMode.h"
#include "mainwindow.h"
#include "TIS_Camera.h"
#include "sysdate.h"
#include <QDialog>
#include <QTimer>
#include <QTime>

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
    MainWindow w4;
    CameraDisplay *ca;
    DShowLib::Grabber *pGrabber;
    TIS_Camera cam;
    SysDate p;
private slots:
    void fun();
    void historyimage();
    void debug();
    void password();
    void password1();
    void grab();
    void modbus();
    void onTimerOut();
private:
    Ui::MainDialog *ui;
    QTimer *timer;
    int num=0;
    QString num1;
    int i=10;
};

#endif // MAINDIALOG_H
