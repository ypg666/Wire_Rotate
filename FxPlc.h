/*********************************************************************************
  *Copyright(C)
  *ClassName:  FxLib
  *Author:  佳豪
  *Version: 1.0
  *Date:  2019.7.28
  *Description: PLC操作
  *Others:  //其他内容说明
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
  *History:
**********************************************************************************/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

typedef unsigned char BYTE;

class FxLib
{
public:
	FxLib() = default;
	~FxLib();

	std::string getWriteMsg(int uAddress, int wNumber);

private:
	std::string mytoupper2(std::string nData);

	std::string intToHexW4(int input);

	std::string intToHexW2(int input);

	int checkSum(std::vector<BYTE> nData);

	std::string convertVectorCharToHexString(std::vector<BYTE> nData);

	std::string getReadMsg(int uAddress, int byteNum);

};
