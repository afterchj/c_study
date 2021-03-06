#include "blt_main.h"

#define BUF_SIZE 50
int uartfd = -1;
int sockfd = -1;

int main(int argc, const char *argv[])
{
    int res;
	void * thrd_ret;
    pthread_t tcp_thread, uart_thread, time_thread;
    printf("main start!!\n");
	checknet();//检查网络是否正常，main函数中的网络初始化
	gy_set_sockfd();//设置tcp通信的描述符：gy_c2000_sockfd
    res=pthread_create(&tcp_thread, NULL, thrd_func_tcp_callback, NULL);
    if (res != 0)
	{
		perror("write_thread");
		exit(-1);
	}

    res=pthread_create(&uart_thread, NULL, thrd_func_uart_callback, NULL);
    if (res != 0)
	{
		perror("read_thread");
		exit(-1);
	}

	res=pthread_create(&time_thread, NULL, thrd_func_time_callback, NULL);
    if (res != 0)
	{
		perror("read_thread");
		exit(-1);
	}

    pthread_join(uart_thread, &thrd_ret);//线程回收
	pthread_join(time_thread, &thrd_ret);//线程回收
    uart_close();//串口关闭
	// pthread_join(write_thread, &thrd_ret);//线程回收
    close(sockfd);
    // pthread_cancel(tcp_thread);
    // pthread_cancel(uart_thread);
    printf("pthread cancel\n");
    return 0;
}
void *thrd_func_tcp_callback(void *arg)//thread_server_to_c2000_to_dongle回调函数
{
	while (1)
	{
		gy_server_to_c2000_to_dongle();
		sleep(5);
	}
	pthread_exit(NULL);
}

void *thrd_func_uart_callback(void *arg)//thread_dongle_to_c2000_to_server回调函数
{
	while (1)
	{
		int n = dongle_to_c2000();//接收dongle发送给c2000的数据
		if (n > 0)
		{
			int m = send(sockfd, uart_buff, n, 0);
			if (m <= 0)
			{
				perror("send fail!");
			}else
            {
                printf("socket send[%4u]:uart_buff = %s\n",m, Hex2Str(uart_buff,strlen(uart_buff)));
            }
		}
	}
}

void *thrd_func_time_callback(void *arg)//thread_dongle_to_c2000_to_server回调函数
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
}