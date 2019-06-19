// Listener1.cpp: implementation of the Listener1 class.
//
//////////////////////////////////////////////////////////////////////


//#include "StdAfx.h"
//#include "stdafx.h"
#include "Listener1.h"
#include "tisudshl.h"
#include<QDebug>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
using namespace DShowLib;

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
    char filename[MAX_PATH];
////	if( currFrame < m_BufferWritten.size() )

        sprintf( filename, "image%02i.bmp", currFrame );

        saveToFileBMP( *pBuffer, filename );

}

//void Listener1::SetViewWnd(CWnd*wnd)
//{
//   viewWnd=wnd;
//}
