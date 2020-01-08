#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.lib

#define BUF_SIZE 50

int main(){
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // 创建套接字
    SOCKADDR_IN sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("10.10.11.60");   sockAddr.sin_port = htons(8001);

    char bufSend[BUF_SIZE] = {0};
    char bufRecv[BUF_SIZE] = {0};

    while (1) {
        // 创建套接字
        SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        // 连接服务器
        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        // 获取用户输入的字符串并发送给服务器
        printf("Input a string:");
        gets(bufSend);
        send(sock, bufSend, BUF_SIZE, 0);
        // 接受服务器传回来的消息
        while(recv(sock, bufRecv, BUF_SIZE, 0)>0){
            printf("Message form server: %s\n", bufRecv);
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