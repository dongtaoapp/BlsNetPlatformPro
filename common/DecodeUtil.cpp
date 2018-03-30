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
* �ı������ֽڡ�
* ˵����
*   1 ������ı����ֽڵ�16�����ַ��������볤��Ϊ2��
*     ��ʽ��"00" ~ "FF", �ַ� A~F ��Ϊ��д��
*   2 ���ڽ�ͼƬͨ��XML�ı�����ʱ����������á�
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
* �ֽڱ�����ı���
* ˵����
*   1 �������ı��Ǹ��ֽڵ�16������ʽ���ַ�����
*     ��ʽ��"00" ~ "FF", �ַ� A~F ��Ϊ��д��
*   2 ���ڽ�ͼƬͨ��(XML)�ı�����ʱ�������á�
*   3 ��Ӧ�Ľ��뺯��Ϊ byte hexstrToByte(String)
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
* ���ֽ�����ת��Ϊ�ַ���
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
* ���ַ���ת��Ϊ�ֽ�����
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
