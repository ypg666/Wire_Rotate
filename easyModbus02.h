#pragma once
#include <QDebug>
#include <QSerialPort>
#include <QtSerialPort\qserialport.h>
#include <QtSerialPort\qserialportinfo.h>
#include <QString>
#include <string>
#include "CRC16.h"

//modbus class, which is very different to easyModbus01.h
class easyModbus2
{
public:
    easyModbus2();
    easyModbus2(int a);
    easyModbus2(QString selfDefinedPortName);
    ~easyModbus2();

	void sendMsg(QString  input);           //发送数据
	void sendMsg(int intInput);            //发送整形数据
    QByteArray readMsg();                   //接收数据

private:

	QSerialPort serialPort;      //串口类
	QString serialPortName;      //打开的串口
    QString received_Msg;        //接收到的数据
    QByteArray receive_byte;     //接收到的数据

    QString matchMessageA = "01 06 01 98 00 08 08 1F";
    QString matchMessageB = "01 06 01 98 00 08 08 1F";

    QString matchMessageAA = "3a30313035303530304646303046360D0A";

    QString matchMessageAB = "3a30313035303530304646303046360d0a";


    bool rtuOrAscii = true;
};

