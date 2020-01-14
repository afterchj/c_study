#include "main.h"

char sDest[100]={0};
unsigned char dest[100]={0};

const unsigned char Num2CharTable[] = "0123456789ABCDEF";//16进制数据转换为字符串使用
//int j = 0;//record number of 0xcc
unsigned char string[128];

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

//十六进制转字符串函数
unsigned char* Hex2Str(const char* source, int sourceLen)
{
    short i;
    unsigned char highByte, lowByte;
    for (i = 0; i < sourceLen; i += 2)
    {
        highByte = toupper(source[i]);
        lowByte  = toupper(source[i + 1]);
        if (highByte > 0x39)  
            highByte -= 0x37; //'A'->10 'F'->15
        else
            highByte -= 0x30; //'1'->1 '9'->9
        if (lowByte > 0x39)
            lowByte -= 0x37;
        else
            lowByte -= 0x30;
        dest[i / 2] = (highByte << 4) | lowByte;
    }
	printf("source=%s\n",source);
	return dest;
}

//字符串转十六进制字符串
unsigned char * Str2Hex( const char *sSrc, int nSrcLen )
{
    int  i;
    char szTmp[3];
    for( i = 0; i < nSrcLen; i++ )
    {
        sprintf( szTmp, "%02X", (unsigned char) sSrc[i] );
        memcpy( &sDest[i * 2], szTmp, 2 );
    }
	printf("source=%s\n",sSrc);
	return sDest;
}
