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

