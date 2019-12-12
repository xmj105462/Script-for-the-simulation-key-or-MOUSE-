#include <WinSock2.h> 
#include <iostream> 
#include <fstream>  
#include <sstream> 


#pragma comment(lib, "ws2_32.lib")
using namespace std;
#define SEND_SIZE 24
 bool compFile(string& recv, SOCKET& sockConn);
int main() {
	// �����׽��ֿ� 
	WORD wVersionRequested; 
	WSADATA wsaData; 
	int err; 
	wVersionRequested = MAKEWORD(1,1); 
	// ��ʼ���׽��ֿ� 
	err = WSAStartup(wVersionRequested, &wsaData); 
	if (err != 0) {
		return err;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup(); 
		return -1;
	}
	// �½��׽��� 
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0); 
	SOCKADDR_IN addrSrv; 
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET; 
	addrSrv.sin_port = htons(6000); // ���׽��ֵ�����IP��ַ���˿ں�6000 
	bind(sockSrv, (SOCKADDR*)& addrSrv, sizeof(SOCKADDR)); 
	// ��ʼ���� 
	listen(sockSrv, 5); 
	SOCKADDR_IN addrCli; 
	int len = sizeof(SOCKADDR); 
	while (true) {// ���տͻ����� 
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)& addrCli, &len);
		/*char sendBuf[512]; 
		sprintf_s(sendBuf, sizeof(sendBuf), "Welcome %s to qiniu!", inet_ntoa(addrCli.sin_addr));*/ 
		//�������� 
		//send(sockConn, sendBuf, strlen(sendBuf) + 1, 0); 
		char recvBuf[512]; //�������� 
		recv(sockConn, recvBuf, sizeof(recvBuf), 0); 
		//��ӡ���յ�����
		string recv = recvBuf;
		std::cout << recvBuf<<std::endl;
		compFile(recv,sockConn);//���ж�ȡ�ļ����ݱȶ��Ƿ�ע�ᣬ�Ǿ͵�¼�ɹ�
		/*size_t compStrLength;
		string compStr = "80-C5-F2-D1-A5-B7AT/AT COMPATIBLE _ASUS_ - 1072009";
		compStrLength = compStr.size();*/
		//char recvComp[512]= "80 - C5 - F2 - D1 - A5 - B7AT / AT COMPATIBLE _ASUS_ - 1072009123456\0";
		//if (recv.compare(0,compStrLength,compStr, 0, compStrLength)==0) {
		//	/*char sendBuf[SEND_SIZE];
		//	sprintf_s(sendBuf, sizeof("1"), "1");*///, inet_ntoa(addrCli.sin_addr) 
		//		//�������� 
		//	send(sockConn, "1", strlen("1") + 1, 0);
		//	std::cout << "��½�ɹ�" << std::endl;
		//}
		//else {
		//	std::cout << "��½ʧ��" << std::endl;
		//}
		closesocket(sockConn); 
	}
	closesocket(sockSrv);
	//closesocket(sockSrv); 
	WSACleanup(); 
	return 0;
}

 bool compFile(string& recv,SOCKET& sockConn) {
	FILE* compFile;
	fopen_s(&compFile, "compStr.txt", "r");//��ȡ
	if (compFile) {
		printf("�ҵ��ļ�.\n");
		string filename = "compStr.txt";
		fstream fin;
		fin.open(filename.c_str(), ios::in);
		string compStr;
		while (getline(fin, compStr)) {
			cout << "��ȡ��"<< compStr << endl;
			size_t compStrLength;			
			compStrLength = compStr.size();
			if (recv.compare(0, compStrLength, compStr, 0, compStrLength) == 0) {				 
				//�������� 
				send(sockConn, "1", strlen("1") + 1, 0);
				std::cout << "��½�ɹ�" << std::endl;
				return true;
			}
			else {
				std::cout << "��½ʧ��" << std::endl;
			}
		}		
	}
	else {
		printf("û���ҵ��ļ�.\n");		
	}
	return false;
}
