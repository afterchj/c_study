#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
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
    int mon=p->tm_mon+1;
    int day=p->tm_mday;
    printf("current time is %d-%02d-%02d %02d:%02d:%02d\n",p->tm_year+1900,mon,day,h,m,p->tm_sec);
     if(h==10 & m==50)
    {
        printf("start excute task...\n");
    }
    if(h==10 & m==55)
    {
        printf("stop excute task...\n");
    }
    alarm(30);
}

int main(int argc,const char *argv[]) 
{ 
    time(&timep);
    p=gmtime(&timep);
    // printf("receive the signal %d.\n", num);
    int h=p->tm_hour+8;                                                                                                                                                                                                                                                                                     
    int m=p->tm_min;
    printf("initial time is %d-%02d-%02d %02d:%02d:%02d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday,h,m,p->tm_sec);
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
    // exit(0);
}