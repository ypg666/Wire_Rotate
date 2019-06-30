#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <typeinfo>

// 调用CRC::convertIntToModbusString(int ) 即可

template <typename T>
T string_to_T(std::string const &val)
{
	std::istringstream istr(val);
	T returnVal;
	if (!(istr >> returnVal)) {
		std::cout << "Not a valid " + (std::string)typeid(T).name() + " received!\n";
	}
	return returnVal;
}

namespace CRC16 {

	typedef unsigned char BYTE;
	typedef unsigned short WORD;
	// Ref: https://www.modbustools.com/modbus_crc16.html
	static const WORD wCRCTable[] = {
		0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
		0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
		0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
		0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
		0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
		0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
		0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
		0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
		0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
		0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
		0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
		0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
		0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
		0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
		0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
		0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
		0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
		0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
		0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
		0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
		0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
		0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
		0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
		0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
		0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
		0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
		0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
		0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
		0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
		0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
		0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
		0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

	inline WORD CRC16(const BYTE *nData, WORD wLength)
	{

		BYTE nTemp;
		WORD wCRCWord = 0xFFFF;

		while (wLength--)
		{
			nTemp = *nData++ ^ wCRCWord;
			wCRCWord >>= 8;
			wCRCWord ^= wCRCTable[nTemp];
		}
		return wCRCWord;

	}

	// intToHex 和 intToHex均为十进制转十六进制函数
	inline std::string intToHex(int input)
	{
		std::stringstream stream;
		stream << "0x" << std::hex << input;
		return stream.str();
	}

	inline std::string intToHex2(int input)
	{
		std::stringstream stream;
		stream << std::setw(2) << std::setfill('0') <<std::hex << input;
		return stream.str();
	}

    inline std::string intToHexW4(int input)
    {
        std::stringstream stream;
        stream << std::setw(4) << std::setfill('0') << std::hex << input;
        return stream.str();
    }

	inline std::string convertCharToHexString(const BYTE *nData, WORD wLength) {
		std::string res;
		while (wLength--)
		{
			res.append(intToHex2(static_cast<int>(*nData++)));
			if (wLength > 0) {
				res.append(" ");
			}
		}
		return res;
	}

	// Modbus 采用char类型输出更为简单 -- 之所以用String输出，是为了直接对应之前的IOclass
	inline std::string convertIntToModbusString(int input) {
		const int wLength = 6;
		// 设置初始值 -- 不包括校验码
        BYTE byteArray[wLength] = { 0x01, 0xF6, 0xD4, 0x08, 0xFF, 0x00};

        // 处理符号位
        if (input < 0) {
            *(byteArray + 4) = 0xff;
            input = std::abs(input);
        }
        else
        {
            *(byteArray + 4) = 0x00;
        }

		// 将绝对值转化为16进制
		*(byteArray + 5) = static_cast<BYTE>(input);
		WORD tempCRC;
		tempCRC = CRC16(byteArray, wLength);

        std::string tempC = intToHexW4(static_cast<int>(tempCRC));
		// std::cout << tempC << std::endl;

		// 拼接校验码
		std::string tempRes = convertCharToHexString(byteArray, wLength);

		tempRes.append(" ");
		tempRes.append(tempC.substr(2, 2));
		tempRes.append(" ");
		tempRes.append(tempC.substr(0, 2));
		std::cout << tempRes << std::endl;

		return tempRes;
	}

}


// 与CRC16 代码很多重复，为了增加模块可移植性
namespace LRC {

    typedef unsigned char BYTE;
    typedef unsigned short WORD;

    // https://www.modbustools.com/modbus.html
    inline BYTE calLRC(BYTE *nData, WORD wLength)
    {
        BYTE nLRC = 0; // LRC char initialized

        for (int i = 0; i < wLength; i++) {
            nLRC += *nData++;
        }

        return (BYTE)(-nLRC);

    } // End: LRC

    inline std::string intToHex2(int input)
    {
        std::stringstream stream;
        stream << std::setw(2) << std::setfill('0') << std::hex << input;
        return stream.str();
    }

    inline void mytoupper(BYTE *nData, WORD wLength) {
        for (int i = 0; i < wLength; i++) {
            if (*nData >= 'a' && *nData <= 'z') {
                *nData = toupper(*nData);
            }
            nData++;
        }
    }

    inline std::string mytoupper2(std::string nData) {
        // std::cout << "==" << "SIZE: " << nData.size() << "==" << std::endl;
        for (int i = 0; i < nData.size(); i++) {
            // std::cout << "==" << nData[i] << "==" << std::endl;
            if (nData[i] >= 'a' && nData[i] <= 'z') {
                nData[i] = toupper(nData[i]);
            }
        }
        return nData;
    }

    inline std::string convertCharToHexString(const BYTE *nData, WORD wLength) {
        std::string res;
        while (wLength--)
        {
            res.append(mytoupper2(intToHex2(static_cast<int>(*nData++))));
        }
        return res;
    }

    inline std::string convertStringToFinalAscii(std::string temp) {

        std::string results = "3A";

        std::stringstream tempStream;
        // 拼接校验码
        for (size_t i = 0; i < temp.size(); i++)
        {
            if (temp[i] == ' ') {
                continue;
            }
            tempStream << std::hex << int(temp[i]);
            // std::cout << tempStream.str() << std::endl;
            // tempStream.clear();
        }
        results.append(tempStream.str());
        std::string tempRes = "0D0A";
        results.append(tempRes);

        std::cout << "===============================" << std::endl;
        std::cout << "Results:   " << results << std::endl;
        std::cout << "===============================" << std::endl;

        return results;
    }

    // Modbus 采用char类型输出更为简单 -- 之所以用String输出，是为了直接对应之前的IOclass
    inline std::string convertIntToModbusString(int input) {
        const int wLength = 6;
        // 设置初始值 -- 不包括校验码
        BYTE byteArray[wLength] = { 0x01, 0x05, 0x05, 0x00, 0xFF, 0x00 };

        // 处理符号位
        if (input <= 0) {
            *(byteArray + 4) = 0xFF;
            input = std::abs(input);
        }
        else
        {
            *(byteArray + 4) = 0x00;
        }

        // 将绝对值转化为16进制
        *(byteArray + 5) = static_cast<BYTE>(input);


        std::string intStr1 = convertCharToHexString(byteArray, wLength);

        std::cout << "===============================" << std::endl;
        std::cout << "intStr1:   " << intStr1 << std::endl;
        std::cout << "===============================" << std::endl;

        // 校验码计算
        BYTE tempLRC;
        tempLRC= calLRC(byteArray, wLength);

        std::string intStr2 = mytoupper2(intToHex2(tempLRC));

        std::cout << "===============================" << std::endl;
        //std::cout << intToHex2(tempLRC) << std::endl;
        std::cout << "intStr2:   " << intStr2 << std::endl;
        std::cout << "===============================" << std::endl;

        intStr1.append(intStr2);

        std::cout << "===============================" << std::endl;
        std::cout << "intStr:   " << intStr1 << std::endl;
        std::cout << "===============================" << std::endl;

        return convertStringToFinalAscii(intStr1);
    }

}
