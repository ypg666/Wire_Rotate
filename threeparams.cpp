#include "threeparams.h"
#include "ui_threeparams.h"

threeParams::threeParams(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::threeParams)
{
    ui->setupUi(this);

    wd_AP = new AdjustParameters(this);
    connect(this, &threeParams::paramMinChanged, wd_AP, &AdjustParameters::setParamMin);
    connect(this, &threeParams::paramMaxChanged, wd_AP, &AdjustParameters::setParamMax);
    connect(this, &threeParams::paramDefaultChanged, wd_AP, &AdjustParameters::setParamDefault);
    connect(this, &threeParams::paramWinTitleChanged, wd_AP, &AdjustParameters::setWinTitle);
    connect(this, &threeParams::sendCvMat, wd_AP, &AdjustParameters::setInDisplay);
}

threeParams::~threeParams()
{
    delete ui;
}

void threeParams::on_pb_Yellow_clicked()
{
    QString winTitle = QString::fromLocal8Bit("黄色通道参数调整");
    emit paramWinTitleChanged(winTitle);

    std::vector<int> paramMin(10, 0);
    std::vector<int> paramMax = {180, 180, 255, 255, 255, 255, 255, 255, 255, 255};

    // === 从ini文件中，读取参数 === //
    std::vector<int> paramDefault = {120, 40, 0, 255, 25, 255, 0, 255, 0, 100};
    QString channelStr;
    channelStr.sprintf("Yellow");
    fileReader.readIni(channelStr, paramDefault);

    emit paramMinChanged(paramMin);
    emit paramMaxChanged(paramMax);
    emit paramDefaultChanged(paramDefault);

    //QPixmap inputImg2 = QPixmap::fromImage(QImage(inFrame.data, inFrame.cols,
     //                                               inFrame.rows, inFrame.step, QImage::Format_RGB888).rgbSwapped());
    wd_AP->updataOutDisplay = false;
    if(hasInputImg){
        emit sendCvMat(this->inputImg);
    }

    wd_AP->show();
}

void threeParams::on_pb_Green_clicked()
{
    QString winTitle = QString::fromLocal8Bit("绿色通道参数调整");
    emit paramWinTitleChanged(winTitle);

    // qDebug() << "hello" << endl;
    std::vector<int> paramMin(10, 0);
    std::vector<int> paramMax = {180, 180, 255, 255, 255, 255, 255, 255, 255, 255};
    std::vector<int> paramDefault = {45, 100, 70, 255, 25, 255, 0, 255, 0, 255};

    fileReader.readIni(QString("Green"), paramDefault);

    emit paramMinChanged(paramMin);
    emit paramMaxChanged(paramMax);
    emit paramDefaultChanged(paramDefault);
    wd_AP->updataOutDisplay = false;
    if(hasInputImg){
        emit sendCvMat(this->inputImg);
    }

    wd_AP->show();
}

void threeParams::on_pb_Blue_clicked()
{
    QString winTitle = QString::fromLocal8Bit("蓝色通道参数调整");
    emit paramWinTitleChanged(winTitle);

    std::vector<int> paramMin(10, 0);
    std::vector<int> paramMax = {180, 180, 255, 255, 255, 255, 255, 255, 255, 255};
    std::vector<int> paramDefault = {100, 120, 30, 255, 25, 255, 0, 255, 0, 255};

    fileReader.readIni(QString("Blue"), paramDefault);

    emit paramMinChanged(paramMin);
    emit paramMaxChanged(paramMax);
    emit paramDefaultChanged(paramDefault);

    wd_AP->updataOutDisplay = false;
    if(hasInputImg){
        emit sendCvMat(this->inputImg);
    }

    wd_AP->show();
}

void threeParams::on_pb_Brown_clicked()
{
    QString winTitle = QString::fromLocal8Bit("棕色通道参数调整");
    emit paramWinTitleChanged(winTitle);

    std::vector<int> paramMin(10, 0);
    std::vector<int> paramMax = {180, 180, 255, 255, 255, 255, 255, 255, 255, 255};
    std::vector<int> paramDefault = {120, 40, 0, 255, 25, 255, 0, 255, 100, 255};

    fileReader.readIni(QString("Brown"), paramDefault);

    emit paramMinChanged(paramMin);
    emit paramMaxChanged(paramMax);
    emit paramDefaultChanged(paramDefault);

    wd_AP->updataOutDisplay = false;
    if(hasInputImg){
        emit sendCvMat(this->inputImg);
    }

    wd_AP->show();
}

void threeParams::write_params(std::vector<std::vector<int>> &params1)
{
    std::vector<int> blueThreshold{ 100, 120, 30, 255, 25, 255, 0, 255, 0, 255 };
    std::vector<int> greenThreshold{ 45, 100, 70, 255, 50, 255, 0, 255, 0, 255 };
    std::vector<int> yellowThreshold{ 120, 40, 0, 255, 50, 255, 0, 255, 0, 100 };
    std::vector<int> brownThreshold{ 120, 40, 0, 255, 40, 255, 0, 255, 101, 255 };


    QString channelStr;
    channelStr.sprintf("Blue");
    fileReader.readIni(channelStr, blueThreshold);

    channelStr.sprintf("Green");
    fileReader.readIni(channelStr, greenThreshold);

    channelStr.sprintf("Yellow");
    fileReader.readIni(channelStr, yellowThreshold);

    channelStr.sprintf("Brown");
    fileReader.readIni(channelStr, brownThreshold);

    params1.push_back(blueThreshold);
    params1.push_back(greenThreshold);
    params1.push_back(yellowThreshold);
    params1.push_back(brownThreshold);
}
