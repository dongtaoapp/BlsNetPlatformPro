#pragma once
#include ".\common_global.h"
#include <string>
#include <vector>


namespace jysoft{
namespace utility {
	/**
* 编码和解码类
*/
class AFX_EXT_CLASS CDecodeUtil
{
public:
	CDecodeUtil(void);
	~CDecodeUtil(void);
public:
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
    static byte hexstrToByte(const char cCoding[2]);
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
	static std::string byteToHexstr(byte b);
	/**
	 * 将字节数组转换为字符串
	 */
	static std::string byteArrayToHexstr(byte *lptrData, long dwLength);

	static std::string byteArrayToHexstr(std::vector<byte>::iterator bpos, std::vector<byte>::iterator endpos);
	/**
	 * 将字符串转换为字节数组
	 */
	static long hexstrToByteArray(const std::string &str, /*out*/byte *lpDecodeData);
};

}}
