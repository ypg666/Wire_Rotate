/*********************************************************************************
  *Copyright(C)
  *ClassName:  LineRotate2
  *Author:  昊杰
  *Version: 1.0
  *Date:  2019.7.12
  *Description: 检测算法类
                先init(std::vector<std::vector<int>> params) 输入算法参数初始化
                int getRotate(cv::Mat srcImage);输入图片输出角度，注意catch错误
                重载int getRotate(cv::Mat srcImage, bool debug, std::string debugFilePath) 可以调试模式生产错误日志
                void clearTempData()清除临时数据
  *Others:  //其他内容说明
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
  *History:
  *         将存放算法参数的thresholdValue2结构体改为了静态变量，使主逻辑中的调试计算和回调中的计算两个对象
  *         通过一个初始化函数得到同样的算法参数。  // 2019.7.12  璞光
**********************************************************************************/
#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <opencv2\opencv.hpp>
#include <fstream>


enum SELECT2{
    YELLOWGREENMASK2,
    BROWNMASK2,
    BLUEMASK2
};

struct thresholdValue2
{
    int blue_h_min = 0;
    int blue_h_max = 180;
    int blue_s_min = 0;
    int blue_s_max = 255;
    int blue_v_min = 0;
    int blue_v_max = 255;
    int blue_cr_min = 0;
    int blue_cr_max = 255;
    int blue_cb_min = 0;
    int blue_cb_max = 255;

    int green_h_min = 0;
    int green_h_max = 180;
    int green_s_min = 0;
    int green_s_max = 255;
    int green_v_min = 0;
    int green_v_max = 255;
    int green_cr_min = 0;
    int green_cr_max = 255;
    int green_cb_min = 0;
    int green_cb_max = 255;

    int yellow_h_min = 0;
    int yellow_h_max = 180;
    int yellow_s_min = 0;
    int yellow_s_max = 255;
    int yellow_v_min = 0;
    int yellow_v_max = 255;
    int yellow_cr_min = 0;
    int yellow_cr_max = 255;
    int yellow_cb_min = 0;
    int yellow_cb_max = 255;

    int brown_h_min = 0;
    int brown_h_max = 180;
    int brown_s_min = 0;
    int brown_s_max = 255;
    int brown_v_min = 0;
    int brown_v_max = 255;
    int brown_cr_min = 0;
    int brown_cr_max = 255;
    int brown_cb_min = 0;
    int brown_cb_max = 255;
};

class LineRotate2
{
public:
    LineRotate2();
    ~LineRotate2();
    void init(std::vector<std::vector<int>> params);
    void init(std::vector<int> params, int flag);
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
    int read();

protected:
    void getRoIImage(cv::Mat &image, cv::Mat &result);
    static thresholdValue2 thresholdValue2_struct; //尝试静态变量
//    thresholdValue2 thresholdValue2_struct;

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
    void getColorMask(cv::Mat &image);
    void getBlockInfo();
    inline void setDebugInfoPath(std::string path) {
        debugFilePath = path;
    }
    //辅助小/工具函数
    void findBlockMaxContour(cv::Mat maskImage, SELECT2 block);
};

