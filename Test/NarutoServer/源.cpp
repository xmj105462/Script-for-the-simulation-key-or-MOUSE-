#include <WinSock2.h> 
#include <iostream> 
#include <fstream>  
#include <sstream> 


#pragma comment(lib, "ws2_32.lib")
using namespace std;
#define SEND_SIZE 24
 bool compFile(string& recv, SOCKET& sockConn);
int main() {
	// 加载套接字库 
	WORD wVersionRequested; 
	WSADATA wsaData; 
	int err; 
	wVersionRequested = MAKEWORD(1,1); 
	// 初始化套接字库 
	err = WSAStartup(wVersionRequested, &wsaData); 
	if (err != 0) {
		return err;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup(); 
		return -1;
	}
	// 新建套接字 
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0); 
	SOCKADDR_IN addrSrv; 
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET; 
	addrSrv.sin_port = htons(6000); // 绑定套接字到本地IP地址，端口号6000 
	bind(sockSrv, (SOCKADDR*)& addrSrv, sizeof(SOCKADDR)); 
	// 开始监听 
	listen(sockSrv, 5); 
	SOCKADDR_IN addrCli; 
	int len = sizeof(SOCKADDR); 
	while (true) {// 接收客户连接 
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)& addrCli, &len);
		/*char sendBuf[512]; 
		sprintf_s(sendBuf, sizeof(sendBuf), "Welcome %s to qiniu!", inet_ntoa(addrCli.sin_addr));*/ 
		//发送数据 
		//send(sockConn, sendBuf, strlen(sendBuf) + 1, 0); 
		char recvBuf[512]; //接收数据 
		recv(sockConn, recvBuf, sizeof(recvBuf), 0); 
		//打印接收的数据
		string recv = recvBuf;
		std::cout << recvBuf<<std::endl;
		compFile(recv,sockConn);//逐行读取文件内容比对是否注册，是就登录成功
		/*size_t compStrLength;
		string compStr = "80-C5-F2-D1-A5-B7AT/AT COMPATIBLE _ASUS_ - 1072009";
		compStrLength = compStr.size();*/
		//char recvComp[512]= "80 - C5 - F2 - D1 - A5 - B7AT / AT COMPATIBLE _ASUS_ - 1072009123456\0";
		//if (recv.compare(0,compStrLength,compStr, 0, compStrLength)==0) {
		//	/*char sendBuf[SEND_SIZE];
		//	sprintf_s(sendBuf, sizeof("1"), "1");*///, inet_ntoa(addrCli.sin_addr) 
		//		//发送数据 
		//	send(sockConn, "1", strlen("1") + 1, 0);
		//	std::cout << "登陆成功" << std::endl;
		//}
		//else {
		//	std::cout << "登陆失败" << std::endl;
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
	fopen_s(&compFile, "compStr.txt", "r");//读取
	if (compFile) {
		printf("找到文件.\n");
		string filename = "compStr.txt";
		fstream fin;
		fin.open(filename.c_str(), ios::in);
		string compStr;
		while (getline(fin, compStr)) {
			cout << "读取到"<< compStr << endl;
			size_t compStrLength;			
			compStrLength = compStr.size();
			if (recv.compare(0, compStrLength, compStr, 0, compStrLength) == 0) {				 
				//发送数据 
				send(sockConn, "1", strlen("1") + 1, 0);
				std::cout << "登陆成功" << std::endl;
				return true;
			}
			else {
				std::cout << "登陆失败" << std::endl;
			}
		}		
	}
	else {
		printf("没有找到文件.\n");		
	}
	return false;
}
