
// MachineCodeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MachineCode.h"
#include "MachineCodeDlg.h"
#include "afxdialogex.h"
#include <WinSock2.h> 
#include "NarutoFunc.h"
#include<string>
#include <streambuf>
using namespace std;
#pragma comment(lib, "ws2_32.lib") 
#define IDC_EDIT_MACHINE_CODE  1005
#define IDC_EDIT_PASSWORD      1006	
#define IDC_BUTTON_LOGIN       1007	

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedOk();
	//afx_msg void OnBnClickedButtonLogin();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
	//ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CAboutDlg::OnBnClickedButtonLogin)
END_MESSAGE_MAP()


// CMachineCodeDlg 对话框



CMachineCodeDlg::CMachineCodeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MACHINECODE_DIALOG, pParent)
	, m_tip(_T("请先联系\r\nqq1054628060\r\n注册")) {
	Chwi.Read();
	 m_machineCode = Chwi.m_strMACAddress+Chwi.m_strBIOSSerialNumber;
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMachineCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MACHINE_CODE, m_machineCode);

	DDX_Text(pDX, IDC_TIP, m_tip);
}

BEGIN_MESSAGE_MAP(CMachineCodeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CMachineCodeDlg::OnBnClickedButtonLogin)
	//ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CMachineCodeDlg::OnBnClickedButtonLogin)
	//ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CMachineCodeDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CMachineCodeDlg::OnBnClickedButtonLogin)
	ON_WM_KEYDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CMachineCodeDlg 消息处理程序

BOOL CMachineCodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMachineCodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMachineCodeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMachineCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMachineCodeDlg::OnBnClickedButtonLogin() {
	//建立连接
	//char sendBuf[512];
	CString sendStr;	
	WORD wVersion;
	WSADATA wsaData;
	int err; 
	wVersion = MAKEWORD(1, 1);
	err = WSAStartup(wVersion, &wsaData);
	if (err != 0) { return ; }
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup(); return;
	}
	// 创建tcp套接字 
	SOCKET sockCli = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.0.106");//服务器地址127.0.0.1是本机
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);//端口
	//向服务器发起连接请求 
	connect(sockCli, (SOCKADDR*)& addrSrv, sizeof(SOCKADDR));	
	//std::cout << recvBuf << std::endl;
		
	//获取文本框内容
	//CString passwordText;
	//CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_PASSWORD);
	////edit->GetWindowTextW(passwordText);//Unicode字符集
	//edit->GetWindowTextA(passwordText);//多字节字符集
	/*if (m_machineCode!="80-C5-F2-D1-A5-B7AT/AT COMPATIBLE _ASUS_ - 1072009") {
		MessageBox(_T("登陆失败"));
	}*/
	//if (passwordText =="123456") {
	 //发送数据 
		sendStr = m_machineCode;//
		 char *buff;          
         buff=sendStr.GetBuffer(sendStr.GetLength()); //CString到缓冲区
          
		//sprintf_s(sendBuf, sizeof(sendStr), (const char*)&sendStr);//字符串转字符数组
		send(sockCli, buff, strlen(sendStr)+1, 0);//发送
	sendStr.ReleaseBuffer();
		MessageBox(_T("发送成功"));
		/*time_t end; time(&end); CString str1;
		str1.Format("%d", end);
		MessageBox(_T(str1));*/
		//// 接收数据 
		char recvBuf[24]; //time_t start; time(&start);
		recv(sockCli, recvBuf, sizeof(recvBuf), 0);
		string recvStr = recvBuf;
		if (recvStr.compare(0,1,"1",0,1)==0) {
			MessageBox(_T("登录成功"));
			NarutoFunc nf;
			nf.DoModal();
		}
		
		/*CString str;
		str.Format("%d", start);
		MessageBox(_T(str));*/
	//}
	/*else {
		MessageBox(_T("登陆失败"));
	}*/// 关闭套接字 
		closesocket(sockCli);
		WSACleanup();
			

}


