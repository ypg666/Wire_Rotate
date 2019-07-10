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
