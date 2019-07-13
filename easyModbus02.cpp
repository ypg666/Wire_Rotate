#include "easyModbus02.h"

easyModbus2::easyModbus2(int numberOfRegister)
{
    // use the user-defined register
    this->numberOfRegister = numberOfRegister;
}

easyModbus2::~easyModbus2()
{
    serialPort.clear();
    serialPort.close();
}

int easyModbus2::initSerialPort2()
{
    this->hasMatchPort = false;
    QStringList mPortNameList;  //串口列表
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    if (!portList.empty()) {
        foreach(const QSerialPortInfo &info, portList)
        {
            // qDebug() << "SerialPortList:";
            mPortNameList.push_back(info.portName());
            // qDebug() << "    SerialPortName:" << info.portName();
        }

        for(auto sPortName:mPortNameList){
            this->serialPortName = sPortName;
            serialPort.setPortName(serialPortName);
            serialPort.setBaudRate(QSerialPort::Baud9600);           //设置波特率和读写方向
            serialPort.setDataBits(QSerialPort::Data7);              //数据位为8位
            serialPort.setFlowControl(QSerialPort::NoFlowControl);   //无流控制
            serialPort.setParity(QSerialPort::EvenParity);           //无校验位
            serialPort.setStopBits(QSerialPort::OneStop);            //一位停止位
            if (serialPort.isOpen())                                 //如果串口已经打开了 先给他关闭了
            {
                serialPort.clear();
                serialPort.close();
            }

            if (!serialPort.open(QIODevice::ReadWrite))              //用ReadWrite 的模式尝试打开串口
            {
                continue;
            }
            else
            {
                // ===== Matching Serial Port ======= //
                sendMsg(this->matchMessageAA);
                QByteArray receiveByte = readMsg();
                QString receivedMsg = receiveByte.toHex();
                if (receivedMsg == this->matchMessageAB)
                {
                    this->hasMatchPort = true;
                    // qDebug() << QObject::tr("Successful Opening of Serial Port: %1").arg(this->serialPortName) << endl;
                    return 1;
                }
            }
        }
    }
    else
    {
        return -1;
    }
    return -1;
}

int easyModbus2::initSerialPort()
{
    this->hasMatchPort = false;
    QStringList mPortNameList;  //串口列表
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    if (!portList.empty()) {
        foreach(const QSerialPortInfo &info, portList)
        {
            // qDebug() << "SerialPortList:";
            mPortNameList.push_back(info.portName());
            // qDebug() << "    SerialPortName:" << info.portName();
        }

        for(auto sPortName:mPortNameList){
            this->serialPortName = sPortName;
            serialPort.setPortName(serialPortName);
            serialPort.setBaudRate(QSerialPort::Baud9600);           //设置波特率和读写方向
            serialPort.setDataBits(QSerialPort::Data7);              //数据位为8位
            serialPort.setFlowControl(QSerialPort::NoFlowControl);   //无流控制
            serialPort.setParity(QSerialPort::EvenParity);           //无校验位
            serialPort.setStopBits(QSerialPort::OneStop);            //一位停止位
            if (serialPort.isOpen())                                 //如果串口已经打开了 先给他关闭了
            {
                serialPort.clear();
                serialPort.close();
            }

            if (!serialPort.open(QIODevice::ReadWrite))              //用ReadWrite 的模式尝试打开串口
            {
                continue;
            }
            else
            {
                // ===== Matching Serial Port ======= //
                sendMsg(this->matchMessageAA2);
                QByteArray receiveByte = readMsg();
                QString receivedMsg = receiveByte.toHex();
                if (receivedMsg.size() == 30)
                {
                    this->hasMatchPort = true;
                    // qDebug() << QObject::tr("Successful Opening of Serial Port: %1").arg(this->serialPortName) << endl;
                    return 1;
                }
            }
        }
    }
    else
    {
        return -1;
    }
    return -1;
}


void easyModbus2::sendMsg(QString input)
{

    QString str = input;
    // === 发送数据 === //
    QByteArray writeData = QByteArray::fromHex(str.toLatin1().data());

    serialPort.clear();
    qint64 bytesWritten = serialPort.write(writeData);

    if(bytesWritten == -1 || bytesWritten != writeData.size() || !serialPort.waitForBytesWritten(300)){
        throw 100;
    }

//    if (bytesWritten == -1)
//    {
//        qDebug() << QObject::tr("Failed to write the data to port %1 , error:%2").arg(serialPortName).arg(serialPort.errorString()) << endl;
//    }
//    else if (bytesWritten != writeData.size())
//    {
//        qDebug() << QObject::tr("Failed to write all the data to port %1 , error:%2").arg(serialPortName).arg(serialPort.errorString()) << endl;
//    }
//    else if (!serialPort.waitForBytesWritten(5000))
//    {
//        qDebug() << QObject::tr("Operation timed out or an error occurred for port %1 , error:%2").arg(serialPortName).arg(serialPort.errorString()) << endl;
//    }
//    else{
//        //////////////////////显示发送的数据/////////////////////////////////////////////////
//        qDebug() << QObject::tr("Data successfully sent to port %1").arg(serialPortName) << endl;
//        //////////////////////显示接收的数据/////////////////////////////////////////////////
//    }

}

void easyModbus2::sendMsg(int intInput)
{

    if(!this->hasMatchPort){
        throw 100;
    }

    QString input = QString::fromStdString(LRC::convertIntToModbusString(intInput, this->numberOfRegister));
    sendMsg(input);

    // === test receive === //
    // ==== 一定要读一下才能保证写入，具体原因不详
    if(true){
        QByteArray receiveByte = readMsg();
//        for(int i = 0; i < receiveByte.size();i++){
//            std::cout << (receiveByte[i]);
//        }
    }

}

QByteArray easyModbus2::readMsg()
{
	QByteArray readData = serialPort.readAll();
    while (serialPort.waitForReadyRead(200)){
        readData.append(serialPort.readAll());
    }

//	if (serialPort.error() == QSerialPort::ReadError)
//	{
//		qDebug() << QObject::tr("Failed to read from port %1 ,error: %2 ").arg(serialPortName).arg(serialPort.errorString()) << endl;
//	}
//	else if (serialPort.error() == QSerialPort::TimeoutError && readData.isEmpty())
//	{
//		qDebug() << QObject::tr("No data was currently available for reading from port %1").arg(serialPortName) << endl;
//	}
//    else{
//        qDebug() << QObject::tr("Data successfully received from port %1").arg(serialPortName) << endl;
//    }
//    if(!readData.isEmpty()){
//        qDebug() << readData.toHex() << endl;
//        //	QString backdata = readData.toHex();
//        //  qDebug() << readData.toHex();
//    }
	return readData;
}
