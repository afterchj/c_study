/*************************************************************************
 
    > File Name: blt_time.c
 
    > Author: hongjian.chen
 
    > Mail: 766256898@qq.com
 
    > Created Time: 2019年1月15日 星期三 15时12分52秒
 
 ************************************************************************/

#include "blt_main.h"

char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

void sig_handler(int num) 
{ 
    char * s1="77011465FFFFFFFF2A00000000C000373700000000CCCC";
    char * s2="77011465FFFFFFFF2A00000000C000323200000000CCCC";
    int size=strlen(s1)+1;
    time(&timep);
    p=gmtime(&timep);
    int h=p->tm_hour+8;                                                                                                                                                                                                                                                                                     
    int m=p->tm_min;
    int mon=p->tm_mon+1;
    int day=p->tm_mday;
    printf("current time is %d-%02d-%02d %02d:%02d:%02d\n",p->tm_year+1900,mon,day,h,m,p->tm_sec);
    if(h==17 & m==5)
    {
        printf("start excute task...\n");
        uart_init();//串口初始化
	    int ret = write(uartfd, s1, size);//将接收到的服务器发送过来的数据下发至dongle
		if (ret == -1)
		{
			perror("write");
			uart_init();//if uart error,open uart again
			write(uartfd, s1, size);
		}
    }
    if(h==17 & m==10)
    {
        printf("stop excute task...\n");
        uart_init();//串口初始化
	    int ret = write(uartfd, s2, size);//将接收到的服务器发送过来的数据下发至dongle
		if (ret == -1)
		{
			perror("write");
			uart_init();//if uart error,open uart again
			write(uartfd, s2, size);
		}
    }
    alarm(30);
}
