#include ".\DecodeUtil.h"
#include <boost/format.hpp>

namespace jysoft{
namespace utility {

CDecodeUtil::CDecodeUtil(void)
{
}

CDecodeUtil::~CDecodeUtil(void)
{
}

/**
* 文本解码字节。
* 说明：
*   1 输入的文本是字节的16进制字符串，必须长度为2。
*     格式如"00" ~ "FF", 字符 A~F 均为大写。
*   2 用于将图片通过XML文本传输时，编码解码用。
*
* @param str String
* @return byte
*/
byte CDecodeUtil::hexstrToByte(const char cCoding[])
{
	byte c1 = cCoding[0];
	byte c2 = cCoding[1];
	c1 = (byte) (c1 > '9' ? c1 - 55 : c1 - 48);
	c2 = (byte) (c2 > '9' ? c2 - 55 : c2 - 48);
	return (byte) (c1 << 4 | c2);
}

/**
* 字节编码成文本。
* 说明：
*   1 编码后的文本是该字节的16进制形式的字符串，
*     格式如"00" ~ "FF", 字符 A~F 均为大写。
*   2 用于将图片通过(XML)文本传输时，编码用。
*   3 对应的解码函数为 byte hexstrToByte(String)
*
* @param b byte
* @return String
*/
std::string CDecodeUtil::byteToHexstr(byte b)
{
	byte c1 = (byte) ((b >> 4) & 15);
	byte c2 = (byte) (b & 15);
	c1 = (byte) (c1 > 9 ? c1 + 55 : c1 + 48);
	c2 = (byte) (c2 > 9 ? c2 + 55 : c2 + 48);

	boost::format   fm("%c%c");
	fm % c1 % c2;
	return fm.str();
}

/**
* 将字节数组转换为字符串
*/
std::string CDecodeUtil::byteArrayToHexstr(byte *lptrData, long dwLength)
{
	std::string rtn;
	if(lptrData == NULL || dwLength <= 0)
		return rtn;
	for(long i =0; i < dwLength; ++i)
		rtn = rtn + byteToHexstr(lptrData[i]);
	return rtn;
}

std::string CDecodeUtil::byteArrayToHexstr(std::vector<byte>::iterator bpos, std::vector<byte>::iterator endpos)
{
	std::string strRtn;
	for(; bpos != endpos; ++bpos)
	{
		strRtn = strRtn + byteToHexstr(*bpos);
	}
	return strRtn;
}

/**
* 将字符串转换为字节数组
*/
long CDecodeUtil::hexstrToByteArray(const std::string &str, /*out*/byte *lpDecodeData)
{
	if(lpDecodeData == NULL)
		return str.length()/2;
	for(long iStep =0 ; iStep < str.length(); iStep += 2)
	{
		char cTmp[2];
		cTmp[0] = str.c_str()[iStep];
		cTmp[1] = str.c_str()[iStep+1];
		lpDecodeData[iStep/2] = hexstrToByte(cTmp);
	}
	return str.length()/2;
}

}}
