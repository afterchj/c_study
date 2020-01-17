#include "blt_main.h"

int sockfd;
int uartfd;
#define TIME_OUT_PORT_8003 25//设置接收超时时间
#define SERVER_PORT 8001//8003
#define SERV_IP_ADDR "192.168.3.108"/*"192.168.1.199"*//*"122.112.229.195"*/

void checknet(void)//检查网络是否正常，main函数中的网络初始化
{
	printf("check net start!!\n");
	struct sockaddr_in servaddr;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(-1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_addr.s_addr = inet_addr(SERV_IP_ADDR);

	while (1)
	{
		sleep(1);
		if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
		{
			perror("socket");
		}
		else
		{
			printf("network success !\n");
			close(sockfd);
			break;
		}
		printf("check network ...\n");
	}

	return;
}

void gy_set_sockfd(void)//设置tcp通信的描述符：gy_c2000_sockfd
{
	while (1)
	{
		sleep(1);
		close(sockfd);
		struct sockaddr_in servaddr;
		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
			perror("socket1");
			//	exit(-1);
			printf("设置TCP通信描述符失败！！\n");
			continue;
		}

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(SERVER_PORT);
		servaddr.sin_addr.s_addr = inet_addr(SERV_IP_ADDR);

		if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
		{
			perror("sockfd");
			//exit(-1);
			close(sockfd);
			printf("连接服务器失败，设置TCP通信描述符失败！！\n");
			continue;
		}
		break;
	}
	return;
}

void gy_server_to_c2000_to_dongle(void)
{
	signal(SIGALRM, sig_handler);
	while (1)
	{
		struct timeval timeout = { TIME_OUT_PORT_8003,0 };//接收数据超时时间设置

		//设置接收超时
		//setsockopt(gy_c2000_sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));
 		FILE *fp;
		memset(tcp_buff,0, BUFFSIZE);
		int n = recv(sockfd, tcp_buff, BUFFSIZE, 0);
		char dest[7]={0};
		strncpy(dest,tcp_buff,6);
		// printf("result=%s,flag=%d\n",dest,strcmp("770107",dest));
		if(strcmp("770107",dest)==0)
		{
			if( (fp=fopen("./time.txt", "at+")) == NULL )
			{
				puts("Fail to open file!");
				exit(0);
    		}
			fputs(tcp_buff, fp);
    		fclose(fp);
		}
		if (n > 0)
		{
			printf("socket receive[%4u]:server_to_c2000_to_dongle_buf = %s\n",n, tcp_buff);
			uart_init();//串口初始化
			int ret = write(uartfd, tcp_buff, n);//将接收到的服务器发送过来的数据下发至dongle
			if (ret == -1)
			{
				perror("write");
				uart_init();//if uart error,open uart again
				write(uartfd, tcp_buff, n);
			}
		}
		else if(n == 0)//如果tcp连接断开，重新连接
		{
			perror("socket_recv");
			printf("socket_recv: n = %d\n",n);
			gy_set_sockfd();//设置tcp通信的描述符：gy_c2000_sockfd
		}
	}

	return;
}

// int main(int argc, const char *argv[])
// {
//     printf("main start!!\n");
// 	checknet();//检查网络是否正常，main函数中的网络初始化
// 	gy_set_sockfd();//设置tcp通信的描述符：gy_c2000_sockfd
//     gy_server_to_c2000_to_dongle();
//     return 0;
// }