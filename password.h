/*******************************************************************************
* 类 名         : Password
* 类功能		   : 密码界面
* 输    入         : setflag(int i)  i=o对应系统设置界面，i=1对应IO设置界面
* 输    出         : 无
*******************************************************************************/
#ifndef PASSWORD_H
#define PASSWORD_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "sysdate.h"
#include "sys.h"
#include "TIS_Camera.h"
#include "TIS_Camera2.h"



namespace Ui {
class Password;
}

class Password : public QDialog
{
    Q_OBJECT

public:
    explicit Password(QWidget *parent = 0);
    ~Password();
    SysDate p;
    Sys w3;
//    TIS_Camera w4;
    QString q;
    void setflag(int i);
signals:
    void fin();
private slots:
    void on_loginBtn_clicked();
    void finish();

private:
    Ui::Password *ui;
    static int flag;
};

#endif // PASSWORD_H
