#include "FxPLC.h"

FxLib::~FxLib()
{
}

std::string FxLib::getWriteMsg(int uAddress, int wNumber)
{
	std::vector<BYTE> nData;
	// 1. 起始命令
	nData.push_back(0x02);
	// 2. 读取指令 ‘1’
	nData.push_back('1');
	// 3. 地址处理
	uAddress = uAddress * 2 + 0x1000;
	std::string temp;
	temp = intToHexW4(uAddress);
	// std::cout << temp << std::endl;
	for (auto &ch : temp) {
		nData.push_back(ch);
	}
	// 4. 写入字节设置 -- 四个字节 04
	nData.push_back('0');
	nData.push_back('4');

	// 5. 写入数据设置
	temp.clear();
	temp = intToHexW2(wNumber);
	for (auto &ch : temp) {
		nData.push_back(ch);
	}
	nData.push_back('0');
	nData.push_back('0');
	// 6. 加入终止符
	nData.push_back(0x03);
	int tempSum = checkSum(nData);
	temp.clear();
	temp = intToHexW2(tempSum);
	for (auto &ch : temp) {
		nData.push_back(ch);
	}

	std::string res = convertVectorCharToHexString(nData);
	// std::cout << res << std::endl;
	return res;
}

std::string FxLib::mytoupper2(std::string nData)
{
	// std::cout << "==" << "SIZE: " << nData.size() << "==" << std::endl;
	for (int i = 0; i < nData.size(); i++) {
		// std::cout << "==" << nData[i] << "==" << std::endl;
		if (nData[i] >= 'a' && nData[i] <= 'z') {
			nData[i] = toupper(nData[i]);
		}
	}
	return nData;
}

std::string FxLib::intToHexW4(int input)
{
	std::stringstream stream;
	stream << std::setw(4) << std::setfill('0') << std::hex << input;
	return mytoupper2(stream.str());
}

std::string FxLib::intToHexW2(int input)
{
	std::stringstream stream;
	stream << std::setw(2) << std::setfill('0') << std::hex << input;
	return mytoupper2(stream.str());
}

int FxLib::checkSum(std::vector<BYTE> nData)
{
	int cheSum = 0;
	// 以终止符为界
	for (int i = 1; nData[i] != 0x03; i++)
	{
		cheSum += nData[i];
	}
	// 加上终止符
	cheSum += 0x03;
	// 累加和超过两位取低两位
	cheSum = (cheSum & 0xFF);
	return cheSum;
}

std::string FxLib::convertVectorCharToHexString(std::vector<BYTE> nData)
{
	std::string res;
	int length = nData.size();
	for (size_t i = 0; i < length; i++)
	{
		if (i != 0) {
			res.append(" ");
		}
		res.append(intToHexW2(static_cast<int>(nData[i])));
	}
	return res;
}

std::string FxLib::getReadMsg(int uAddress, int byteNum)
{
	std::vector<BYTE> nData;
	// 1. 起始命令
	nData.push_back(0x02);
	// 2. 读取指令 ‘1’
	nData.push_back('0');
	// 3. 地址处理
	uAddress = uAddress * 2 + 0x1000;
	std::string temp;
	temp = intToHexW4(uAddress);
	std::cout << temp << std::endl;
	for (auto &ch : temp) {
		nData.push_back(ch);
	}
	// 4. 写入字节设置 -- 两个字节 02
	nData.push_back('0');
	nData.push_back('0' + byteNum);

	//// 5. 写入数据设置
	//temp.clear();
	//temp = intToHexW2(wNumber);
	//for (auto &ch : temp) {
	//	nData.push_back(ch);
	//}
	// 6. 加入终止符
	nData.push_back(0x03);
	int tempSum = checkSum(nData);
	temp.clear();
	temp = intToHexW2(tempSum);
	for (auto &ch : temp) {
		nData.push_back(ch);
	}

	std::string res = convertVectorCharToHexString(nData);
	std::cout << "ReadMsg:" << res << std::endl;
	return res;
}

