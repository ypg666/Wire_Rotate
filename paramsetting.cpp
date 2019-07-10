#include "paramsetting.h"


void ParamSetting::writeIni(QString param, std::vector<int> value)
{
    filepath = filepath.append(name);
    QSettings ini(this->filepath, QSettings::IniFormat);
    ini.beginGroup(param);
    std::vector<QString> keyStr = {"Hmin", "Hmax", "Smin", "Smax", "Vmin", "Vmax", "Crmin", "Crmax", "Cbmin", "Cbmax"};
    for(int i = 0; i < 10; i++){
        ini.setValue(keyStr[i], value[i]);
    }
    ini.endGroup();

    qDebug() << "Writing Data Successfully !!!" << endl;
}

void ParamSetting::readIni(QString param, std::vector<int> &value)
{

    filepath = filepath.append(name);
    QSettings ini(this->filepath, QSettings::IniFormat);

    QStringList strList = ini.childGroups();

    if(strList.contains(param)){
        ini.beginGroup(param);
        std::vector<QString> keyStr = {"Hmin", "Hmax", "Smin", "Smax", "Vmin", "Vmax", "Crmin", "Crmax", "Cbmin", "Cbmax"};
        for(int i = 0; i < 10; i++){
            value[i] = ini.value(keyStr[i]).toInt();
        }
        ini.endGroup();

        qDebug() << "Reading Data Successfully !!!" << endl;
    }

}


