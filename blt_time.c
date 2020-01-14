/*************************************************************************
 
    > File Name: alarm.c
 
    > Author:
 
    > Mail:
 
    > Created Time: 2015年11月20日 星期五 21时12分52秒
 
 ************************************************************************/
#include "blt_main.h"

char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
time_t timep;
struct tm *p;

void sig_handler(int num)
{
    time(&timep);
    p=gmtime(&timep);
    // printf("receive the signal %d.\n", num);
    int h=p->tm_hour+8;                                                                                                                                                                                                                                                                                     
    int m=p->tm_min;
    printf("%s %d:%d:%d->receive the signal %d\n", wday[p->tm_wday], h, m, p->tm_sec,num);
    if(h==11 & m==45)
    {
        printf("start excute task...\n");
    }
    if(h==11 & m==48)
    {
        printf("stop excute task...\n");
    }
    alarm(20);
}
 
// int main()
// {
//     // time(&timep);
//     // p=gmtime(&timep);
//     // printf("%s %d:%d:%d\n", wday[p->tm_wday], p->tm_hour+8, p->tm_min, p->tm_sec);
//     signal(SIGALRM, sig_handler);
//     // alarm(10);
//     // char cur_time[20];
//     while(1){
//         pause();
//         printf("pause is over.\n");
//     //     struct timeval tv;
//     //     gettimeofday(&tv,NULL);//获取1970-1-1到现在的时间结果保存到tv中
//     //     uint64_t sec=tv.tv_sec;
//     //     uint64_t min=tv.tv_sec/60;
//     //     struct tm cur_tm;//保存转换后的时间结果
//     //     localtime_r((time_t*)&sec,&cur_tm);
//     //     char cur_time[20];
//     //     snprintf(cur_time,20,"%d-%02d-%02d %02d:%02d:%02d",cur_tm.tm_year+1900,cur_tm.tm_mon+1,cur_tm.tm_mday,cur_tm.tm_hour,cur_tm.tm_min,cur_tm.tm_sec);
//     //     printf("current time is %s\n",cur_time);//打印当前时间
//     }
//     exit(0);
//     // return 0;
// }
