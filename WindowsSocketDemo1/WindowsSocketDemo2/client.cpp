#include "stdio.h"
#include "winsock2.h"

#pragma comment (lib, "ws2_32.lib")

int main()
{
	//��ʼ��dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
	//�����׽���
	SOCKET clnSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clnSocket == INVALID_SOCKET)
	{
		printf("socket error!");
		return 0;
	}

	//���׽��� bind
	sockaddr_in sockAddr;
	sockAddr.sin_family = PF_INET;//IPv4
	sockAddr.sin_port = htons(1234);//�˿�
	sockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//����IP��ַ

	//connet ���ӷ�����
	connect(clnSocket, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//���ܷ��������ص�����
	char szBuffer[MAXBYTE] = { 0 };
	recv(clnSocket, szBuffer, MAXBYTE, NULL);
	/************************************************************************/
	/*̨ʽ����ע��20190528                                                                      */
	/************************************************************************/
	printf("Message form server :%s\n", szBuffer);
	closesocket(clnSocket);
	WSACleanup();
	system("pause");
	return 0;
}