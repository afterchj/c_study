#include <stdio.h>
#include <WinSock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.lib
#define BUF_SIZE 100

int main() {
    //
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    // 创建套接字
    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);

    // 绑定套接字
    SOCKADDR_IN sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(9080);
    bind(serverSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    // 进入监听状态
    listen(serverSock, 20);

    // 接受客户端请求
    SOCKADDR cltAddr;
    int nSize = sizeof(cltAddr);
    char buffer[BUF_SIZE] = {0};
    while(1) {
        // 阻塞直到客户端发来消息
        SOCKET clientSock = accept(serverSock, (SOCKADDR*)&cltAddr, &nSize);

        // 接受客户端消息
        int strLen = recv(clientSock, buffer, BUF_SIZE, 0);
        printf("Message form client: %s\n", buffer);

        // 给客户端回复消息      
        printf("Input a string: \n");
        gets(buffer);
        send(clientSock, buffer, strLen, 0);

        // 关闭套接字
        closesocket(clientSock);
        // 重置缓冲区
        memset(buffer, 0, BUF_SIZE);
    }

    // 关闭套接字
    closesocket(serverSock);
    // 终止DLL使用
    WSACleanup();
}