#include "ClassThresholdTools.h"


ClassThresholdTools::ClassThresholdTools()
{
}


ClassThresholdTools::~ClassThresholdTools()
{
}

void ClassThresholdTools::getThresholdResult(cv::Mat src, cv::Mat & dst, std::vector<int>& argv)
{
    cv::Mat ROIImage;
    const int hMin = argv[0];
    const int hMax = argv[1];
    const int sMin = argv[2];
    const int sMax = argv[3];
    const int vMin = argv[4];
    const int vMax = argv[5];
    const int crMin = argv[6];
    const int crMax = argv[7];
    const int cbMin = argv[8];
    const int cbMax = argv[9];

    try
    {
        getRoIImage(src, ROIImage);
    }
    catch (const std::exception& e)
    {
        std::cout << "获取图片的ROI区域失败" << std::endl;
        throw 1;
    }
    ROIImage.copyTo(src);

    std::vector<cv::Mat> HSV, ycrcb;
    cv::Mat src_hsv, src_ycrcb, mask;
    cv::cvtColor(ROIImage, src_hsv, cv::COLOR_BGR2HSV);

    cv::split(src_hsv, HSV);

    // 先对H通道进行分割
    cv::Mat hmask1, hmask2, hmask;
    cv::threshold(HSV[0], hmask1, hMin, 255, cv::THRESH_BINARY);
    cv::threshold(HSV[0], hmask2, hMax, 255, cv::THRESH_BINARY_INV);
    if (hMin < hMax)
    {
        cv::bitwise_and(hmask1, hmask2, hmask);
    }
    else
    {
        cv::bitwise_or(hmask1, hmask2, hmask);
    }

    // 对S通道进行分割
    cv::Mat smask1, smask2, smask;
    cv::threshold(HSV[1], smask1, sMin, 255, cv::THRESH_BINARY);
    cv::threshold(HSV[1], smask2, sMax, 255, cv::THRESH_BINARY_INV);
    cv::bitwise_and(smask1, smask2, smask);

    // 对V通道进行分割
    cv::Mat vmask1, vmask2, vmask;
    cv::threshold(HSV[2], vmask1, vMin, 255, cv::THRESH_BINARY);
    cv::threshold(HSV[2], vmask2, vMax, 255, cv::THRESH_BINARY_INV);
    cv::bitwise_and(vmask1, vmask2, vmask);


    cv::bitwise_and(smask, vmask, mask);
    cv::bitwise_and(mask, hmask, mask);
    cv::Mat dst_temp;
    cv::bitwise_and(src, src, dst_temp, mask);

    cv::cvtColor(dst_temp, src_ycrcb, cv::COLOR_BGR2YCrCb);
    cv::split(src_ycrcb, ycrcb);

    // 对cr通道进行分割
    cv::Mat crmask1, crmask2, crmask;
    cv::threshold(ycrcb[1], crmask1, crMin, 255, cv::THRESH_BINARY);
    cv::threshold(ycrcb[1], crmask2, crMax, 255, cv::THRESH_BINARY_INV);
    cv::bitwise_and(crmask1, crmask2, crmask);

    // 对cb通道进行分割
    cv::Mat cbmask1, cbmask2, cbmask;
    cv::threshold(ycrcb[2], cbmask1, cbMin, 255, cv::THRESH_BINARY);
    cv::threshold(ycrcb[2], cbmask2, cbMax, 255, cv::THRESH_BINARY_INV);
    cv::bitwise_and(cbmask1, cbmask2, cbmask);

    cv::bitwise_and(mask, crmask, mask);
    cv::bitwise_and(mask, cbmask, mask);

    cv::bitwise_and(src, src, dst, mask);

}

