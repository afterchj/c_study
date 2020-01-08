/*******net********/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/******uart*******/
#include <termios.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>

/******check_8001_net******/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>

#define BUFFSIZE  128

/******************************blt_tcp.c************************************/
extern void checknet(void);//检查网络是否正常，main函数中的网络初始化
extern void gy_set_sockfd(void);//设置tcp通信的描述符：gy_c2000_sockfd
extern void gy_server_to_c2000_to_dongle(void);

extern int sockfd;//c2000上传数据和接收数据使用的描述符
extern int uartfd;//c2000串口描述符
extern int stop_flag;

unsigned char uart_buff[BUFFSIZE];//dongle发送过来的16进制数据保存到该位置
unsigned char tcp_buff[BUFFSIZE];//server发送过来的16进制数据保存到该位置

//主函数入口：网络初始化、串口初始化、相关线程初始化（BLE-C2000-SERVER、SERVER-C2000-BLE）、串口关闭、线程回收
extern void *thrd_func_tcp_callback(void *arg);//thread_server_to_c2000_to_dongle回调函数
extern void *thrd_func_uart_callback(void *arg);//thread_dongle_to_c2000_to_server回调函数
//十六进制转字符串函数
unsigned char* Hex2Str(const char * hexarray, int length);
extern int main(int argc, const char *argv[]);
/*****************************blt_uart.c***************************************/
extern void uart_init(void);//串口初始化
extern void uart_close(void);//串口关闭
extern int dongle_to_c2000(void);//接收dongle发送给c2000的数据
