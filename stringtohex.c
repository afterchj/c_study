#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

const unsigned char Num2CharTable[] = "0123456789ABCDEF";//16进制数据转换为字符串使用
//int j = 0;//record number of 0xcc
unsigned char string[128];

unsigned char char_to_hex_low(char low_data)//一个字节的低位解析
{
	switch(low_data)
	{
	case '0':
		return 0x00;
	case '1':
		return 0x01;
	case '2':
		return 0x02;
	case '3':
		return 0x03;
	case '4':
		return 0x04;
	case '5':
		return 0x05;
	case '6':
		return 0x06;
	case '7':
		return 0x07;
	case '8':
		return 0x08;
	case '9':
		return 0x09;
	case 'A':
	case 'a':
		return 0x0A;
	case 'B':
	case 'b':
		return 0x0B;
	case 'C':
	case 'c':
		return 0x0C;
	case 'D':
	case 'd':
		return 0x0D;
	case 'E':
	case 'e':
		return 0x0E;
	case 'F':
	case 'f':
		return 0x0F;
	}
}


unsigned char char_to_hex_high(char high_data)//一个字节的高位解析
{
	switch(high_data)
	{
	case '0':
		return (0x00 * 16);
	case '1':
		return (0x01 * 16);
	case '2':
		return (0x02 * 16);
	case '3':
		return (0x03 * 16);
	case '4':
		return (0x04 * 16);
	case '5':
		return (0x05 * 16);
	case '6':
		return (0x06 * 16);
	case '7':
		return (0x07 * 16);
	case '8':
		return (0x08 * 16);
	case '9':
		return (0x09 * 16);
	case 'A':
	case 'a':
		return (0x0A * 16);
	case 'B':
	case 'b':
		return (0x0B * 16);
	case 'C':
	case 'c':
		return (0x0C * 16);
	case 'D':
	case 'd':
		return (0x0D * 16);
	case 'E':
	case 'e':
		return (0x0E * 16);
	case 'F':
	case 'f':
		return (0x0F * 16);
	}
}

unsigned char two_char_to_BYTE(char *twochar)//将两个连续的字符转换为16进制
{
	return (char_to_hex_high(twochar[0]) + char_to_hex_low(twochar[1]));	
}

unsigned char * HexArrayToString(unsigned char *hexarray,int length)
{
	int gy_i = 0;
	int gy_j = 0;
	for (; gy_i< length; gy_i++)
	{
		string[gy_j++] = Num2CharTable[hexarray[gy_i] / 16];
		string[gy_j++] = Num2CharTable[hexarray[gy_i] % 16];
	}
	return string;
}

// int main(void)
// {
// 	unsigned char src[]="770501013737CCCC";
// 	unsigned char server_to_c2000_to_dongle_buf_hex[128];//server发送过来的16进制数据保存到该位置
// 	int gy_i = 0;
// 	printf("%s<-StrToHex->",src);
// 	for(; gy_i<strlen(src); gy_i++)
// 	{
// 		if (gy_i%2==0)
// 		{
// 			server_to_c2000_to_dongle_buf_hex[gy_i / 2] = two_char_to_BYTE(&src[gy_i]);//将两个连续的字符转换为16进制
// 			printf("%02x ", server_to_c2000_to_dongle_buf_hex[gy_i / 2]);
// 		}
// 	}
// 	printf("\n");
// 	unsigned char * str = Hex2Str(server_to_c2000_to_dongle_buf_hex,strlen(server_to_c2000_to_dongle_buf_hex));
//     printf("HexToStr=%s\n",str); 	
// 	return 0;
// }