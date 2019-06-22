#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <opencv2\opencv.hpp>
#include <fstream>


enum SELECT{
    YELLOWGREENMASK,
    BROWNMASK,
    BLUEMASK
};

class LineRotate
{
public:
    LineRotate();
    ~LineRotate();
    int getRotate(cv::Mat srcImage);
    int getRotate(cv::Mat srcImage, bool debug, std::string debugFilePath);
    inline void clearTempData() {
        yellowgreenBlockAreaContour.clear();
        brownBlockAreaContour.clear();
        blueBlockAreaContour.clear();
        yellowgreenBlockAreaSum = 0.0;
        brownBlockAreaSum = 0.0;
        blueBlockAreaSum = 0.0;
        yellowgreenBlockPosition = 0.0;
        brownBlockPosition = 0.0;
        blueBlockPosition = 0.0;
        originImage.release();
    }
private:
    //私有变量
    bool debug = false;
    std::string debugFilePath = "D:/lineDebug";
    std::ofstream logHandle;
    std::string errorImageFolder;

    cv::Mat originImage;

    // 计算角度时需要用到的中间变量值
    std::vector< cv::Point> yellowgreenBlockAreaContour;
    std::vector< cv::Point> brownBlockAreaContour;
    std::vector< cv::Point> blueBlockAreaContour;
    float yellowgreenBlockAreaSum;
    float brownBlockAreaSum;
    float blueBlockAreaSum;
    float yellowgreenBlockPosition;
    float brownBlockPosition;
    float blueBlockPosition;

    //私有方法函数
    void getRoIImage(cv::Mat &image, cv::Mat &result);
    void getColorMask(cv::Mat &image);
    void getBlockInfo();
    inline void setDebugInfoPath(std::string path) {
        debugFilePath = path;
    }
    //辅助小/工具函数
    void findBlockMaxContour(cv::Mat maskImage, SELECT block);
};

