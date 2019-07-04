#pragma once
#include <QDebug>
#include <QSerialPort>
#include <QtSerialPort\qserialport.h>
#include <QtSerialPort\qserialportinfo.h>
#include <QString>
#include <string>
#include "CRC16.h"
#include <iostream>

/**
* @brief        以ASCII的编码与PLC进行通讯
*               类设计原理：
*               1.类的构造函数分为easyModbus2(int) 功能是指定写入寄存器
*               2.int initSerialPort() -- 自动检测并初始化串口并返回初始化串口的状态
*               3.sengMsg 发送消息至串口
*               4.readMsg 读取串口
* @author        George
* @date          2019-07-04
*/

class easyModbus2
{
public:
    easyModbus2() = default;
    easyModbus2(int numberOfRegister);
    ~easyModbus2();

    int initSerialPort();
	void sendMsg(QString  input);           //发送数据
    void sendMsg(int intInput);             //发送整形角度数据
    QByteArray readMsg();                   //接收数据

private:

	QSerialPort serialPort;      //串口类
	QString serialPortName;      //打开的串口

    // ==== The setting of modbus ===== //
    //// == register == ////
    int numberOfRegister = 4888;

    //// == Matching message == ////
    QString matchMessageAA = "3A30313036313331384646303043460D0A"; // int 0
    QString matchMessageAB = "3a30313036313331384646303043460d0a";

};

