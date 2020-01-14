/*************************************************************************
 
    > File Name: alarm.c
 
    > Author:
 
    > Mail:
 
    > Created Time: 2015年11月20日 星期五 21时12分52秒
 
 ************************************************************************/
#include<sys/time.h>
#include<stdio.h>
#include<time.h>
#include<stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
time_t timep;
struct tm *p;

void sig_handler(int num)
{
    time(&timep);
    p=gmtime(&timep);
    // printf("receive the signal %d.\n", num);
    printf("%s %d:%d:%d->receive the signal %d\n", wday[p->tm_wday], p->tm_hour+8, p->tm_min, p->tm_sec,num);
    alarm(10);
}
 
int main()
{
    time(&timep);
    p=gmtime(&timep);
    printf("%s %d:%d:%d\n", wday[p->tm_wday], p->tm_hour+8, p->tm_min, p->tm_sec);
    signal(SIGALRM, sig_handler);
    alarm(20);
    while(1){
        pause();
        printf("pause is over.\n");
    }
    exit(0);
}
