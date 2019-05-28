#include "stdio.h"
#include "winsock2.h"

#pragma comment (lib, "ws2_32.lib")

int main()
{
	//初始化dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
	//创建套接字
	SOCKET clnSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clnSocket == INVALID_SOCKET)
	{
		printf("socket error!");
		return 0;
	}

	//绑定套接字 bind
	sockaddr_in sockAddr;
	sockAddr.sin_family = PF_INET;//IPv4
	sockAddr.sin_port = htons(1234);//端口
	sockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//具体IP地址

	//connet 连接服务器
	connect(clnSocket, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//接受服务器传回的数据
	char szBuffer[MAXBYTE] = { 0 };
	recv(clnSocket, szBuffer, MAXBYTE, NULL);
	/************************************************************************/
	/*台式机上注释20190528                                                                      */
	/************************************************************************/
	printf("Message form server :%s\n", szBuffer);
	closesocket(clnSocket);
	WSACleanup();
	system("pause");
	return 0;
}