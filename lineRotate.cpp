// lineRotate.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "LineRotate.h"
#include "ClassThresholdTools.h"
#include <opencv2\opencv.hpp>
#include <cmath>
#include <numeric>
#include <time.h>
#include <io.h>
#include <direct.h>
#include <QDebug>

thresholdValue LineRotate::thresholdValue_struct;
/*
int main()
{
    std::cout << "Hello World!\n"; 
    cv::Mat testImage = cv::imread("E:/outpack/line/line1/image35.bmp");
    std::vector<std::vector<int>> params;
    std::vector<int> blueThreshold{ 100, 120, 30, 255, 25, 255, 0, 255, 0, 255 };
    std::vector<int> greenThreshold{ 45, 100, 70, 255, 50, 255, 0, 255, 0, 255 };
    std::vector<int> yellowThreshold{ 120, 40, 0, 255, 50, 255, 0, 255, 0, 100 };
    std::vector<int> brownThreshold{ 120, 40, 0, 255, 40, 255, 0, 255, 101, 255 };
    params.push_back(blueThreshold);
    params.push_back(greenThreshold);
    params.push_back(yellowThreshold);
    params.push_back(brownThreshold);
    //调用方法：
    //首先实例化一个对象，调用getRotate方法，根据重载不同，可以分别调用debug模式或者普通模式
    //在debug模式下需要输入debug信息的路径，这个路径是文件夹路径，做如下约定：路径中的斜杠统一采用正斜杠/而不采用反斜杠\；表示路径的url后面必须以/结尾
    //实际使用过程中尽量使用try…catch方法调用getRotate函数，根据抛出的异常大概确定问题所在，目前异常抛出的类型为整型，请用int类型捕获
    LineRotate *lineRotate = new LineRotate(); 
    lineRotate->init(params);
    int rotate = 0;
    try {
        //rotate = lineRotate.getRotate(testImage, true, "D:/lineDebug/");
        rotate = lineRotate->getRotate(testImage);
        lineRotate->clearTempData(); // 这一句可加 可不加 有洁癖的话可以加一下确保每次检测完后回到初始值
    }
    catch (const int errorcode)
    {
        std::cout << "ERROR CODE: "<< errorcode << std::endl;
    }
    std::cout << rotate << std::endl;

    // 调节工具测试
    //ClassThresholdTools tools;
    //cv::Mat result;
    //std::vector<int> params { 120,40,0,255,25,255,0,255,100,255};
    //tools.getThresholdResult(testImage, result, params);
    //cv::imshow("result", result);
    //cv::waitKey(0);
    //cv::destroyAllWindows();

    //调用结束
    return 0;
}
*/

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件


LineRotate::LineRotate()
{
}


LineRotate::~LineRotate()
{
    //析构时关闭文件流
    if (logHandle.is_open())
    {
        //std::cout << "file is open" << std::endl;
        logHandle.close();
    }
    //std::cout << "file has closed" << std::endl;
}

int LineRotate::read()
{
    return thresholdValue_struct.yellow_h_min;
}

void LineRotate::init(std::vector<std::vector<int>> params) {
    assert(params.size() == 4 && params[0].size() == 10);
    thresholdValue_struct.blue_h_min = params[0][0];
    thresholdValue_struct.blue_h_max = params[0][1];
    thresholdValue_struct.blue_s_min = params[0][2];
    thresholdValue_struct.blue_s_max = params[0][3];
    thresholdValue_struct.blue_v_min = params[0][4];
    thresholdValue_struct.blue_v_max = params[0][5];
    thresholdValue_struct.blue_cr_min = params[0][6];
    thresholdValue_struct.blue_cr_max = params[0][7];
    thresholdValue_struct.blue_cb_min = params[0][8];
    thresholdValue_struct.blue_cb_max = params[0][9];

    thresholdValue_struct.green_h_min = params[1][0];
    thresholdValue_struct.green_h_max = params[1][1];
    thresholdValue_struct.green_s_min = params[1][2];
    thresholdValue_struct.green_s_max = params[1][3];
    thresholdValue_struct.green_v_min = params[1][4];
    thresholdValue_struct.green_v_max = params[1][5];
    thresholdValue_struct.green_cr_min = params[1][6];
    thresholdValue_struct.green_cr_max = params[1][7];
    thresholdValue_struct.green_cb_min = params[1][8];
    thresholdValue_struct.green_cb_max = params[1][9];

    thresholdValue_struct.yellow_h_min = params[2][0];
    thresholdValue_struct.yellow_h_max = params[2][1];
    thresholdValue_struct.yellow_s_min = params[2][2];
    thresholdValue_struct.yellow_s_max = params[2][3];
    thresholdValue_struct.yellow_v_min = params[2][4];
    thresholdValue_struct.yellow_v_max = params[2][5];
    thresholdValue_struct.yellow_cr_min = params[2][6];
    thresholdValue_struct.yellow_cr_max = params[2][7];
    thresholdValue_struct.yellow_cb_min = params[2][8];
    thresholdValue_struct.yellow_cb_max = params[2][9];

    thresholdValue_struct.brown_h_min = params[3][0];
    thresholdValue_struct.brown_h_max = params[3][1];
    thresholdValue_struct.brown_s_min = params[3][2];
    thresholdValue_struct.brown_s_max = params[3][3];
    thresholdValue_struct.brown_v_min = params[3][4];
    thresholdValue_struct.brown_v_max = params[3][5];
    thresholdValue_struct.brown_cr_min = params[3][6];
    thresholdValue_struct.brown_cr_max = params[3][7];
    thresholdValue_struct.brown_cb_min = params[3][8];
    thresholdValue_struct.brown_cb_max = params[3][9];
}

int LineRotate::getRotate(cv::Mat srcImage)
{
    try {
        getColorMask(srcImage);
        getBlockInfo();
    }
    catch (const int i) {
        throw i;
    }
    catch (const std::exception& e)
    {
        throw -1;
    }
    float areaList[3] = { yellowgreenBlockAreaSum, blueBlockAreaSum,brownBlockAreaSum };
    float positionList[3] = { yellowgreenBlockPosition,blueBlockPosition,brownBlockPosition };
    float temp[3];
    memcpy(temp, areaList, sizeof(temp));
    std::sort(temp, temp + 3);
    if (temp[2] > 2 * (temp[0] + temp[1]))
    {
        throw "发生错误！请使用debug模式";
    }
    else 
    {
        int max_id, second_id;
        for (int i = 0; i < 3; i++)
        {
            if (areaList[i] == temp[2])
            {
                max_id = i;
                break;
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (areaList[i] == temp[1])
            {
                second_id = i;
                break;
            }
        }
        if (positionList[max_id] == NULL || positionList[second_id] == NULL)
        {
            throw 2;
        }
        else {
            //确定正反转
            int direction = (positionList[max_id] > positionList[second_id]) ? 1 : -1;
            float rotate = asin(areaList[second_id] / areaList[max_id] - M_PI / 6) / M_PI * 180 * direction;
            if (max_id == 1)
                rotate += 120;
            else if (max_id == 2)
                rotate -= 120;
            return rotate;
        }
    }
}

//debug模式的重载
int LineRotate::getRotate(cv::Mat srcImage, bool debug, std::string debugFilePath)
{
    originImage = srcImage.clone();
    if (debug)
    {
        setDebugInfoPath(debugFilePath);
        std::string logFilePath = debugFilePath + "/log.txt";
        errorImageFolder = debugFilePath + "image/";
        if (0 != _access(errorImageFolder.c_str(), 0))
        {
            char *fileName = const_cast<char*>(errorImageFolder.c_str()), *tag;
            for (tag = fileName; *tag; tag++)
            {
                if (*tag == '/')
                {
                    char buf[1000], path[1000];
                    strcpy_s(buf, fileName);
                    buf[strlen(fileName) - strlen(tag) + 1] = NULL;
                    strcpy_s(path, buf);
                    if (_access(path, 6) == -1)
                    {
                        _mkdir(path);
                    }
                }
            }
            std::cout << _mkdir(errorImageFolder.c_str()) << std::endl;
        }
        if (!logHandle.is_open())
            logHandle.open(logFilePath.c_str(), std::ios::app);
        time_t tt = time(nullptr);
        struct tm t;
        localtime_s(&t, &tt);
        logHandle << "[ " << std::to_string(t.tm_year + 1900) << "-" << std::to_string(t.tm_mon + 1) << "-" << std::to_string(t.tm_mday) << " " << std::to_string(t.tm_hour) << ":" << std::to_string(t.tm_min) << ":" << std::to_string(t.tm_sec) << " ]" << std::endl;
    }
    try {
        getColorMask(srcImage);
        getBlockInfo();
    }
    catch (const int i) {
        if (debug)
        {
            time_t tt = time(nullptr);
            cv::imwrite(errorImageFolder + "/" + std::to_string(tt) + ".bmp", originImage);
            logHandle << "错误类型: " << std::to_string(i) << "\t 文件已经保存 \t " << errorImageFolder + std::to_string(tt) + ".bmp" << std::endl;
        }
        throw 1;
    }
    catch (const std::exception& e)
    {
        if (debug)
        {
            time_t tt = time(nullptr);
            cv::imwrite(errorImageFolder + "/" + std::to_string(tt) + ".bmp", originImage);
            logHandle << "标准错误，错误类型：-1 \t 文件已经保存 \t " << errorImageFolder + "/" + std::to_string(tt) + ".bmp" << std::endl;
            logHandle << "Standard exception: " << e.what() << std::endl;
        }
        throw -1;
    }
    float areaList[3] = { yellowgreenBlockAreaSum, blueBlockAreaSum,brownBlockAreaSum };
    float positionList[3] = { yellowgreenBlockPosition,blueBlockPosition,brownBlockPosition };
    float temp[3];
    memcpy(temp, areaList, sizeof(temp));
    std::sort(temp, temp + 3);
    if (temp[2] > 2 * (temp[0] + temp[1]))
    {
        if (debug)
        {
            time_t tt = time(nullptr);
            cv::imwrite(errorImageFolder + "/" + std::to_string(tt) + ".bmp", originImage);
            logHandle << "边界处理错误 \t 文件已经保存 \t " << errorImageFolder + std::to_string(tt) + ".bmp" << std::endl;
            logHandle << "错误类型: 2 \t 文件已经保存 \t " << errorImageFolder  + std::to_string(tt) + ".bmp" << std::endl;
        }
        throw 2;
    }
    else
    {
        int max_id, second_id;
        for (int i = 0; i < 3; i++)
        {
            if (areaList[i] == temp[2])
            {
                max_id = i;
                break;
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (areaList[i] == temp[1])
            {
                second_id = i;
                break;
            }
        }
        if (positionList[max_id] == NULL || positionList[second_id] == NULL)
        {
            throw 2;
        }
        else {
            int direction = (positionList[max_id] > positionList[second_id]) ? 1 : -1;
            float rotate = asin(areaList[second_id] / areaList[max_id] - M_PI / 6) / M_PI * 180 * direction;
            if (max_id == 1)
                rotate += 120;
            else if (max_id == 2)
                rotate -= 120;
            return rotate;
        }
    }
}

void LineRotate::getColorMask(cv::Mat & image)
//获取三个颜色区域在RoI区域上的Mask
{
    std::vector<cv::Mat> temp_HSV, temp_YCrCb;
    cv::Mat RoI, tmp;
    try
    {
        getRoIImage(image, RoI);
        cv::imwrite("C:/Users/Administrator/Desktop/test.bmp",image);
        cv::imwrite("C:/Users/Administrator/Desktop/test1.bmp",RoI);
        std::cout << "got ROI Block" << std::endl;
    }
    catch (const std::exception& e)
    {
        if (debug)
        {
            time_t tt = time(nullptr);
            cv::imwrite(errorImageFolder + "/" + std::to_string(tt) + ".bmp", image);
            logHandle << "getRoIImage 函数调用错误 \t 文件已经保存 \t " << errorImageFolder + "/" + std::to_string(tt) + ".bmp" << std::endl;
            logHandle << "Standard exception: " << e.what() << std::endl;
        }
        throw 1;
    }
    catch (const int i)
    {
        std::cout << "error 1" << std::endl;
        throw 1;
    }
    cv::cvtColor(RoI, tmp, cv::COLOR_BGR2HSV);
    cv::split(tmp, temp_HSV);
    cv::cvtColor(RoI, tmp, cv::COLOR_BGR2YCrCb);
    cv::split(tmp, temp_YCrCb);

    
    cv::Mat blueMask1, blueMask2, blueMask3, blueMask4, blueMask;
    cv::Mat greenMask1, greenMask2, greenMask3, greenMask4, greenMask;
    cv::Mat ybMask1, ybMask2, ybMask3, ybMask;
    cv::Mat yellowMask1, yellowMask, brownMask1, brownMask, yellowgreenMask;
    //提取蓝色区域
    cv::threshold(temp_HSV[0], blueMask1, thresholdValue_struct.blue_h_min, 255, cv::THRESH_BINARY);
    cv::threshold(temp_HSV[0], blueMask2, thresholdValue_struct.blue_h_max, 255, cv::THRESH_BINARY_INV);
    cv::threshold(temp_HSV[1], blueMask3, thresholdValue_struct.blue_s_min, 255, cv::THRESH_BINARY);
    cv::threshold(temp_HSV[2], blueMask4, thresholdValue_struct.blue_v_min, 255, cv::THRESH_BINARY);
    cv::bitwise_and(blueMask1, blueMask2, blueMask);
    cv::bitwise_and(blueMask, blueMask3, blueMask);
    cv::bitwise_and(blueMask, blueMask4, blueMask);
    //提取绿色区域
    cv::threshold(temp_HSV[0], greenMask1, thresholdValue_struct.green_h_min, 255, cv::THRESH_BINARY);
    cv::threshold(temp_HSV[0], greenMask2, thresholdValue_struct.green_h_max, 255, cv::THRESH_BINARY_INV);
    cv::threshold(temp_HSV[1], greenMask3, thresholdValue_struct.green_s_min, 255, cv::THRESH_BINARY);
    cv::threshold(temp_HSV[2], greenMask4, thresholdValue_struct.green_v_min,255, cv::THRESH_BINARY);
    cv::bitwise_and(greenMask1, greenMask2, greenMask);
    cv::bitwise_and(greenMask, greenMask3, greenMask);
    cv::bitwise_and(greenMask, greenMask4, greenMask);
    //提取黄棕色区域
    cv::threshold(temp_HSV[0], ybMask1, thresholdValue_struct.yellow_h_min, 255, cv::THRESH_BINARY);
    cv::threshold(temp_HSV[0], ybMask2, thresholdValue_struct.yellow_h_max, 255, cv::THRESH_BINARY_INV);
    cv::threshold(temp_HSV[2], ybMask3, thresholdValue_struct.yellow_v_min, 255, cv::THRESH_BINARY);
    cv::bitwise_or(ybMask1, ybMask2, ybMask);
    cv::bitwise_and(ybMask, ybMask3, ybMask);
    //提取黄色区域
    cv::threshold(temp_YCrCb[2], yellowMask1, thresholdValue_struct.yellow_cb_max, 255, cv::THRESH_BINARY_INV);
    cv::bitwise_and(ybMask, yellowMask1, yellowMask);
    //提取棕色区域
    cv::threshold(temp_YCrCb[2], brownMask1, thresholdValue_struct.brown_cb_min, 255, cv::THRESH_BINARY);
    cv::bitwise_and(ybMask, brownMask1, brownMask);
    //合并黄色和绿色区域
    cv::bitwise_or(yellowMask, greenMask, yellowgreenMask);

    //对对应的Mask进行形态学处理
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(brownMask, brownMask, cv::MORPH_CLOSE, kernel);
    cv::morphologyEx(blueMask, blueMask, cv::MORPH_CLOSE, kernel);
    cv::morphologyEx(yellowgreenMask, yellowgreenMask, cv::MORPH_CLOSE, kernel);

    //寻找最大的连通域
    findBlockMaxContour(yellowgreenMask, YELLOWGREENMASK);
    findBlockMaxContour(brownMask, BROWNMASK);
    findBlockMaxContour(blueMask, BLUEMASK);

}

void LineRotate::getBlockInfo()
{
    cv::Moments temp;
    //计算各个区块的位置的和大小
    //蓝色区域
    if (blueBlockAreaContour.size() > 0)
    {
        temp = cv::moments(blueBlockAreaContour);
        blueBlockPosition = ((temp.m00 == 0) ? NULL : (temp.m01 / temp.m00));
        blueBlockAreaSum = temp.m00;
    }
    //棕色区域
    if (brownBlockAreaContour.size() > 0)
    {
        temp = cv::moments(brownBlockAreaContour);
        brownBlockPosition = ((temp.m00 == 0) ? NULL : (temp.m01 / temp.m00));
        brownBlockAreaSum = temp.m00;
    }
    //黄绿区域
    if (yellowgreenBlockAreaContour.size() > 0)
    {
        temp = cv::moments(yellowgreenBlockAreaContour);
        yellowgreenBlockPosition = ((temp.m00 == 0) ? NULL : (temp.m01 / temp.m00));
        yellowgreenBlockAreaSum = temp.m00;
    }
}

void LineRotate::findBlockMaxContour(cv::Mat maskImage, SELECT block)
//寻找每个区块的最大连通域
{
    std::vector<std::vector<cv::Point>> temp;
    cv::findContours(maskImage, temp, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
    float max_temp = 0.0;
    std::vector<cv::Point> maxContour;
    for (int i = 0; i < temp.size(); i++)
    {
        float area = cv::contourArea(temp[i]);
        if (area > max_temp)
        {
            max_temp = area;
            maxContour = temp[i];
        }
    }
    switch (block)
    {
    case 0:
        yellowgreenBlockAreaContour = maxContour;
        yellowgreenBlockAreaSum = max_temp;
        break;
    case 1:
        brownBlockAreaContour = maxContour;
        brownBlockAreaSum = max_temp;
        break;
    case 2:
        blueBlockAreaContour = maxContour;
        blueBlockAreaSum = max_temp;
        break;
    default:
        break;
    }
}

void LineRotate::getRoIImage(cv::Mat & image, cv::Mat & result)
// 找到线头获取RoI区域
{
    cv::Mat temp;
    std::vector< cv::Mat> splitImage;
    cv::Mat edge2, edge3;
    std::vector<cv::Vec2f> lines2, lines3;
    std::vector<float> alpha;
    float alpha_mean, alpha_std;
    cv::medianBlur(image, temp, 7);
    cv::cvtColor(temp, temp, cv::COLOR_BGR2HSV);
    cv::split(temp, splitImage);

    // hough直线检测
    //cv::Canny(splitImage[1], edge2, 60, 180);
    cv::Canny(splitImage[2], edge3, 60, 120);
    //cv::HoughLines(edge2, lines2, 1, M_PI / 180, 100);
    cv::HoughLines(edge3, lines3, 1, M_PI / 180, 100);
    for (auto line : lines3) 
    {
        alpha.push_back(line[1]);
    }
    // 计算平均直线角度
    alpha_mean = std::accumulate(alpha.begin(), alpha.end(), 0.0) / alpha.size();
    float accum = 0.0;
    std::for_each(std::begin(alpha), std::end(alpha), [&](const float d) 
    {
        accum += (d - alpha_mean)*(d - alpha_mean);
    });
    alpha_std = sqrt(accum / (alpha.size() - 1));
    // 剔除异常数据
    for (auto iter = alpha.begin(); iter != alpha.end(); ++iter) 
    {
        if (*iter > (alpha_mean + 3 * alpha_std) || *iter < (alpha_mean - 3 * alpha_std)) 
        {
            iter = alpha.erase(iter);
            iter--;
        }
    }
    alpha_mean = std::accumulate(alpha.begin(), alpha.end(), 0.0) / alpha.size();

    //旋转矫正
    float rotate = alpha_mean / M_PI * 180 - 90;
    float rotate_r = alpha_mean - M_PI / 2;
    float width_new = temp.rows*abs(sin(rotate_r)) + temp.cols*abs(cos(rotate_r));
    float height_new = temp.cols*abs(sin(rotate_r)) + temp.rows*abs(cos(rotate_r));
    cv::Mat M = cv::getRotationMatrix2D(cv::Point((temp.cols - 1) / 2, (temp.rows - 1) / 2), rotate, 1);
    M.at<double>(0, 2) += (width_new - temp.cols) / 2;
    M.at<double>(1, 2) += (height_new - temp.rows) / 2;

    cv::Mat dst;
    cv::warpAffine(temp, dst, M, cv::Size(int(width_new), int(height_new)));
    cv::warpAffine(edge3, edge3, M, cv::Size(int(width_new), int(height_new)));

    // Sobel竖直边缘提取，归边累加提取线头位置
    // 计算RoI区域的大小
    cv::Mat edge3_sobel_y;
    cv::Sobel(edge3, edge3_sobel_y, CV_16S, 1, 0);
    cv::convertScaleAbs(edge3_sobel_y, edge3_sobel_y);

    cv::Mat edge3_sobel_sum;
    cv::reduce(edge3_sobel_y, edge3_sobel_sum, 0, cv::REDUCE_SUM, CV_32S);
    int x_index[2] = {};
    cv::minMaxIdx(edge3_sobel_sum, nullptr, nullptr, nullptr, x_index);

    if(x_index[0] == x_index[1])
    {
        std::cout << "没有检测到ROI区域" << std::endl;
        throw 1;
    }

    cv::Mat end_RoI, end_RoI_sum;
    if (x_index[1] > 30 && dst.cols - x_index[1] > 30)
    {
        end_RoI = edge3_sobel_y(cv::Range::all(), cv::Range(x_index[1] - 30, x_index[1] + 30));
    }
    else if(x_index[1] <= 30)
    {
        end_RoI = edge3_sobel_y(cv::Range::all(), cv::Range(0, 60));
    }
    else
    {
        end_RoI = edge3_sobel_y(cv::Range::all(), cv::Range(dst.cols - 60, dst.cols-1));
    }
    cv::reduce(end_RoI, end_RoI_sum, 1, cv::REDUCE_SUM, CV_32S);
    int y1, y2;
    for (int i = 0; i < end_RoI_sum.rows; i++)
    {
        if (end_RoI_sum.at<int>(i, 0) > 0)
        {
            y1 = i;
            break;
        }
    }
    for (int i = end_RoI_sum.rows - 1; i >= 0; i--)
    {
        if (end_RoI_sum.at<int>(i, 0) > 0)
        {
            y2 = i;
            break;
        }
    }

    cv::Mat color_RoI;
    if (x_index[1] > 70)
    {
        if(y1 > 30)
        {
            if (y2 + 30 < dst.rows)
            {
                color_RoI = dst(cv::Range(y1 - 30, y2 + 30), cv::Range(x_index[1] - 70, x_index[1] - 40));
            }
            else {
                color_RoI = dst(cv::Range(dst.rows + y1 - 60 - y2, dst.rows - 1), cv::Range(x_index[1] - 70, x_index[1] - 40));
            }
        }
        else if(y1 <=30) 
        {
            color_RoI = dst(cv::Range(0, 60 + y2 - y1), cv::Range(x_index[1] - 70, x_index[1] - 40));
        }
    }
    else if (x_index[1] <= 70)
    {
        if (y1 > 30)
        {
            if (y2 + 30 < dst.rows)
            {
                color_RoI = dst(cv::Range(y1 - 30, y2 + 30), cv::Range(x_index[1] + 40, x_index[1] + 70));
            }
            else {
                color_RoI = dst(cv::Range(dst.rows + y1 - 60 - y2, dst.rows - 1), cv::Range(x_index[1] + 40, x_index[1] + 70));
            }
        }
        else if (y1 <= 30)
        {
            color_RoI = dst(cv::Range(0, 60 + y2 - y1), cv::Range(x_index[1] + 40, x_index[1] + 70));
        }
    }
    //result = color_RoI.clone();
    // 将图像重新转回BGR格式
    cv::cvtColor(color_RoI, result, cv::COLOR_HSV2BGR);
}


