/*********************************************************************************
  *Copyright(C)
  *ClassName:  stateWidget
  *Author:  佳豪
  *Version: 1.0
  *Date:  2019.7.12
  *Description: 调试窗口状态指示灯的Widget
  *             直接在.ui里创建Widget提升实现
  *             在这里可以设置初始颜色
  *Others:  //其他内容说明
  *Function List:  QColor m_color =  //设置指示灯开启的颜色
  *                turnOn() //指示灯开启
  *                随后指示灯对象调用update()更新状态
  *History:
  *
**********************************************************************************/
#pragma once

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QLabel>
#include <string>
#include <iostream>

// 支持中文
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif


class stateWidget : public QWidget
{
    Q_OBJECT
        Q_PROPERTY(bool on READ isOn WRITE setOn)
    // Q_PROPERTY()是一个宏，用来在一个类中声明一个属性property，由于该宏是qt特有的，需要用moc进行编译，故必须继承于QObject类

public:
    explicit stateWidget(QWidget *parent = 0);

    bool isOn() const;
    void setOn(bool on);

    QColor m_color = Qt::blue;

	QString lightTextStr = QString::fromUtf8("");

signals:


public slots:
    void turnOff();
    void turnOn();

protected:
    void paintEvent(QPaintEvent *) override;

private:
    bool m_on;
    bool addTextFlag = false;
	
	
};
