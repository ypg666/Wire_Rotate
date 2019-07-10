#ifndef THREEPARAMS_H
#define THREEPARAMS_H

#include <QDialog>
#include <vector>
#include <QDebug>
#include <QPixmap>

#include "adjustparameters.h"
#include "paramsetting.h"

#include<opencv2/opencv.hpp>


namespace Ui {
class threeParams;
}

class threeParams : public QDialog
{
    Q_OBJECT

public:
    explicit threeParams(QWidget *parent = 0);
    ~threeParams();

    void write_params(std::vector<std::vector<int>> &params1);//读算法参数
signals:
    void sendCvMat(cv::Mat img);

private slots:
    void on_pb_Yellow_clicked();

    void on_pb_Green_clicked();

    void on_pb_Blue_clicked();

    void on_pb_Brown_clicked();

signals:
    void paramWinTitleChanged(QString winTitle);

    void paramMinChanged(std::vector<int> params);
    void paramMaxChanged(std::vector<int> params);
    void paramDefaultChanged(std::vector<int> params);


private:
    Ui::threeParams *ui;
    AdjustParameters *wd_AP;
    std::vector<int> params;
    ParamSetting fileReader;

public:
    cv::Mat inputImg;
    bool hasInputImg = false;
};

#endif // THREEPARAMS_H
