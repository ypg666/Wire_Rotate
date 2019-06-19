/*******************************************************************************
* 类 名         : Sys
* 类功能		   : 系统设置界面
* 输    入         : 不用管，直接通过密码界面设置flag打开
* 输    出         : 无
*******************************************************************************/
#ifndef SYS_H
#define SYS_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include "sysdate.h"

namespace Ui {
class Sys;
}

class Sys : public QDialog
{
    Q_OBJECT

public:
    explicit Sys(QWidget *parent = 0);
    ~Sys();
    SysDate p;
private slots:
    void Password();
    void PicNum();
private:
    Ui::Sys *ui;
};

#endif // SYS_H
