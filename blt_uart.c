/**
* @file uart.c
*/
#include "blt_main.h"

const unsigned char Num2CharTable[] = "0123456789ABCDEF";//16进制数据转换为字符串使用
//int j = 0;//record number of 0xcc
unsigned char string[BUFFSIZE];

int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)//设置串口通信
{
	struct termios newtio, oldtio;
	if (tcgetattr(fd, &oldtio) != 0) {
		perror("SetupSerial 1");
		return -1;
	}
	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag |= CLOCAL | CREAD; //CLOCAL:忽略modem控制线  CREAD：打开接受者
	newtio.c_cflag &= ~CSIZE; //字符长度掩码。取值为：CS5，CS6，CS7或CS8

	switch (nBits)
	{
	case 7:
		newtio.c_cflag |= CS7;
		break;
	case 8:
		newtio.c_cflag |= CS8;
		break;
	}

	switch (nEvent)
	{
	case 'O':
		newtio.c_cflag |= PARENB; //允许输出产生奇偶信息以及输入到奇偶校验
		newtio.c_cflag |= PARODD;  //输入和输出是奇及校验
		newtio.c_iflag |= (INPCK | ISTRIP); // INPACK:启用输入奇偶检测；ISTRIP：去掉第八位
		break;
	case 'E':
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N':
		newtio.c_cflag &= ~PARENB;
		break;
	}

	switch (nSpeed)
	{
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
		break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
		break;
	case 9600:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		break;
	case 460800:
		cfsetispeed(&newtio, B460800);
		cfsetospeed(&newtio, B460800);
		break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	}

	if (nStop == 1)
		newtio.c_cflag &= ~CSTOPB; //CSTOPB:设置两个停止位，而不是一个
	else if (nStop == 2)
		newtio.c_cflag |= CSTOPB;

	newtio.c_cc[VTIME] = 0; //VTIME:非cannoical模式读时的延时，以十分之一秒位单位
	newtio.c_cc[VMIN] = 0; //VMIN:非canonical模式读到最小字符数
	tcflush(fd, TCIFLUSH); // 改变在所有写入 fd 引用的对象的输出都被传输后生效，所有已接受但未读入的输入都在改变发生前丢弃。
	if ((tcsetattr(fd, TCSANOW, &newtio)) != 0) //TCSANOW:改变立即发生
	{
		perror("com set error");
		return -1;
	}
	return 0;
}
 
/*打开串口函数*/
void uart_init(void)//串口初始化
{
	while (1)
	{
		uart_close();
		//sleep(1);
		uartfd = open("/dev/ttyUSB1", O_RDWR);
        // uartfd = open("/dev/ttyUSB1", O_RDWR);
		if (uartfd < 0)
		{
			//printf("open ttyS1 error!\n");
			perror("open fail!");
			//	exit(1);
			continue;
		}
		int nset = set_opt(uartfd, 9600, 8, 'N', 1);
		if (nset == -1)
		{
			//printf("set opt error!\n");
			perror("set_opt");
			//	exit(1);
			continue;
		}
		//bzero(hilink_to_dongle_buf, sizeof(hilink_to_dongle_buf));
		bzero(uart_buff, sizeof(uart_buff));
		break;
	}
}

//十六进制转字符串函数
unsigned char* Hex2Str(const char * hexarray, int length)
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

int dongle_to_c2000(void)//接收dongle发送给c2000的数据
{
	bzero(uart_buff, sizeof(uart_buff));
	int nread = read(uartfd, uart_buff, BUFFSIZE);
	// if (nread > 0) {
	// 	printf("uartfd read[%4u]:uart_buff = %s\n",nread, Hex2Str(uart_buff,strlen(uart_buff)));
	// }
	return nread;
}

void uart_close(void)//串口关闭
{
	close(uartfd);
}