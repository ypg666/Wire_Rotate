#ifndef PARAMSETTING_H
#define PARAMSETTING_H

#include <QString>
#include <QSettings>
#include <vector>
#include <string>
#include <QDebug>
#include <QStringList>
#include<QStandardPaths>

class ParamSetting
{
public:
    ParamSetting() = default;

    void writeIni(QString param, std::vector<int> value);

    void readIni(QString param, std::vector<int> &value);



private:
    //const QString filepath ="paramSetting.ini";
    QString filepath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QString name = "/paramSetting.ini";

    const QString blueParam = "Blue";
    const QString greenParam = "Green";
    const QString yellowParam = "Yellow";
    const QString brownParam = "Brown";

};

#endif // PARAMSETTING_H
