﻿/*******************************************************************************
* 类 名         : SysDate
* 类功能		   : 系统界面数据
* 输    入         : setpass(QString p) 设置密码
*                   setpic(QString p） 设置存储图片数量
* 输    出         : readpass() 读取密码
*                   readpic() 读取存储图片数量
*******************************************************************************/
#ifndef SYSDATE_H
#define SYSDATE_H

#include<QString>
#include<QSettings>

class SysDate
{
public:
    SysDate();
    const QString filepath ="C:/Users/Administrator/Desktop/1/Config.ini";
    void setpass(QString p);
    QString readpass();
    void setpic(QString p);
    int readpic();
    void sethis(QString p);
    QString readhis();
    void setcur(int p);
    int readcur();
    void set_deflection(int  p);
    int read_deflection();
    void initFromConfig();
private:
    static QString password; //一定要记得初始化，对于静态变量，不然编译通不过
    static QString picnum;  //存储数量
    static QString hisnum;  //历史检测数量
    static QString curnum;  //图片保存时，当前的序号
    static QString deflection;  //偏转角度
    void writeConfig(QString  p,QString  q,QString  z,QString  x,QString deflection1);
};

#endif // SYSDATE_H
