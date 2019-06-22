// Listener1.h: interface for the Listener1 class.
//
//////////////////////////////////////////////////////////////////////
#include "tisudshl.h"
#include "LineRotate.h"
#include "sysdate.h"

#if !defined(AFX_LISTENER1_H__9BF7AEC9_0888_4A16_88DD_2EA7C7D59C97__INCLUDED_)
#define AFX_LISTENER1_H__9BF7AEC9_0888_4A16_88DD_2EA7C7D59C97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Listener1 : public DShowLib::GrabberListener   
{
public:
	Listener1();
	virtual ~Listener1();
    LineRotate lineRotate;
    SysDate sysdate;
    int curnum;int picnum;
public:
	virtual void frameReady(DShowLib::Grabber& caller, smart_ptr<DShowLib::MemBuffer> pBuffer, DWORD FrameNumber);
    void		saveImage( smart_ptr<DShowLib::MemBuffer> pBuffer, DWORD currFrame );
	//这两行代码通过设置句柄可以实现在窗口显示
//    void SetViewWnd(CWnd *wnd);
//	  CWnd *viewWnd;
};

#endif // !defined(AFX_LISTENER1_H__9BF7AEC9_0888_4A16_88DD_2EA7C7D59C97__INCLUDED_)
