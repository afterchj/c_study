#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>

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
    alarm(10);
}
int main(int argc, char *argv[]) 
{ 
    signal(SIGALRM, sig_handler);
    alarm(10);
    while(1)//做一个死循环，防止主线程提早退出，相等于线程中的join
    {
        pause();
    }
    //pause();//如果没有做一个死循环则只会让出一次cpu然后就还给主线程，主线程一旦运行结束就会退出程序
    // struct timeval tv;
    // gettimeofday(&tv,NULL);//获取1970-1-1到现在的时间结果保存到tv中
    // uint64_t sec=tv.tv_sec;
    // uint64_t min=tv.tv_sec/60;
    // struct tm cur_tm;//保存转换后的时间结果
    // localtime_r((time_t*)&sec,&cur_tm);
    // char cur_time[20];
    // snprintf(cur_time,20,"%d-%02d-%02d %02d:%02d:%02d",cur_tm.tm_year+1900,cur_tm.tm_mon+1,cur_tm.tm_mday,cur_tm.tm_hour,cur_tm.tm_min,cur_tm.tm_sec);
    // if(cur_tm.tm_min==15)
    // {
    //     printf("执行定时任务。。。");
    // }
    // printf("current time is %s\n",cur_time);//打印当前时间
    exit(0);
}