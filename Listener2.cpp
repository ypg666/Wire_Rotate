// Listener1.cpp: implementation of the Listener1 class.
//
//////////////////////////////////////////////////////////////////////


//#include "StdAfx.h"
//#include "stdafx.h"
#include "Listener2.h"
#include "tisudshl.h"
#include <iostream>
#include<QDebug>
#include <opencv2\opencv.hpp>
#include<QStandardPaths>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
using namespace DShowLib;
using namespace std;

Listener2 *Listener2::_instance = 0;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Listener2::Listener2()
{

}

Listener2::~Listener2()
{

}

void Listener2::frameReady(Grabber& caller, smart_ptr<MemBuffer> pBuffer, DWORD currFrame)
{     

//     qDebug() << "111";
     saveImage( pBuffer, currFrame ); // Do the buffer processing.

     ::Sleep(5); // Simulate a time expensive processing.


	//pBuffer是数据指针头
}

void	Listener2::saveImage( smart_ptr<MemBuffer> pBuffer, DWORD currFrame)
{
    sysdate.initFromConfig();
    curnum=sysdate.readcur();
    picnum=sysdate.readpic();

    char filename[MAX_PATH];

    if(curnum <=  picnum)
    {
    curnum++;
    sysdate.setcur(curnum);
    }
    else{curnum=1;sysdate.setcur(curnum);}
    cv::Mat testImage(480, 640 ,CV_8UC4, pBuffer->getPtr());
    cv::flip(testImage, testImage, 0);//垂直反转

//    qDebug() << lineRotate.read();

//    cv::imshow("Test", testImage);
//    cv::imwrite("test/imaging.bmp", testImage);

//    cv::Mat testImage = cv::imread("imaging.bmp");


    int rotate = 0;
//    cout << "start" << endl;
    try {
        //rotate = lineRotate.getRotate(testImage, true, "D:/lineDebug/");

        rotate = lineRotate.getRotate(testImage);
        //lineRotate.clearTempData(); // 这一句可加 可不加 有洁癖的话可以加一下确保每次检测完后回到初始值
    }
    catch (const int errorcode )
    {
        //mei you chuang kou yao yong NULL
        // fei zhu xian cheng bu neng yong QMess
//        QMessageBox::information(this,QString::fromLocal8Bit("错误"),QString::fromLocal8Bit("图像中没有线材"),QMessageBox::Yes);

        emit no_roi();
        return;

        //        std::cout << "ERROR CODE: "<< errorcode << std::endl;
    }
    lineRotate.clearTempData();
//    cout << "end" << endl;
    std::cout << rotate << std::endl;

    QString qfilename = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    sprintf( filename, "/Camara2/%i_%i.bmp", rotate,curnum );
    // /history
    // he bing zi fu chuan
    //zhuan huan ge shi
    qfilename = qfilename.append(filename);
    char*  ch;
    QByteArray ba = qfilename.toLatin1(); // must
    ch = ba.data();

    //qDebug() << ch ;
    cv::imwrite(ch, testImage);
    emit finish(rotate);
}

//void Listener1::SetViewWnd(CWnd*wnd)
//{
//   viewWnd=wnd;
//}
