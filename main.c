#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned char Num2CharTable[] = "0123456789ABCDEF";//16进制数据转换为字符串使用
//int j = 0;//record number of 0xcc

void HexArrayToString(unsigned char *hexarray,int length,unsigned char *string)
{
	int gy_i = 0;
	int gy_j = 0;
	for (; gy_i< length; gy_i++)
	{
		string[gy_j++] = Num2CharTable[hexarray[gy_i] / 16];
		string[gy_j++] = Num2CharTable[hexarray[gy_i] % 16];
	}
    printf("result=%s\n",string);
}

int main(void)
{
   unsigned char src[]="770501013737CCCC";
   unsigned char str[100];
   HexArrayToString(src,strlen(src),str);

    // getchar();
    return 0;
}