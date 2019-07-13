/*********************************************************************************
  *Copyright(C)
  *ClassName:  ClassThresholdTools
  *Author:  昊杰
  *Version: 1.0
  *Date:  2019.7.12
  *Description: 算法阈值调整，算法参数调节的内核
  *             通过佳豪的AdjustParameters，threeParams调用。
  *             threeParams -> AdjustParameters -> ClassThresholdTools
  *Others:  //其他内容说明
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
  *History:  //修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介
**********************************************************************************/
#pragma once
#include "opencv2/opencv.hpp"
#include <iostream>
#include "LineRotate.h"


class ClassThresholdTools:public LineRotate
{
public:
    ClassThresholdTools();
    ~ClassThresholdTools();
    void getThresholdResult(cv::Mat src, cv::Mat &dst, std::vector<int> &params);
private:
};

