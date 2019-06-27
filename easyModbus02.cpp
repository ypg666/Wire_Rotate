#include "easyModbus02.h"

easyModbus2::easyModbus2()
{
    //initialize the first serial port
    // choose the first serialPort
    QStringList mPortNameList;  //串口列表

    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    if (!portList.empty()) {
        foreach(const QSerialPortInfo &info, portList)
        {
            mPortNameList.push_back(info.portName());
            qDebug() << "SerialPortName:" << info.portName();
        }
    }
    else
    {
        qDebug() << "No Available Serial Port" << endl;
    }

    int matchingFlag = false;

    for(auto sPortName:mPortNameList){
        this->serialPortName = sPortName;
        serialPort.setPortName(serialPortName);
        serialPort.setBaudRate(QSerialPort::Baud9600);//设置波特率和读写方向
        serialPort.setDataBits(QSerialPort::Data8);      //数据位为8位
        serialPort.setFlowControl(QSerialPort::NoFlowControl);//无流控制
        serialPort.setParity(QSerialPort::NoParity); //无校验位
        serialPort.setStopBits(QSerialPort::OneStop);  //一位停止位
        if (serialPort.isOpen())//如果串口已经打开了 先给他关闭了
        {
            // serialPort.clear();
            serialPort.close();
        }

        if (!serialPort.open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
        {
            qDebug() << QObject::tr("Failed to open serial port: %1").arg(serialPortName) << endl;

        }
        else
        {
            // Matching Serial Port
            sendMsg(matchMessageA);
            QByteArray receiveByte = readMsg();
            QString receivedMsg = receiveByte.toHex();
            if (receivedMsg == matchMessageB)
            {
                qDebug() << QObject::tr("Successful Opening of Serial Port: %1").arg(serialPortName) << endl;
                matchingFlag = true;
                break;
            }
        }
    }
    if(!matchingFlag){
        qDebug() << QObject::tr("Please check the serial port. No suitable serial port can communicate.") << endl;
    }
}

easyModbus2::easyModbus2(QString selfDefinedPortName)
{

    this->serialPortName = selfDefinedPortName;
    serialPort.setPortName(serialPortName);
    serialPort.setBaudRate(QSerialPort::Baud9600);//设置波特率和读写方向
    serialPort.setDataBits(QSerialPort::Data8);      //数据位为8位
    serialPort.setFlowControl(QSerialPort::NoFlowControl);//无流控制
    serialPort.setParity(QSerialPort::NoParity); //无校验位
    serialPort.setStopBits(QSerialPort::OneStop);  //一位停止位
    if (serialPort.isOpen())//如果串口已经打开了 先给他关闭了
    {
        // serialPort.clear();
        serialPort.close();
    }

    if (!serialPort.open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
    {
        qDebug() << QObject::tr("Failed to open serial port: %1").arg(serialPortName) << endl;

    }
    else
    {
        qDebug() << QObject::tr("Successful Opening of Serial Port: %1").arg(serialPortName) << endl;
    }
}

easyModbus2::~easyModbus2()
{
    serialPort.clear();
    serialPort.close();
}

void easyModbus2::sendMsg(QString input)
{
	QByteArray writeData;

	QString str;
	bool ok;
	char data;
	QStringList list;
	str = input;

	list = str.split(" ");
	for (int i = 0; i < list.count(); i++) {
		if (list.at(i) == " ")
			continue;
		if (list.at(i).isEmpty())
			continue;
		data = (char)list.at(i).toInt(&ok, 16);
		if (!ok)
		{
			qDebug() << "输入数据有误" << endl;
		}
		writeData.append(data);
	}
	////发送数据
	//	serialPort.write(buf);
    //  QByteArray str1=QByteArray::fromHex(str.toLatin1().data());???

	qint64 bytesWritten = serialPort.write(writeData);

	if (bytesWritten == -1)
	{
		qDebug() << QObject::tr("Failed to write the data to port %1 , error:%2").arg(serialPortName).arg(serialPort.errorString()) << endl;
	}
	else if (bytesWritten != writeData.size())
	{
		qDebug() << QObject::tr("Failed to write all the data to port %1 , error:%2").arg(serialPortName).arg(serialPort.errorString()) << endl;
	}
	else if (!serialPort.waitForBytesWritten(5000))
	{
		qDebug() << QObject::tr("Operation timed out or an error occurred for port %1 , error:%2").arg(serialPortName).arg(serialPort.errorString()) << endl;
	}
	//////////////////////显示发送的数据/////////////////////////////////////////////////

	qDebug() << QObject::tr("Data successfully sent to port %1").arg(serialPortName) << endl;

	//////////////////////显示接收的数据/////////////////////////////////////////////////
}

void easyModbus2::sendMsg(int intInput)
{
	QString input = QString::fromStdString(CRC16::convertIntToModbusString(intInput));
	sendMsg(input);
}

QByteArray easyModbus2::readMsg()
{
	QByteArray readData = serialPort.readAll();
	while (serialPort.waitForReadyRead(1000))
		readData.append(serialPort.readAll());
	if (serialPort.error() == QSerialPort::ReadError)
	{
		qDebug() << QObject::tr("Failed to read from port %1 ,error: %2 ").arg(serialPortName).arg(serialPort.errorString()) << endl;
	}
	else if (serialPort.error() == QSerialPort::TimeoutError && readData.isEmpty())
	{
		qDebug() << QObject::tr("No data was currently available for reading from port %1").arg(serialPortName) << endl;
	}
    else{
        qDebug() << QObject::tr("Data successfully received from port %1").arg(serialPortName) << endl;
    }
    if(!readData.isEmpty()){
        qDebug() << readData.toHex() << endl;
        //	QString backdata = readData.toHex();
        qDebug() << readData.toHex();
    }
	return readData;
}
