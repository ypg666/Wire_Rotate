/*******************************************************************************
* 类 名         : Listener1
* 类功能		   : 相机回调，用来实现触发取图和处理
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
// Listener1.h: interface for the Listener1 class.
//
//////////////////////////////////////////////////////////////////////
#include "tisudshl.h"
#include "LineRotate.h"
#include "sysdate.h"
#include <QObject>
#include <QWidget>
#include <QMessageBox>

#if !defined(AFX_LISTENER1_H__9BF7AEC9_0888_4A16_88DD_2EA7C7D59C97__INCLUDED_)
#define AFX_LISTENER1_H__9BF7AEC9_0888_4A16_88DD_2EA7C7D59C97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// QWidget instead QObject
class Listener1 :  public QObject,public DShowLib::GrabberListener
{
       Q_OBJECT
public:
	Listener1();
    ~Listener1();
    //virtual ~Listener1();

    //实现单例模式，即使不创建对象仍能够使用 保证了不同类之间使用了同一个对象，便利于信号与槽的传递，与主界面逻辑的沟通
    static Listener1 *Instance(){
        if (!_instance) {
            _instance = new Listener1;
        }
        return _instance;
    }

    LineRotate lineRotate;
    SysDate sysdate;
    int curnum;int picnum;
public:
	virtual void frameReady(DShowLib::Grabber& caller, smart_ptr<DShowLib::MemBuffer> pBuffer, DWORD FrameNumber);
    void		saveImage( smart_ptr<DShowLib::MemBuffer> pBuffer, DWORD currFrame );
	//这两行代码通过设置句柄可以实现在窗口显示
//    void SetViewWnd(CWnd *wnd);
//	  CWnd *viewWnd;
signals:
    void finish(int);
    void no_roi();
private:
    static Listener1 *_instance;       //实例对象

//    //算法初始参数
//    std::vector<std::vector<int>> params;
//    //基地最优参数
//    std::vector<int> blueThreshold{ 100, 120, 30, 255, 25, 255, 0, 255, 0, 255 };
//    std::vector<int> greenThreshold{ 45, 100, 70, 255, 50, 255, 0, 255, 0, 255 };
//    std::vector<int> yellowThreshold{ 120, 40, 0, 255, 50, 255, 0, 255, 0, 100 };
//    std::vector<int> brownThreshold{ 120, 40, 0, 255, 40, 255, 0, 255, 101, 255 };
};


#endif // !defined(AFX_LISTENER1_H__9BF7AEC9_0888_4A16_88DD_2EA7C7D59C97__INCLUDED_)
