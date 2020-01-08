#ifndef __HILINK_H__
#define __HILINK_H__

/*******net********/
#include <stdio.h>
#include <string.h>

#define BUFFSIZE  128

/*****************************stringtohex.c***************************************/
extern unsigned char char_to_hex_low(char low_data);//一个字节的低位解析
extern unsigned char char_to_hex_high(char high_data);//一个字节的高位解析
extern unsigned char two_char_to_BYTE(char *twochar);//将两个连续的字符转换为16进制

/*****************************hextostring.c***************************************/
extern void HexArrayToString(unsigned char *hexarray, int length, unsigned char *string);

#endif
