/*********************************************************************************
  *Copyright(C)
  *ClassName:  ParamSetting
  *Author:  佳豪
  *Version: 1.0
  *Date:  2019.7.12
  *Description: 算法参数数据读写
  *             存入了paramSetting.ini文件
  *Others:  //其他内容说明
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
  *History:
  *         将存储路径改为了USER目录，后续考虑改为存在当前目录 // 2019.7.12 璞光
**********************************************************************************/
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
