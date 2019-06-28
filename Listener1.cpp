// Listener1.cpp: implementation of the Listener1 class.
//
//////////////////////////////////////////////////////////////////////


//#include "StdAfx.h"
//#include "stdafx.h"
#include "Listener1.h"
#include "tisudshl.h"
#include<QDebug>
#include <opencv2\opencv.hpp>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
using namespace DShowLib;

Listener1 *Listener1::_instance = 0;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Listener1::Listener1()
{

}

Listener1::~Listener1()
{

}

void Listener1::frameReady(Grabber& caller, smart_ptr<MemBuffer> pBuffer, DWORD currFrame)
{     

     qDebug() << "111";
     saveImage( pBuffer, currFrame ); // Do the buffer processing.

     ::Sleep(5); // Simulate a time expensive processing.


	//pBuffer是数据指针头
/*	    

        CRect rect;
		viewWnd->GetWindowRect(&rect);
        CDC *dc=viewWnd->GetDC();
		smart_ptr<BITMAPINFOHEADER> pInf = pBuffer->getBitmapInfoHeader();
		SetStretchBltMode(dc->m_hDC , COLORONCOLOR);
 			int nLines = StretchDIBits( 
				dc->GetSafeHdc(),			// handle to the device context of the window
 				0,
				0,
 				rect.Width(),
				rect.Height(),
 				0,						// x-coordinate of lower-left corner of the source rect
 				0,						// y-coordinate of lower-left corner of the source rect
 				abs(pInf->biWidth),
 				abs(pInf->biHeight),
 				pBuffer->getPtr(),	// modified address of array with DIB bits
 				reinterpret_cast<LPBITMAPINFO>( &*pInf ),	// address of structure with bitmap info
 				DIB_RGB_COLORS,				// RGB or palette indices
 				SRCCOPY
 				);

 		ReleaseDC(viewWnd->m_hWnd,dc->GetSafeHdc());
 	
*/

}

void	Listener1::saveImage( smart_ptr<MemBuffer> pBuffer, DWORD currFrame)
{
    sysdate.initFromConfig();
    curnum=sysdate.readcur();
    picnum=sysdate.readpic();

    char filename[MAX_PATH];

//    sprintf( filename, "history/image%02i.bmp", curnum );

    //saveToFileBMP( *pBuffer, filename );

    if(curnum <=  picnum)
    {
    curnum++;
    sysdate.setcur(curnum);
    }
    else{curnum=1;sysdate.setcur(curnum);}
    cv::Mat testImage(480, 640 ,CV_8UC4, pBuffer->getPtr());
    cv::flip(testImage, testImage, 0);//垂直反转

//    cv::imshow("Test", testImage);
//    cv::imwrite("test/imaging.bmp", testImage);

//    cv::Mat testImage = cv::imread(filename);

    int rotate = 0;
//    try {
//        //rotate = lineRotate.getRotate(testImage, true, "D:/lineDebug/");
//        rotate = lineRotate.getRotate(testImage);
//        lineRotate.clearTempData(); // 这一句可加 可不加 有洁癖的话可以加一下确保每次检测完后回到初始值
//    }
//    catch (const int errorcode)
//    {
//        std::cout << "ERROR CODE: "<< errorcode << std::endl;
//    }
//    std::cout << rotate << std::endl;

//    sprintf( filename, "history/%04i-%04i.bmp", rotate,curnum );
    sprintf( filename, "history/%i-%i.bmp", rotate,curnum );
    cv::imwrite(filename, testImage);
    emit finish(rotate);
}

//void Listener1::SetViewWnd(CWnd*wnd)
//{
//   viewWnd=wnd;
//}
