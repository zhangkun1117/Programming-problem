
/**
 * socket 服务器实现
 * 1：加载套接字库，创建套接字(WSAStartup()/socket())；
 * 2：绑定套接字到一个IP地址和一个端口上(bind())；
 * 3：将套接字设置为监听模式等待连接请求(listen())；
 * 4：请求到来后，接受连接请求，返回一个新的对应于此次连接的套接字(accept())；
 * 5：用返回的套接字和客户端进行通信(send()/recv())；
 * 6：返回，等待另一连接请求；
 * 7：关闭套接字，关闭加载的套接字库(closesocket()/WSACleanup())。
 * */
#include <Winsock2.h>
#include <cstdio>
#pragma comment(lib,"ws2_32.lib")
void main()
{
    WSADATA wsaData;
    SOCKET sockServer;
    SOCKADDR_IN addrServer;
    SOCKET sockClient;
    SOCKADDR_IN addrClient;
    WSAStartup(MAKEWORD(2,2),&wsaData);
    sockServer=socket(AF_INET,SOCK_STREAM,0);
    addrServer.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//INADDR_ANY表示任何IP
    addrServer.sin_family=AF_INET;
    addrServer.sin_port=htons(6000);//绑定端口6000
    bind(sockServer,(SOCKADDR*)&addrServer,sizeof(SOCKADDR));

    //Listen监听端
    listen(sockServer,5);//5为等待连接数目
    printf("服务器已启动:\n监听中...\n");
    int len=sizeof(SOCKADDR);
    charsendBuf[100];//发送至客户端的字符串
    charrecvBuf[100];//接受客户端返回的字符串

    //会阻塞进程，直到有客户端连接上来为止
    sockClient=accept(sockServer,(SOCKADDR*)&addrClient,&len);
    //接收并打印客户端数据
    recv(sockClient,recvBuf,100,0);
    printf("%s\n",recvBuf);

    //关闭socket
    closesocket(sockClient);
    WSACleanup();
}

/**
 * 
 * 客户端编程的步骤：
 * 1：加载套接字库，创建套接字(WSAStartup()/socket())；
 * 2：向服务器发出连接请求(connect())；
 * 3：和服务器端进行通信(send()/recv())；
 * 4：关闭套接字，关闭加载的套接字库(closesocket()/WSACleanup())
 * */
#include <Winsock2.h>
#include <cstdio>
#pragma comment(lib,"ws2_32.lib")
void main()
{
    WSADATA wsaData;
    SOCKET sockClient;//客户端Socket
    SOCKADDR_IN addrServer;//服务端地址
    WSAStartup(MAKEWORD(2,2),&wsaData);
    //新建客户端socket
    sockClient=socket(AF_INET,SOCK_STREAM,0);
    //定义要连接的服务端地址
    addrServer.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//目标IP(127.0.0.1是回送地址)
    addrServer.sin_family=AF_INET;
    addrServer.sin_port=htons(6000);//连接端口6000
    //连接到服务端
    connect(sockClient,(SOCKADDR*)&addrServer,sizeof(SOCKADDR));
    //发送数据
    char message[20]="HelloSocket!";
    send(sockClient,message,strlen(message)+1,0);
    //关闭socket
    closesocket(sockClient);
    WSACleanup();
}