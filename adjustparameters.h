/*********************************************************************************
  *Copyright(C)
  *ClassName:  AdjustParameters
  *Author:  佳豪
  *Version: 1.0
  *Date:  2019.7.12
  *Description: 算法参数调整窗口
  *Others:  //其他内容说明
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
  *History:
  *
**********************************************************************************/
#ifndef ADJUSTPARAMETERS_H
#define ADJUSTPARAMETERS_H

#include <QDialog>
#include <vector>
#include <QDebug>
#include <QString>
#include <QPixmap>
#include <QImage>

#include "paramsetting.h"

#include <opencv2/opencv.hpp>
#include "ClassThresholdTools.h"
#include <QMessageBox>

namespace Ui {
class AdjustParameters;
}

class AdjustParameters : public QDialog
{
    Q_OBJECT

public:
    explicit AdjustParameters(QWidget *parent = 0);
    ~AdjustParameters();

public slots:

    void setWinTitle(QString winTitle);

    void setParamMin(std::vector<int> params);
    void setParamMax(std::vector<int> params);
    void setParamDefault(std::vector<int> params);

    void setInDisplay(cv::Mat inputImg);

private slots:
    void on_saveParams_clicked();

    void on_resetParams_clicked();

    void updateParamValue();

private:
    QImage cvMat2QImage(cv::Mat mat);


private:
    Ui::AdjustParameters *ui;

    LineRotate lineRotate; //算法

    QString winTitle = "";

    std::vector<int> paramMax;
    std::vector<int> paramMin;
    std::vector<int> paramDefault;

    std::vector<int> paramValue;

    std::vector<int> paramYellowDefault = {120, 40, 0, 255, 25, 255, 0, 255, 0, 100};
    std::vector<int> paramGreenDefault = {45, 100, 70, 255, 25, 255, 0, 255, 0, 255};
    std::vector<int> paramBlueDefault = {100, 120, 30, 255, 25, 255, 0, 255, 0, 255};
    std::vector<int> paramBrownDefault = {120, 40, 0, 255, 25, 255, 0, 255, 100, 255};



    // === 用作实时处理的图像 === //
    cv::Mat inputImage;
    const int setHeight = 300;
    const int setWidth = 765;

public:
     bool updataOutDisplay = false;
     ClassThresholdTools thresholdTools;
};

#endif // ADJUSTPARAMETERS_H
