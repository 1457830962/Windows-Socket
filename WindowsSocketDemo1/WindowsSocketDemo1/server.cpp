#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll

int main(){
	/************************************************************************/
	/* ̨ʽ���¼�ע��20190528                                                                     */
	/************************************************************************/
	//��ʼ�� DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//����TCP�׽���
	//SOCKET sockSock = socket(AF_INET, SOCK_DGRAM, 0); //����UDP�׽���

	//���׽���
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
	sockAddr.sin_port = htons(1234);  //�˿�
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));//�����׽��ֺ��������Ҫbind�������׽������ض���IP��ַ�Ͷ˿ڵ�ַ��������
	//ֻ������������IP��ַ�Ͷ˿ڵ����ݲ��ܽ����׽��ִ���

	//�������״̬
	listen(servSock, 20);

	//���տͻ�������
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

	//��ͻ��˷�������
	char *str = "Hello World!";
	send(clntSock, str, strlen(str) + sizeof(char), NULL);

	//�ر��׽���
	closesocket(clntSock);
	closesocket(servSock);

	//��ֹ DLL ��ʹ��
	WSACleanup();

	return 0;
}
