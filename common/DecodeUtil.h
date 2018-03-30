#pragma once
#include ".\common_global.h"
#include <string>
#include <vector>


namespace jysoft{
namespace utility {
	/**
* ����ͽ�����
*/
class AFX_EXT_CLASS CDecodeUtil
{
public:
	CDecodeUtil(void);
	~CDecodeUtil(void);
public:
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
    static byte hexstrToByte(const char cCoding[2]);
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
	static std::string byteToHexstr(byte b);
	/**
	 * ���ֽ�����ת��Ϊ�ַ���
	 */
	static std::string byteArrayToHexstr(byte *lptrData, long dwLength);

	static std::string byteArrayToHexstr(std::vector<byte>::iterator bpos, std::vector<byte>::iterator endpos);
	/**
	 * ���ַ���ת��Ϊ�ֽ�����
	 */
	static long hexstrToByteArray(const std::string &str, /*out*/byte *lpDecodeData);
};

}}
