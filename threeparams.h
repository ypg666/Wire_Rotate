/*********************************************************************************
  *Copyright(C)
  *ClassName:  threeParams
  *Author:  佳豪
  *Version: 1.0
  *Date:  2019.7.12
  *Description: 算法参数窗口（选择设置哪个颜色的参数）
  *             write_params(std::vector<std::vector<int>> &params1); 初始化时把算法参数传入，得到保存的算法参数用于后续算法初始化
  *Others:  //其他内容说明
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
  *History:
  *          加入了write_params(std::vector<std::vector<int>> &params1);用于初始化算法参数  //2019.7.12 璞光
**********************************************************************************/
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
