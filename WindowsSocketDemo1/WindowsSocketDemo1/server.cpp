#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

int main(){
	/************************************************************************/
	/* 台式机新加注释20190528                                                                     */
	/************************************************************************/
	//初始化 DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//创建TCP套接字
	//SOCKET sockSock = socket(AF_INET, SOCK_DGRAM, 0); //创建UDP套接字

	//绑定套接字
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;  //使用IPv4地址
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	sockAddr.sin_port = htons(1234);  //端口
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));//创建套接字后服务器需要bind函数将套接字与特定的IP地址和端口地址绑定起来，
	//只有这样，流经IP地址和端口的数据才能交给套接字处理

	//进入监听状态
	listen(servSock, 20);

	//接收客户端请求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

	//向客户端发送数据
	char *str = "Hello World!";
	send(clntSock, str, strlen(str) + sizeof(char), NULL);

	//关闭套接字
	closesocket(clntSock);
	closesocket(servSock);

	//终止 DLL 的使用
	WSACleanup();

	return 0;
}
