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
