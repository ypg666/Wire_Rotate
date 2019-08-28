/*********************************************************************************
  *Copyright(C)
  *ClassName:  TIS_Camera
  *Author:  璞光
  *Version: 1.0
  *Date:  2019.7.12
  *Description: 映美精相机类,用于操作相机
                采用单例模式，可以不用实例化对象，保证了只有一个相机对象，不同窗口操作同一个相机。
  *Others:  //其他内容说明
  *Function List:  Camera(QWidget *win) //相机直接显示实时图像 需传入显示Widget的句柄
  *                Trigger(QWidget *win) //硬触发模式
  *                CameraInit() //相机初始化，用于相机设置参数后更新相机
  *                bool Valid() //判断相机状态，打开为true
  *                Mat GetMatImage();//抓图
  *History:  //修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介
**********************************************************************************/

// TIS_Camera.h: interface for the TIS_Camera class.
//
//////////////////////////////////////////////////////////////////////
#include "tisudshl.h"
#include "Listener2.h"//回调头文件
#include<opencv2\opencv.hpp>
#include <QtGui>
#include <QObject>

//加上会不编译后面的
//#if !defined(AFX_TIS_CAMERA_H__9AE25ADE_A9E6_4DFD_A8E0_6181580BA1D4__INCLUDED_)
//#define AFX_TIS_CAMERA_H__9AE25ADE_A9E6_4DFD_A8E0_6181580BA1D4__INCLUDED_

//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000



using namespace cv;
using namespace DShowLib;

class TIS_Camera2 : public QObject
{
    Q_OBJECT

public:
    TIS_Camera2();
     ~TIS_Camera2();

    //实现单例模式，即使不创建对象仍能够使用 保证了不同类之间使用了同一个对象，便利于信号与槽的传递，与主界面逻辑的沟通
    static TIS_Camera2 *Instance(){
        if (!_instance) {
            _instance = new TIS_Camera2;
        }
        return _instance;
    }

     Listener2 *pListener1; //回调对象
	
	 //生成相机取图与接口对象
//     DShowLib::Grabber *Grab1;
     DShowLib::Grabber Grab1;
	 tFrameHandlerSinkPtr pSink;
	 tIVCDPropertyInterfacePtr	 pItf;	
	 tIVCDPropertyItemsPtr		 pProps;
	 Grabber::tVidFmtListPtr  pVidCapDevList;
	 
    void Camera(QWidget *win); // xiangji zhijie xianshi
    void Trigger(QWidget *win); //wai bu chufa
    void CameraInit();//相机初始化
//	void CameraShowImage();//实时显示图片
//	void CamBin(int Bvalue);//Binning；
    bool Valid(); //detect  camera statute
    Mat GetMatImage();//获取图片图片
//	void CameraClose();//关闭相机
//	void CameraStart();//开始取图
//	void CameraStop();//停止取图
//	void Camerapropery();//相机属性

    QImage cvMat2QImage(const cv::Mat& mat, bool clone = true, bool rb_swap = true);
	/**
	* @brief 将 OpenCV 的 cv::Mat 类型图像转换为 QImage 类型
	* @param mat 待转换的图像，支持 CV_8UC1、CV_8UC3、CV_8UC4 三种OpenCV 的数据类型
	* @param clone true 表示与 Mat 不共享内存，更改生成的 mat 不会影响原始图像，false 则会与 mat 共享内存
	* @param rb_swap 只针对 CV_8UC3 格式，如果 true 则会调换 R 与 B RGB->BGR，如果共享内存的话原始图像也会发生变化
	* @return 转换后的 QImage 图像
	*/

signals:
     void ini();
private:

     static TIS_Camera2 *_instance;       //实例对象
    Mat m_getmat;
    QImage m_qimg;


};

//#endif // !defined(AFX_TIS_CAMERA_H__9AE25ADE_A9E6_4DFD_A8E0_6181580BA1D4__INCLUDED_)
