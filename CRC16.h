#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <typeinfo>


// 与CRC16 代码很多重复，为了增加模块可移植性
namespace LRC {
    typedef unsigned char BYTE;
    typedef unsigned short WORD;

    /**
    * @brief         calculate LRC
    * @author        George
    * @date          2019-07-03
    */
    // https://www.modbustools.com/modbus.html
    inline BYTE calLRC(BYTE *nData, WORD wLength)
    {
        BYTE nLRC = 0; // LRC char initialized

        for (int i = 0; i < wLength; i++) {
            nLRC += *nData++;
        }

        return (BYTE)(-nLRC);

    } // End: LRC


    /**
    * @brief         将int转化为hex, 并以一个字节的形式输出
    * @author        George
    * @date          2019-07-04
    */
    inline std::string intToHex2(int input)
    {
        std::stringstream stream;
        stream << std::setw(2) << std::setfill('0') << std::hex << input;
        return stream.str();
    }

    /**
    * @brief         toupper every char in nData
    * @author        George
    * @date          2019-07-03
    */
    inline void mytoupper(BYTE *nData, WORD wLength) {
        for (int i = 0; i < wLength; i++) {
            if (*nData >= 'a' && *nData <= 'z') {
                *nData = toupper(*nData);
            }
            nData++;
        }
    }

    /**
    * @brief         toupper every char in nData
    * @author        George
    * @date          2019-07-03
    */
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


    /**
    * @brief         将char数组转化为以hex编码的字符串
    * @author        George
    * @date          2019-07-04
    */
    inline std::string convertCharToHexString(const BYTE *nData, WORD wLength) {
        std::string res;
        while (wLength--)
        {
            res.append(mytoupper2(intToHex2(static_cast<int>(*nData++))));
        }
        return res;
    }

    /**
    * @brief         convert each char in Input string to Ascii and ignore space in Input string
    * @author        George
    * @date          2019-07-03
    */
    inline std::string convertStringToFinalAscii(std::string temp) {

        std::string results = "3A";
        std::stringstream tempStream;
        // ===== 拼接校验码 ======= //
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

//        std::cout << "===============================" << std::endl;
//        std::cout << "Results:   " << results << std::endl;
//        std::cout << "===============================" << std::endl;

        return results;
    }

    /**
    * @brief         convert the data to Ascii string(following the modbus rule)
    * @author        George
    * @date          2019-07-03
    */
    inline std::string convertIntToModbusString(int input, int numberOfRefgister) {
        const int wLength = 6;
        // 1. 设置初始值 -- 不包括校验码
        BYTE byteArray[wLength] = { 0x01, 0x06, 0x13, 0x18, 0xFF, 0x00 };

        // 2. 寄存器设置
        // ---- 高位 ---- //
        *(byteArray + 2) = static_cast<BYTE>(numberOfRefgister >> 8);
        // ---- 低位 ---- //
        *(byteArray + 3) = static_cast<BYTE>((numberOfRefgister & 0x00FF));
        // 3. 设置符号位
        if (input <= 0) {
            *(byteArray + 4) = 0xFF;
            input = std::abs(input);
        }
        else
        {
            *(byteArray + 4) = 0x00;
        }

        // 4. 设置写入数据的绝对值 将绝对值转化为16进制
        *(byteArray + 5) = static_cast<BYTE>(input);

        std::string intStr1 = convertCharToHexString(byteArray, wLength);

//        std::cout << "===============================" << std::endl;
//        std::cout << "intStr1:   " << intStr1 << std::endl;
//        std::cout << "===============================" << std::endl;

        // 5. 校验码计算
        BYTE tempLRC;
        tempLRC= calLRC(byteArray, wLength);

        std::string intStr2 = mytoupper2(intToHex2(tempLRC));

//        std::cout << "===============================" << std::endl;
//        //std::cout << intToHex2(tempLRC) << std::endl;
//        std::cout << "intStr2:   " << intStr2 << std::endl;
//        std::cout << "===============================" << std::endl;

        intStr1.append(intStr2);

//        std::cout << "===============================" << std::endl;
//        std::cout << "intStr:   " << intStr1 << std::endl;
//        std::cout << "===============================" << std::endl;

        return convertStringToFinalAscii(intStr1);
    }
}
