// TIS_Camera.h: interface for the TIS_Camera class.
//
//////////////////////////////////////////////////////////////////////
#include "tisudshl.h"
#include "Listener1.h"//回调头文件
#include<opencv2\opencv.hpp>
#include <QtGui>


#if !defined(AFX_TIS_CAMERA_H__9AE25ADE_A9E6_4DFD_A8E0_6181580BA1D4__INCLUDED_)
#define AFX_TIS_CAMERA_H__9AE25ADE_A9E6_4DFD_A8E0_6181580BA1D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



using namespace cv;
using namespace DShowLib;

class TIS_Camera  
{
public:
	TIS_Camera();
	 ~TIS_Camera();

	 
	 Listener1 *pListener1; //回调对象
	
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
//    QImage GetMatImage();//获取图片图片
//	void CameraClose();//关闭相机
//	void CameraStart();//开始取图
//	void CameraStop();//停止取图
//	void Camerapropery();//相机属性

//    QImage cvMat2QImage(const cv::Mat& mat, bool clone = true, bool rb_swap = true);
	/**
	* @brief 将 OpenCV 的 cv::Mat 类型图像转换为 QImage 类型
	* @param mat 待转换的图像，支持 CV_8UC1、CV_8UC3、CV_8UC4 三种OpenCV 的数据类型
	* @param clone true 表示与 Mat 不共享内存，更改生成的 mat 不会影响原始图像，false 则会与 mat 共享内存
	* @param rb_swap 只针对 CV_8UC3 格式，如果 true 则会调换 R 与 B RGB->BGR，如果共享内存的话原始图像也会发生变化
	* @return 转换后的 QImage 图像
	*/

private:

    Mat m_getmat;
    QImage m_qimg;


};

#endif // !defined(AFX_TIS_CAMERA_H__9AE25ADE_A9E6_4DFD_A8E0_6181580BA1D4__INCLUDED_)
