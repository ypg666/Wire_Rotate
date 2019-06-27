// TIS_Camera.cpp: implementation of the TIS_Camera class.
//
//////////////////////////////////////////////////////////////////////

#include "TIS_Camera.h"
#include "Listener1.h"
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include "tisudshl.h"
#include <QtCore/QCoreApplication>
#include <QtGui>
#include <QWidget>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

using namespace std;
using namespace cv;
using namespace DShowLib;

TIS_Camera *TIS_Camera::_instance = 0;

TIS_Camera::TIS_Camera()
{

}

TIS_Camera::~TIS_Camera()
{

}

void TIS_Camera::Camera(QWidget *win)
{
    if (Grab1.isLive())
    {
        Grab1.stopLive();
    }
//    Grab1 = new DShowLib::Grabber;
        if (!Grab1.loadDeviceStateFromFile("device.xml",true))
        {
            Grab1.showDevicePage(); //
            Grab1.saveDeviceStateToFile("device.xml");
        }
//    if (!Grab1.openDev(0x07914124))  //
//    {

//    }
    atexit(DShowLib::ExitLibrary); //
//    Grab1->showDevicePage();//bool
//    Grab1.removeListener(pListener1);
    Grab1.removeListener(Listener1::Instance());
    if (Grab1.isDevValid())//
    {
        if( Grab1.getExternalTrigger() )
        {
            Grab1.setExternalTrigger(false);
        }
//        pListener1 = new Listener1;
//        Grab1.addListener(pListener1,DShowLib::GrabberListener::eFRAMEREADY);//
        pSink = FrameHandlerSink::create( eRGB32,3);//黑白相机用eY800，彩色用eRGB32格式
       // pSink = FrameHandlerSink::create( eY800,3);
        // Disable snap mode.
        pSink->setSnapMode(false);
        // Set the sink.
        Grab1.setSinkType(pSink);

        //
        HWND appwnd;
        appwnd = (HWND)win->winId();
        // Set the window that should display the live video.
        Grab1.setHWND(appwnd);//

        //Enables or disables the default window size lock of the video window.
        Grab1.setDefaultWindowPosition(false);
        //Sets the size of the video window.
//        pGrabber->setWindowSize(ui->widget->width(),ui->widget->height());
//         pGrabber->setWindowSize(1280,960);
        Grab1.setWindowSize(800,600);
        // Start the live video.
//        long Width = Grab1.getAcqSizeMaxX();
//        long Height = Grab1.getAcqSizeMaxY();  //获取图像大小
//        Mat mat(Height, Width, CV_8U, pSink->getLastAcqMemBuffer()->getPtr());
        Grab1.startLive();
    }
}
void TIS_Camera::Trigger(QWidget *win)
{
    if (Grab1.isLive())
    {
        Grab1.stopLive();
    }
    if (!Grab1.loadDeviceStateFromFile("device.xml",true))
    {
        Grab1.showDevicePage(); //
        Grab1.saveDeviceStateToFile("device.xml");
    }
//    Grab1 = new DShowLib::Grabber;
//    if (!Grab1.openDev(0x07914124))  //
//    {

//    }
    atexit(DShowLib::ExitLibrary); //
//    Grab1->showDevicePage();//bool
    if (Grab1.isDevValid())//
    {
       // pListener1 = new Listener1;
        Grab1.addListener(Listener1::Instance(),DShowLib::GrabberListener::eFRAMEREADY);//
        pSink = FrameHandlerSink::create( eRGB32,3);//黑白相机用eY800，彩色用eRGB32格式
        // Disable snap mode.
        pSink->setSnapMode(false);
        // Set the sink.
        Grab1.setSinkType(pSink);

        if( Grab1.getExternalTrigger() )
        {
//            Grab1.setExternalTrigger(false);
        }
        else
        {
            Grab1.setExternalTrigger( true );
        }

        HWND appwnd;
        appwnd = (HWND)win->winId();
        // Set the window that should display the live video.
        Grab1.setHWND(appwnd);
        /*setWindowSize()*/
        //Enables or disables the default window size lock of the video window.
        Grab1.setDefaultWindowPosition(false);
        //Sets the size of the video window.
//        pGrabber->setWindowSize(ui->widget->width(),ui->widget->height());
//         pGrabber->setWindowSize(1280,960);
        Grab1.setWindowSize(800,600);
        // Start the live video.
        Grab1.startLive();
    }
}
//相机初始化
void TIS_Camera::CameraInit()
{
    if( !DShowLib::InitLibrary( "" ) )
    {
//		TRACE("The library could not be initialized. Invalid license key?");

    }

//    Grab1 = new DShowLib::Grabber;

    //从文件打开相机

//	if (!Grab1->loadDeviceStateFromFile("device.xml",true))
//	{
//		Grab1->showDevicePage(); //显示相机设备
//		Grab1->saveDeviceStateToFile("device.xml");
//	}

    //使用序号打开相机
// 	if (!Grab1->openDev(0x46614490))  //相机外壳序列号加上0x（即零x）
// 	{
// 		AfxMessageBox("打开相机失败,是否已连接好相机或相机SN号有误");
//
// 	}
//    if (Grab1.isLive())
//    {
//        Grab1.stopLive();
//    }
    Grab1.showDevicePage();                                             //显示相机设备
    Grab1.saveDeviceStateToFile("device.xml");
    Grab1.loadDeviceStateFromFile("device.xml",true);
//    Grab1.startLive();
    emit ini();
    //    //设置回调函数
//    pListener1 = new Listener1();
//    Grab1->addListener(pListener1,DShowLib::GrabberListener::eFRAMEREADY);//注册回调
//    pSink = FrameHandlerSink::create( eY800,3);//黑白用eY800；彩色用eRGB32格式

//    // Disable snap mode.
//    pSink->setSnapMode(false);
//    // Set the sink.
//    Grab1->setSinkType(pSink);


}
/*
void TIS_Camera::CameraShowImage()//实时显示图片
{
    pSink->setSnapMode(true);
    while (1)
    {
        pSink->snapImages(1);	// Grab NUM_BUFFERS images.
        Sleep(10);
    }

}
*/
bool TIS_Camera::Valid()
{
    if (Grab1.isDevValid())
    {
        return true;
    }
    else return false;
}
//获取图片
Mat TIS_Camera::GetMatImage()
{
    if (Grab1.isDevValid())
    {
    pSink->setSnapMode(true);
    // Apply the sink to the grabber.
    Grab1.setSinkType(pSink);
   // Grab1.startLive();				// Start the grabber.
    pSink->snapImages(1);
   // Grab1.stopLive();					// Stop the grabber.

    //获取图像格式
    int nChannels = 1;
    long Width = Grab1.getAcqSizeMaxX();
    long Height = Grab1.getAcqSizeMaxY();  //获取图像大小
    int depth = pSink->getLastAcqMemBuffer()->getBitsPerPixel();//获取图像深度
    Mat mat(Height, Width, CV_8UC4, pSink->getLastAcqMemBuffer()->getPtr());
    // CV_8U
    return mat;
    }
    /*
    //通过数据指针保存图片
    Mat mat(Height, Width, CV_8U, pSink->getLastAcqMemBuffer()->getPtr());
    imshow("Test", mat);
    imwrite("image.bmp", mat);
    cvWaitKey(0);
    */
//	IplImage* img_src = cvCreateImage(cvSize(Width, Height), depth, nChannels);
//	memcpy(img_src->imageData, pSink->getLastAcqMemBuffer()->getPtr(), Width*Height);
//	cvSaveImage("image.bmp", img_src);
//	namedWindow("Test", WINDOW_AUTOSIZE);
//	cvShowImage("Test", img_src);
//	cvWaitKey(0);
}
/*
//退出后关闭相机
void TIS_Camera::CameraClose()
{
    if (Grab1->isLive())
    {
        Grab1->stopLive();
    }
    if (Grab1->isListenerRegistered(pListener1))
    {
        Grab1->removeListener(pListener1, DShowLib::GrabberListener::eFRAMEREADY);

    }

    if (Grab1->isDevOpen())
    {
        Grab1->closeDev();
    }

    delete pListener1;

    delete Grab1;
}
//开始取图
void TIS_Camera::CameraStart()
{
//	Grab1->startLive(true);
    Grab1->startLive(false);
}

//停止取图
void TIS_Camera::CameraStop()
{
    Grab1->stopLive();
}

//相机属性
void TIS_Camera::Camerapropery()
{
    Grab1->showVCDPropertyPage();
}

//相机Binning
void TIS_Camera::CamBin(int Bvalue)
{
    switch(Bvalue)
    {
    case 1:
        Grab1->stopLive();
        Grab1->setVideoFormat("Y800 (2592x1944) [Binning 1x]");
        Grab1->startLive(false);
        break;
    case 2:
        Grab1->stopLive();
        Grab1->setVideoFormat("Y800 (1296x972) [Binning 2x]");
        Grab1->startLive(false);
        break;
    case 4:
        Grab1->stopLive();
        Grab1->setVideoFormat("Y800 (640x484) [Binning 4x]");
        Grab1->startLive(false);
        break;
    }

}


*/
QImage TIS_Camera::cvMat2QImage(const cv::Mat& mat, bool clone, bool rb_swap)
{
    const uchar *pSrc = (const uchar*)mat.data;
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if (mat.type() == CV_8UC1)
    {
        //QImage image(mat.cols, mat.rows, QImage::Format_Grayscale8);
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
        if (clone) return image.copy();
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if (mat.type() == CV_8UC3)
    {
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        if (clone)
        {
            if (rb_swap) return image.rgbSwapped();
            return image.copy();
        }
        else
        {
            if (rb_swap)
            {
                cv::cvtColor(mat, mat, CV_BGR2RGB);
            }
            return image;
        }

    }
    else if (mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        if (clone) return image.copy();
        return image;
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

