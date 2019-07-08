#include "sysdate.h"

QString SysDate::password ="";
QString SysDate::picnum ="";
QString SysDate::hisnum ="";
QString SysDate::curnum ="";
QString SysDate::deflection ="";


SysDate::SysDate()
{

}

void SysDate::setpass(QString  p)
{
    password = p;
    writeConfig(p,picnum,hisnum,curnum,deflection);
}

QString SysDate::readpass()
{
    return password;
}
void SysDate::setpic(QString  p) //保存图片最大数量
{
    picnum = p;
    writeConfig(password,p,hisnum,curnum,deflection);
}

int SysDate::readpic()
{
    int i= picnum.toInt();
    return i;
}
void SysDate::sethis(QString  p)
{
    hisnum = p;
    writeConfig(password,picnum,p,curnum,deflection);
}

QString SysDate::readhis()  //历史检测数量
{
    return hisnum;
}
void SysDate::setcur(int  p)
{
    curnum = QString::number(p);
    writeConfig(password,picnum,hisnum,curnum,deflection);
}

int SysDate::readcur()
{
    int i= curnum.toInt();
    return i;
}
void SysDate::set_deflection(int  p)
{
     deflection = QString::number(p);
     writeConfig(password,picnum,hisnum,curnum,deflection);
        }
int SysDate::read_deflection()
{
    int i= deflection.toInt();
    return i;
}
void SysDate::initFromConfig(){
    QString key;
    QSettings ini(filepath, QSettings::IniFormat);
    ini.beginGroup(QString("System_Data"));
    key.sprintf("password");
    password = ini.value(key).toString();
    key.sprintf("picture_number");
    picnum = ini.value(key).toString();
    key.sprintf("history_number");
    hisnum = ini.value(key).toString();
    key.sprintf("current_number");
    curnum = ini.value(key).toString();
    key.sprintf("deflection");
    deflection = ini.value(key).toString();
    ini.endGroup();
}

void SysDate::writeConfig(QString  p,QString  q,QString  z,QString  x,QString  deflection1)
{
            QSettings ini(filepath, QSettings::IniFormat);
                ini.beginGroup(QString("System_Data"));
                QString key;
                key.sprintf("password");
                ini.setValue(key, p);
                key.sprintf("picture_number");
                ini.setValue(key, q);
                key.sprintf("history_number");
                ini.setValue(key, z);
                key.sprintf("current_number");
                ini.setValue(key, x);
                key.sprintf("deflection");
                ini.setValue(key, deflection1);
                ini.endGroup();

}
