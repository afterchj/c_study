
#include "main.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.lib

#define BUF_SIZE 50

int main(){

    // char source[100]="77011265FFFFFFFF2A00000000C000373700000000CCCC\0";
    // unsigned char * src= Str2Hex(source,strlen(source));
    // printf("Str2Hex=%s\n",src); 
	// printf("---------------separate-------------\n");
    // unsigned char * str = Hex2Str(src,strlen(src));
    // printf("HexToStr=%s\n",str); 
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // 创建套接字
    SOCKADDR_IN sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");   sockAddr.sin_port = htons(8001);

    char bufSend[BUF_SIZE]={0};
    char bufRecv[BUF_SIZE] = {0};

    while (1) {
        // 创建套接字
        SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        // 连接服务器
        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        // 获取用户输入的字符串并发送给服务器
        // printf("Input a string:");
        // strcpy(bufSend,"770103153737CCCC");
        unsigned char src[]="77010A65FFFFFFFFFE00000000CCCC";
        // unsigned char * dest=HexArrayToString(src,strlen(src));
        // gets(bufSend);
        // unsigned char * src= Str2Hex(bufSend,strlen(bufSend));
        // printf("Str2Hex=%s\n",src); 
        send(sock, src, BUF_SIZE, 0);
        // 接受服务器传回来的消息
        while(recv(sock, bufRecv, BUF_SIZE, 0)>0){
            unsigned char server_to_c2000_to_dongle_buf_hex[128];
            printf("Message form server: %s\n", bufRecv);
            int gy_i = 0;
            for(; gy_i<strlen(bufRecv); gy_i++)
            {
                if (gy_i%2==0)
                {
                    server_to_c2000_to_dongle_buf_hex[gy_i / 2] = two_char_to_BYTE(&bufRecv[gy_i]);//将两个连续的字符转换为16进制
                    printf("%02x ", server_to_c2000_to_dongle_buf_hex[gy_i / 2]);
                }
            }
            printf("\n");
            unsigned char * str = HexArrayToString(server_to_c2000_to_dongle_buf_hex,strlen(bufRecv),bufRecv);
            printf("HexToStr=%s\n",str); 	
        }
        // 重置缓冲区
        memset(bufSend, 0, BUF_SIZE);
        memset(bufRecv, 0, BUF_SIZE);
        // 关闭套接字
        closesocket(sock);
    }

    // 终止DLL使用
    WSACleanup();
    return 0;
}