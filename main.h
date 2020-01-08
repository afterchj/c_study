#include<stdio.h>
#include<string.h>
#include<ctype.h>


//十六进制转字符串函数
void Hex2Str(const char* source, int sourceLen);
//字符串转十六进制字符串
unsigned char * Str2Hex( const char *sSrc, int nSrcLen );

unsigned char * HexArrayToString(unsigned char *hexarray,int length);

/*****************************stringtohex.c***************************************/
extern unsigned char char_to_hex_low(char low_data);//一个字节的低位解析
extern unsigned char char_to_hex_high(char high_data);//一个字节的高位解析
extern unsigned char two_char_to_BYTE(char *twochar);//将两个连续的字符转换为16进制