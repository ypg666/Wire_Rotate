#include "sysdate.h"

QString SysDate::password ="";
QString SysDate::picnum ="";
QString SysDate::hisnum ="";

SysDate::SysDate()
{

}

void SysDate::setpass(QString  p)
{
    password = p;
    writeConfig(p,picnum,hisnum);
}

QString SysDate::readpass()
{
    return password;
}
void SysDate::setpic(QString  p)
{
    picnum = p;
    writeConfig(password,p,hisnum);
}

QString SysDate::readpic()
{
    return picnum;
}
void SysDate::sethis(QString  p)
{
    hisnum = p;
    writeConfig(password,picnum,p);
}

QString SysDate::readhis()
{
    return hisnum;
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
    ini.endGroup();
}

void SysDate::writeConfig(QString  p,QString  q,QString  z)
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
                ini.endGroup();

}
