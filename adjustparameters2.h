/*********************************************************************************
  *Copyright(C)
  *ClassName:  AdjustParameters2
  *Author:  �Ѻ�
  *Version: 1.0
  *Date:  2019.7.12
  *Description: �㷨������������
  *Others:  //��������˵��
  *Function List:  //��Ҫ�����б���ÿ����¼Ӧ���������������ܼ�Ҫ˵��
  *History:
  *
**********************************************************************************/
#ifndef AdjustParameters2_H
#define AdjustParameters2_H

#include <QDialog>
#include <vector>
#include <QDebug>
#include <QString>
#include <QPixmap>
#include <QImage>

#include "ParamSetting2.h"

#include <opencv2/opencv.hpp>
#include "ClassThresholdTools.h"
#include <QMessageBox>

namespace Ui {
class AdjustParameters2;
}

class AdjustParameters2 : public QDialog
{
    Q_OBJECT

public:
    explicit AdjustParameters2(QWidget *parent = 0);
    ~AdjustParameters2();

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
    Ui::AdjustParameters2 *ui;

    LineRotate lineRotate; //�㷨

    QString winTitle = "";

    std::vector<int> paramMax;
    std::vector<int> paramMin;
    std::vector<int> paramDefault;

    std::vector<int> paramValue;

    std::vector<int> paramYellowDefault = {120, 40, 0, 255, 25, 255, 0, 255, 0, 100};
    std::vector<int> paramGreenDefault = {45, 100, 70, 255, 25, 255, 0, 255, 0, 255};
    std::vector<int> paramBlueDefault = {100, 120, 30, 255, 25, 255, 0, 255, 0, 255};
    std::vector<int> paramBrownDefault = {120, 40, 0, 255, 25, 255, 0, 255, 100, 255};



    // === ����ʵʱ������ͼ�� === //
    cv::Mat inputImage;
    const int setHeight = 300;
    const int setWidth = 765;

public:
     bool updataOutDisplay = false;
     ClassThresholdTools thresholdTools;
};

#endif // AdjustParameters2_H