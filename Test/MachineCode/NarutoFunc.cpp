// NarutoFunc.cpp: 实现文件
//

#include "pch.h"
#include "MachineCode.h"
#include "NarutoFunc.h"
#include "afxdialogex.h"
#include<Windows.h>
#include<afxwin.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
constexpr auto GROUP_PIXEL = 5;
constexpr auto POINT_ARR_COUNT = 60;
using namespace std;
typedef struct MyPoint {
	int x; int y;
	MyPoint() {
		x = 0; y = 0;
	}
	MyPoint(int a, int b) {
		x = a; y = b;
	}
}MP;
typedef struct MyAreaFindPixel {
	RECT findArea;
	COLORREF color1;
	COLORREF color2;
	int timeLay;
	MyAreaFindPixel() {
		findArea.left = 0; findArea.bottom = 0;
		findArea.right = 0; findArea.top = 0;
		color1 = 0; color2 = 0; timeLay = 0;
	}
	MyAreaFindPixel(int left, int top,int right, int bottom,BYTE r1, BYTE g1, BYTE b1, BYTE r2, BYTE g2, BYTE b2,int timeLay) {
		findArea.left = left;
		findArea.top = top;
		findArea.right = right;
		findArea.bottom = bottom;
		 color1=(RGB(r1, g1, b1));
		 color2=(RGB(r2, g2, b2));
		 this->timeLay = timeLay;
	}
}Mafp;
inline size_t writePointToFile(MP , std::string , char* );
inline void getFilePoint(char* , std::vector<string>& , std::vector<string>& ,MP&);
inline void getFilePoint2(char*, std::vector<string>&,MP&,int&);
inline void getLoopNumber(char*, std::vector<string>&,int&);
inline HBITMAP CopyScreenToBitmap2(LPRECT );
vector<string> split(const string& str, const string& delim);
//T1-T4为矩形左上右下，T5-T10两个颜色值T11写入字符串
#define FIND_PIXEL(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11)  Rect.left =T1 ;\
Rect.top = T2;\
Rect.right =T3 ; Rect.bottom = T4;\
 findColor1=(RGB(T5,T6,T7));\
 findColor2=(RGB(T8,T9,T10));\
 loginP = areaFindPixel(loginLPrect, loginColor1, loginColor2);\
 conChilk=false;\
if(loginP.x!=0){writePointToFile(loginP,T11,fileName);conChilk=true;}\
Sleep(100);
//点数组点击 
#define POINT_ARR_CHILK(T1,T2) chilk(pointArr[T1].x, pointArr[T1].y);Sleep(T2*1000);
//找色点击数据采集
//#define FIND_PIXEL_DATE(T1,T2) const char* sToi = res4[T1].c_str();int T2 = atoi(sToi);
IMPLEMENT_DYNAMIC(NarutoFunc, CDialogEx)
inline void chilkDrag(int , int  , int );
inline void fengrao();
inline void zuzhiliaotian();
inline void denglu_meiriqiandao();
inline void bamendunjia();
inline void jiayuan();
inline void tongji();
inline void shengcun();
inline void guandiaosc();
inline void huanfu();

//bool imageDateComp(CString fileName, LPRECT compRectPtr);
NarutoFunc::NarutoFunc(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FUNC, pParent)
	, m_ok_or_cancel(FALSE), m_if_zd(FALSE), m_if_sc(FALSE), m_if_linshi(FALSE) {
	m_narutoHWND = ::FindWindow(_T("MainView_9F956014-12FC-42d8-80C7-9A90D4D567E3"), _T("火影忍者Online"));
	/*m_x = 0;
	m_pos_y = 0;*/
	m_ok_or_cancel = 0;
	m_if_zd = false; m_if_sc = false; m_if_linshi = FALSE;
	//获取屏幕宽度和高度
		m_xScreen = GetSystemMetrics(SM_CXSCREEN);
		m_yScreen = GetSystemMetrics(SM_CYSCREEN);
		right = (float)m_xScreen; bottom = (float)m_yScreen;
		rightScale = right / GROUP_PIXEL;
		bottomScale = bottom / GROUP_PIXEL;
		// m_pFSBitmap=NULL;
	//设备上下文贴图
	/*hdc = ::GetDC(m_narutoHWND);
	mdc = CreateCompatibleDC(hdc);
	bdc = CreateCompatibleDC(hdc);
	bmp = CreateCompatibleBitmap(hdc, 1920, 1030);
	manBmp = (HBITMAP)LoadImage(NULL, _T("man.bmp"), IMAGE_BITMAP, 1920, 1030, LR_LOADFROMFILE);
	SelectObject(mdc, bmp);*/
}

NarutoFunc::~NarutoFunc()
{
}

void NarutoFunc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_QZ, m_ok_or_cancel);
	DDX_Check(pDX, IDC_CHECK_ZD, m_if_zd);
	DDX_Check(pDX, IDC_CHECK_SC, m_if_sc);
	DDX_Check(pDX, IDC_CHECK1, m_if_linshi);
}


BEGIN_MESSAGE_MAP(NarutoFunc, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_QZ, &NarutoFunc::OnBnClickedCheckQz)
	ON_BN_CLICKED(IDC_CHECK_ZD, &NarutoFunc::OnBnClickedCheckZd)
	ON_BN_CLICKED(IDC_CHECK_SC, &NarutoFunc::OnBnClickedCheckSc)
	ON_BN_CLICKED(IDC_CHECK_FY, &NarutoFunc::OnBnClickedCheckFy)
	ON_BN_CLICKED(IDC_CHECK_PR, &NarutoFunc::OnBnClickedCheckPr)
	ON_BN_CLICKED(IDC_CHECK_JB, &NarutoFunc::OnBnClickedCheckJb)
	ON_BN_CLICKED(IDC_CHECK_JBZS, &NarutoFunc::OnBnClickedCheckJbzs)
	ON_BN_CLICKED(IDC_CHECK_DD, &NarutoFunc::OnBnClickedCheckDd)
	ON_BN_CLICKED(IDC_CHECK_XJ, &NarutoFunc::OnBnClickedCheckXj)
	ON_BN_CLICKED(IDC_CHECK1, &NarutoFunc::OnBnClickedCheck1)
END_MESSAGE_MAP()


// NarutoFunc 消息处理程序

inline void chilk(int x,int y);
void NarutoFunc::OnBnClickedCheckQz() {//达摩挑战
	++m_ok_or_cancel;
	m_ok_or_cancel = m_ok_or_cancel % 2;
	if (TRUE==m_ok_or_cancel) {
		//获取火影窗口
		findWindow(m_narutoHWND);
		::ShowWindow(m_narutoHWND, SW_MAXIMIZE);//最大化 hwnd 所代表的窗口
		Sleep(3000);		
		chilk(633, 197);//限时活动
		RECT loginRect; LPRECT loginLPrect = &loginRect;
		COLORREF color1(RGB(200, 153, 37));
		loginRect.left = 1062;
		loginRect.top = 847;
		loginRect.right = 1068; loginRect.bottom = 886;
		BYTE red1 = GetRValue(color1);
		size_t chilkCount = 0;
		Sleep(2500);
		chilk(490, 695); Sleep(2000);//周末活动
		chilk(1339, 657); Sleep(2500);//骰子手气王
		for (int i=0;i<3;++i){
			chilk(944, 633); Sleep(5000);//掷骰子
		}
		chilk(1423, 878); Sleep(3000);//返回
		chilk(1341, 798); Sleep(2000);//达摩挑战1
		chilk(1085, 633); Sleep(3000);//达摩开始				
		BYTE pBits[36]; HBITMAP findHBitmap; CBitmap bmp; BITMAP BitMap; //BYTE red = 0;
		while (true) {
			findHBitmap = CopyScreenToBitmap2(loginLPrect);			
			bmp.Attach(findHBitmap);
			bmp.GetBitmap(&BitMap);
			if (pBits)bmp.GetBitmapBits(4, pBits);
			if (pBits[2] != red1) {
				if (chilkCount%2==0){
					chilk(1251, 754); Sleep(2000);//锤子右
				} 
				else{
					chilk(887, 754); Sleep(2000);//锤子左
				}
				++chilkCount;
				if (chilkCount == 6) {
					return;
				}
			}
		}
	}
}


void NarutoFunc::OnBnClickedCheckZd() {//脚本开始
	++m_if_zd;
	m_if_zd = m_if_zd % 2;
	if (m_if_zd) {
		//findWindow(m_narutoHWND);
		//::ShowWindow(m_narutoHWND, SW_MAXIMIZE);//最大化 hwnd 所代表的窗口
		Sleep(3000);
		char fileName[] = "脚本数据.txt";
		FILE* fp;
		errno_t s32Err = ::fopen_s(&fp, fileName, "r");
		char readBuf[56];
		int* pointArr = new int[POINT_ARR_COUNT] {};//文本数据数组
		if (fp) {
			fstream out;
			out.open(fileName, ios::in);
			int pointIndex = 0;//
			int loopNumber = 0;
			int pointCount = 0;//数组中点的个数
			while (!out.eof()) {//逐行读取文件内容，数值存进数组
				out.getline(readBuf, sizeof(readBuf), '\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束							 
				if (readBuf[0] == 0) {//遇到换行结束后应该判断数组里有没数值再继续
					break;
				}
				else if (readBuf[0] == '1') {//单次点击
					std::vector<string> res1; 
					MP filePoint1(0, 0); int timeLay = 0;
					getFilePoint2(readBuf, res1,filePoint1,timeLay);
					chilk(filePoint1.x, filePoint1.y); Sleep(timeLay*200);
				}
				else if (readBuf[0] == '2') {//循环数组点击数据采集
					std::vector<string> res2; 
					MP filePoint2(0, 0); int timeLay2 = 0;
					getFilePoint2(readBuf, res2,filePoint2, timeLay2);
					pointArr[pointIndex] = filePoint2.x;
					pointArr[++pointIndex] = filePoint2.y;
					pointArr[++pointIndex] = timeLay2;
					++pointIndex; ++pointCount;
				}
				else if (readBuf[0] == '3') {//循环数组点击结束
					std::vector<string> res3; 
					getLoopNumber(readBuf,res3,loopNumber);
					for (int i = 0; i < loopNumber; ++i) {
						int point_index = 0;
						for (int j = 0; j < pointCount; ++j) {
							int x = point_index; int y = ++point_index; int timeLay = ++point_index;
							chilk(pointArr[x], pointArr[y]); Sleep(pointArr[timeLay] * 200);
							++point_index;
						}					
					}pointIndex=0; pointCount=0;
				}
				else if (readBuf[0] == '4') {//找色单次点击
					std::vector<string> res4;
					res4 = split(readBuf, " ");//第一次分割
					for (int i = 0; i < 11; ++i) {//分割数据到数组
						const char* sToi = res4[i+1].c_str();
						pointArr[i] = atoi(sToi);
					}				
					RECT findArea;
					findArea.left = pointArr[0];
					findArea.top = pointArr[1];
					findArea.right = pointArr[2];
					findArea.bottom = pointArr[3];
					COLORREF color1(RGB(pointArr[4], pointArr[5], pointArr[6]));
					COLORREF color2(RGB(pointArr[7], pointArr[8], pointArr[9]));
					LPRECT lpFindArea = &findArea;					
						areaFindPixel(lpFindArea, color1, color2); Sleep(pointArr[10] * 300);					
				}
				else if (readBuf[0] == '5') {//多色采集
					std::vector<string> res5;
					res5 = split(readBuf, " ");//第一次分割
					for (int i = 0; i < 11; ++i) {//分割数据到数组
						const char* sToi = res5[i + 1].c_str();
						pointArr[pointIndex] = atoi(sToi);
						++pointIndex; 
					}++pointCount;
				}
				else if (readBuf[0] == '6') {//找色循环点击
					std::vector<string> res6;
					res6 = split(readBuf, " ");//第一次分割
					getLoopNumber(readBuf, res6, loopNumber);
					RECT findArea; COLORREF color1; COLORREF color2;
					LPRECT lpFindArea = &findArea;
					for (int i = 0; i < loopNumber; ++i) {
						int point_index = 0;
						for (int j = 0; j < pointCount; ++j) {
							findArea.left = pointArr[point_index];							
							findArea.top = pointArr[++point_index];
							findArea.right = pointArr[++point_index];
							findArea.bottom = pointArr[++point_index];
							int r1 = ++point_index;
							int g1 = ++point_index;
							int b1 = ++point_index;
							color1 = (RGB(pointArr[r1], pointArr[g1], pointArr[b1]));
							int r2 = ++point_index;
							int g2 = ++point_index;
							int b2 = ++point_index;
							color2 = (RGB(pointArr[r2], pointArr[g2], pointArr[b2]));							
							areaFindPixel(lpFindArea, color1, color2); Sleep(pointArr[++point_index] * 300);
							++point_index;
						}
					}
				pointIndex = 0; pointCount = 0;										
				}
				else if (readBuf[0] == '7') {//寻图点击
					std::vector<string> res7;
					res7 = split(readBuf, " ");//第一次分割
					for (int i = 0; i < 5; ++i) {//分割数据到数组
						const char* sToi = res7[i + 1].c_str();
						pointArr[i] = atoi(sToi);
					}
					RECT compArea; LPRECT compLPrect = &compArea;
					compArea.left = pointArr[1];
					compArea.top = pointArr[2];
					compArea.right = pointArr[3]+1;
					compArea.bottom = pointArr[4]+1;
					switch (pointArr[0]) {
					case 1:
						if (imageDateComp("1.bmp", compLPrect)) {
							chilk(compArea.left+5, compArea.top+5);
						}
						break;
					case 2:
						if (imageDateComp("2.bmp", compLPrect)) {
							chilk(compArea.left + 5, compArea.top + 5);
						}
						break; 
					case 3:
						if (imageDateComp("3.bmp", compLPrect)) {
							chilk(compArea.left + 5, compArea.top + 5);
						}
							break;
					default:
						break;
					}
				}
			}
			out.close();
		}
	}
}
MP pointArr[130];
vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if ("" == str) return res;
	//先将要切割的字符串从string类型转换为char*类型
	char* strs = new char[str.length() + 1]; //不要忘了
	//strcpy_s(strs, str.length(),str.c_str());
	strcpy(strs, str.c_str());
	char* d = new char[delim.length() + 1];
	//strcpy_s(d, delim.length(),delim.c_str());
	strcpy(d,delim.c_str());
	char* p = strtok(strs, d);
	while (p) {
		string s = p; //分割得到的字符串转换为string类型
		res.push_back(s); //存入结果数组
		p = strtok(NULL, d);
	}
	delete[] strs; delete[] d;
	return res;
}
void NarutoFunc::OnBnClickedCheckSc() {//一键日常
	++m_if_sc;
	m_if_sc = m_if_sc % 2;
	if (m_if_sc) {
		findWindow(m_narutoHWND);
		::ShowWindow(m_narutoHWND, SW_MAXIMIZE);//最大化 hwnd 所代表的窗口
		Sleep(2000);
		char fileName[] = "一键挂机.txt";
		FILE* fp;
		errno_t s32Err = ::fopen_s(&fp, fileName, "r");
		char readBuf[56];
		if (fp) { 			
			fstream out; 			
			out.open(fileName, ios::in);
			//存储点的数组，以便直接访问点击
			size_t pointIndex = 0;
			while (!out.eof()) {//逐行读取文件内容，数值存进数组
				out.getline(readBuf, sizeof(readBuf), '\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束							 
				if (readBuf[0]==0) {//遇到换行结束后应该判断数组里有没数值再继续
					break;
				}
				std::vector<string> res; std::vector<string> res2;
				MP filePoint(0,0);
				getFilePoint(readBuf, res, res2,filePoint);
				pointArr[pointIndex] = filePoint;	
				++pointIndex;
			}
			out.close();
			Sleep(100);
			{
				denglu_meiriqiandao();
			chilk(pointArr[4].x, pointArr[4].y);//每日福利
			Sleep(2000);
			chilk(pointArr[5].x, pointArr[5].y);//小月卡
			Sleep(1500);
			//chilk(pointArr[6].x, pointArr[6].y);//大月卡
			//Sleep(1500);			
			zuzhiliaotian();
			fengrao();
			bamendunjia();
			jiayuan();			
				POINT_ARR_CHILK(37, 3)//离开家园
				POINT_ARR_CHILK(38, 5)//确定离开
					tongji();  }
			{
				POINT_ARR_CHILK(46, 2)//账号多开1
				POINT_ARR_CHILK(47, 2)//选择其他账号
				POINT_ARR_CHILK(48, 4)//选择新开账号
				POINT_ARR_CHILK(49, 5)//选择小号
				POINT_ARR_CHILK(50, 25)//登陆
				denglu_meiriqiandao();			
			zuzhiliaotian();
			fengrao();
			bamendunjia();
			jiayuan();			
			POINT_ARR_CHILK(37, 3)//离开家园
				POINT_ARR_CHILK(38, 5)//确定离开
				POINT_ARR_CHILK(51, 7)//忍者
				POINT_ARR_CHILK(52, 7)//选择小号爆发队
				chilk(pointArr[108].x, pointArr[108].y);//关闭忍者
			Sleep(20);
				POINT_ARR_CHILK(108, 3)//关闭忍者
					tongji();
			}
			{
				POINT_ARR_CHILK(53, 5)//账号多开2
				POINT_ARR_CHILK(47, 3)//选择其他账号
				POINT_ARR_CHILK(48, 4)//选择新开账号
				POINT_ARR_CHILK(49, 5)//选择小zhi
				POINT_ARR_CHILK(50, 20)//登陆
				denglu_meiriqiandao();			
			zuzhiliaotian();
			fengrao();
			bamendunjia();
			jiayuan();			
				POINT_ARR_CHILK(37, 3)//离开家园
				POINT_ARR_CHILK(38, 5)//确定离开
				POINT_ARR_CHILK(51, 7)//忍者
				POINT_ARR_CHILK(54, 8)//小只3代队
					chilk(pointArr[108].x, pointArr[108].y);//关闭忍者
				Sleep(20);
				POINT_ARR_CHILK(108, 3)//关闭忍者
				tongji(); 
				POINT_ARR_CHILK(116, 3)//小只通缉
					POINT_ARR_CHILK(45, 2)//确认通缉
		}
			Sleep(2*60*1000);//等待2分钟通缉打完
			{
				POINT_ARR_CHILK(70, 7)//大号位置				
					huanfu();
				xuanQu(2); Sleep(6000);
				denglu_meiriqiandao();			 			
			zuzhiliaotian();
			jiayuan();			
			POINT_ARR_CHILK(60, 5)//忍者受命所
				POINT_ARR_CHILK(61, 3)//领取奖励
				POINT_ARR_CHILK(62, 3)//
				POINT_ARR_CHILK(63, 3)//
				POINT_ARR_CHILK(64, 3)//委派好友1
				POINT_ARR_CHILK(67, 3)//筛选好友1
					POINT_ARR_CHILK(61, 3)//确认委派
				POINT_ARR_CHILK(65, 3)//委派好友2
				POINT_ARR_CHILK(89, 3)//筛选好友2
					POINT_ARR_CHILK(62, 3)//确认委派
				POINT_ARR_CHILK(66, 3)//委派好友3
				POINT_ARR_CHILK(90, 3)//筛选好友3
					POINT_ARR_CHILK(63, 3)//确认委派
				POINT_ARR_CHILK(109, 3)//关闭受命所
				POINT_ARR_CHILK(37, 3)//离开家园
				POINT_ARR_CHILK(38, 5)//确定离开				
				POINT_ARR_CHILK(73, 15)//转盘
				POINT_ARR_CHILK(74, 2)//跳过转盘动画				
				for (size_t i = 0; i < 7; ++i) {
					POINT_ARR_CHILK(75, 1)//开始转盘
				}
			POINT_ARR_CHILK(76, 3)//关闭转盘
				POINT_ARR_CHILK(83, 3)//离开组织
				POINT_ARR_CHILK(84, 5)//确认离开组织
				POINT_ARR_CHILK(85, 5)//副本
				POINT_ARR_CHILK(86, 3)//扫荡副本
				for (size_t i = 0; i < 7; ++i) {
					POINT_ARR_CHILK(87, 3)//扫荡5次
				}POINT_ARR_CHILK(88, 3)//关闭扫荡
						POINT_ARR_CHILK(110, 3)//关闭副本
			}
			{
				huanfu();
				xuanQu(3); Sleep(6000);
					denglu_meiriqiandao();				
				zuzhiliaotian();
				jiayuan();
				POINT_ARR_CHILK(60, 5)//忍者受命所
					POINT_ARR_CHILK(61, 3)//领取奖励
					POINT_ARR_CHILK(62, 3)//
					POINT_ARR_CHILK(63, 3)//
					POINT_ARR_CHILK(64, 3)//委派好友1
					POINT_ARR_CHILK(67, 3)//筛选好友1
					POINT_ARR_CHILK(61, 3)//确认委派
					POINT_ARR_CHILK(65, 3)//委派好友2
					POINT_ARR_CHILK(89, 3)//筛选好友2
					POINT_ARR_CHILK(62, 3)//确认委派
					POINT_ARR_CHILK(66, 3)//委派好友3
					POINT_ARR_CHILK(90, 3)//筛选好友3
					POINT_ARR_CHILK(63, 3)//确认委派
					POINT_ARR_CHILK(109, 3)//关闭受命所
					POINT_ARR_CHILK(37, 3)//离开家园
					POINT_ARR_CHILK(38, 5)//确定离开				
					POINT_ARR_CHILK(73, 15)//转盘
					POINT_ARR_CHILK(74, 2)//跳过转盘动画				
					for (size_t i = 0; i < 7; ++i) {
						POINT_ARR_CHILK(75, 1)//开始转盘
					}
				POINT_ARR_CHILK(76, 3)//关闭转盘
					POINT_ARR_CHILK(83, 3)//离开组织
					POINT_ARR_CHILK(84, 5)//确认离开组织
					POINT_ARR_CHILK(85, 5)//副本
					POINT_ARR_CHILK(86, 3)//扫荡副本
					for (size_t i = 0; i < 7; ++i) {
						POINT_ARR_CHILK(87, 3)//扫荡5次
					}POINT_ARR_CHILK(88, 3)//关闭扫荡
			}
								POINT_ARR_CHILK(110, 3)//关闭副本
							{
									POINT_ARR_CHILK(55, 3)//小号位置
										huanfu();
									xuanQu(2); Sleep(6000);
									denglu_meiriqiandao();								
								zuzhiliaotian();
								POINT_ARR_CHILK(15, 5)//选择丰饶
									POINT_ARR_CHILK(16, 3)//进入丰饶
									POINT_ARR_CHILK(59, 2)//扫荡赏金
									POINT_ARR_CHILK(18, 2)//完成扫荡
									POINT_ARR_CHILK(59, 2)//扫荡赏金
									POINT_ARR_CHILK(18, 2)//完成扫荡								
									POINT_ARR_CHILK(20, 2)//关闭丰饶
									jiayuan();
								POINT_ARR_CHILK(60, 5)//忍者受命所
									POINT_ARR_CHILK(61, 3)//领取奖励
									POINT_ARR_CHILK(62, 3)//
									POINT_ARR_CHILK(63, 3)//
									POINT_ARR_CHILK(64, 3)//委派好友1
									POINT_ARR_CHILK(67, 3)//筛选好友1
									POINT_ARR_CHILK(61, 3)//确认委派
									POINT_ARR_CHILK(65, 3)//委派好友2
									POINT_ARR_CHILK(68, 3)//yj筛选好友2
									POINT_ARR_CHILK(62, 3)//确认委派
									POINT_ARR_CHILK(66, 3)//委派好友3
									POINT_ARR_CHILK(69, 3)//yj筛选好友3
									POINT_ARR_CHILK(63, 3)//确认委派
									POINT_ARR_CHILK(109, 3)//关闭受命所
									POINT_ARR_CHILK(37, 3)//离开家园
									POINT_ARR_CHILK(38, 5)//确定离开
									POINT_ARR_CHILK(92, 5)//点击托管
									POINT_ARR_CHILK(94, 5)//开始托管
									POINT_ARR_CHILK(95, 5)//确定托管
							}
								{
								POINT_ARR_CHILK(93, 3)//小只位置
									POINT_ARR_CHILK(118, 2)//关掉组队
									jiayuan();
										POINT_ARR_CHILK(92, 5)//点击托管
										POINT_ARR_CHILK(94, 5)//开始托管
										POINT_ARR_CHILK(95, 5)//确定托管
										POINT_ARR_CHILK(70, 5)//大号位置
										jiayuan();
										huanfu();
										xuanQu(2); 
										Sleep(28 * 1000);
									 zuzhiliaotian();
									jiayuan();
									huanfu();
									xuanQu(1); 
										Sleep(28 * 1000);
									 
								zuzhiliaotian();
									jiayuan();
									POINT_ARR_CHILK(92, 5)//点击托管
										POINT_ARR_CHILK(94, 5)//开始托管
										POINT_ARR_CHILK(95, 5)//确定托管
										POINT_ARR_CHILK(55, 13)//小号位置
										huanfu();
									xuanQu(1); 
										Sleep(28 * 1000);
									 zuzhiliaotian();
									jiayuan();
									POINT_ARR_CHILK(92, 5)//点击托管
										POINT_ARR_CHILK(94, 5)//开始托管
										POINT_ARR_CHILK(95, 5)//确定托管
								}
									Sleep(3*60*1000);//等待托管完毕
									{
									POINT_ARR_CHILK(117, 3)//回城
										POINT_ARR_CHILK(98, 10)//点击生存
										POINT_ARR_CHILK(99, 3)//点击极限
										POINT_ARR_CHILK(100, 3)//切换极限
										POINT_ARR_CHILK(99, 3)//点击极限
										POINT_ARR_CHILK(100, 3)//确认极限
										POINT_ARR_CHILK(101, 10)//SS
										POINT_ARR_CHILK(104, 3)//开战
										POINT_ARR_CHILK(105, 2)//加速
										POINT_ARR_CHILK(106, 5)//自动
										POINT_ARR_CHILK(70, 7)//大号位置									
											shengcun();
										POINT_ARR_CHILK(93, 5)//小只位置
											shengcun();
										POINT_ARR_CHILK(106, 15)//自动
										for (size_t i = 0; i < 2; ++i) {	
											POINT_ARR_CHILK(55, 3)//小号位置
												POINT_ARR_CHILK(107, 7)//胜利
												POINT_ARR_CHILK(102, 10)//S
												POINT_ARR_CHILK(104, 3)//开战
												POINT_ARR_CHILK(70, 7)//大号位置
												POINT_ARR_CHILK(107, 7)//胜利
												POINT_ARR_CHILK(102, 10)//S
												POINT_ARR_CHILK(104, 3)//开战
												POINT_ARR_CHILK(93, 3)//小只位置
												POINT_ARR_CHILK(107, 7)//胜利
												POINT_ARR_CHILK(102, 10)//S
												POINT_ARR_CHILK(104, 2)//开战																								
										}										
											POINT_ARR_CHILK(55, 3)//小号位置
												POINT_ARR_CHILK(107, 7)//胜利
												POINT_ARR_CHILK(103, 10)//B
												POINT_ARR_CHILK(104, 3)//开战
												POINT_ARR_CHILK(70, 7)//大号位置
												POINT_ARR_CHILK(107, 7)//胜利
												POINT_ARR_CHILK(103, 10)//B
												POINT_ARR_CHILK(104, 3)//开战
												POINT_ARR_CHILK(93, 5)//小只位置
												POINT_ARR_CHILK(107, 7)//胜利
												POINT_ARR_CHILK(103, 10)//B
												POINT_ARR_CHILK(104, 17)//开战																																										
										POINT_ARR_CHILK(55, 5)//小号位置
											guandiaosc();
										POINT_ARR_CHILK(70, 7)//大号位置
											guandiaosc();
										POINT_ARR_CHILK(93, 5)//小只位置
											guandiaosc();										
									}		
		}
	}	
}


void NarutoFunc::OnBnClickedCheckFy() {//八门
	++m_if_zd;
	m_if_zd = m_if_zd % 2;
	if (m_if_zd) {
		findWindow(m_narutoHWND);
		::ShowWindow(m_narutoHWND, SW_MAXIMIZE);
		Sleep(2000);		
		for (size_t j = 0; j < 10; ++j) {
			for (size_t i = 0; i < 10; ++i) {
				chilk(520, 526); Sleep(500);			
				chilk(740, 526);Sleep(500);
				chilk(960, 526);Sleep(500);
				chilk(1180, 526);Sleep(500);
				chilk(1400, 526);Sleep(500);
			}chilk(1480, 585);//一键合成
			Sleep(1000);
		}
	}
}


void NarutoFunc::OnBnClickedCheckPr() {
	++m_if_zd;
	m_if_zd = m_if_zd % 2;
	if (m_if_zd) {
		findWindow(m_narutoHWND);
		::ShowWindow(m_narutoHWND, SW_MAXIMIZE);
		Sleep(2000);
						
	}
}


void NarutoFunc::OnBnClickedCheckJb() {//羁绊
	// TODO: 在此添加控件通知处理程序代码
}


void NarutoFunc::OnBnClickedCheckJbzs() {//劫镖追杀
	// TODO: 在此添加控件通知处理程序代码
}


void NarutoFunc::OnBnClickedCheckDd() {//自动打断
	++m_if_zd;
	m_if_zd = m_if_zd % 2;
	if (m_if_zd) {
		findWindow(m_narutoHWND);
		::ShowWindow(m_narutoHWND, SW_MAXIMIZE);
		Sleep(3000);
		RECT Rect; LPRECT LPrect = &Rect;
		COLORREF color1(RGB(192,0,0));
		COLORREF color2(RGB(217,0,0));
		COLORREF color3(RGB(255,0,0));
		Rect.left = 1110;Rect.top = 353;
		Rect.right = 1515; Rect.bottom = 542;		
		size_t confirm = 0;
		int findY = 1110; int maxY = 1515;
		int findX = 353; int maxX = 542;
		BYTE blue1 = GetBValue(color1);
		BYTE green1 = GetGValue(color1);
		BYTE red1 = GetRValue(color1);
		BYTE blue2 = GetBValue(color2);
		BYTE green2 = GetGValue(color2);
		BYTE red2 = GetRValue(color2);
		BYTE blue3 = GetBValue(color3);
		BYTE green3 = GetGValue(color3);
		BYTE red3 = GetRValue(color3);
		size_t colorIndex = 0;
		BYTE blue = 0; BYTE green = 0; BYTE red = 0;
		BYTE *pBits=new BYTE[306181]; 
		HBITMAP findHBitmap; CBitmap bmp; BITMAP BitMap; 
		//size_t byteCount = BitMap.bmWidthBytes * BitMap.bmHeight;
		while (true) {
			findHBitmap = CopyScreenToBitmap2(LPrect);			
			bmp.Attach(findHBitmap);
			bmp.GetBitmap(&BitMap);
			if (pBits)bmp.GetBitmapBits(306180, pBits);
			while (findY < maxY) {//
				while (findX < maxX) {//
					blue = pBits[colorIndex];
					green = pBits[++colorIndex];
					red = pBits[++colorIndex];
					if (0 == confirm) {//
						if (red == red1 && green == green1 && blue == blue1) {//第一个点					
							++confirm;
						}
					}
					else if (1 == confirm) {
						if (red == red2 && green == green2 && blue == blue2) {//第2个点
							++confirm;
						}
					}
					else {//
						if (red == red3 && green == green3 && blue == blue3) {//第3个点
							++confirm;						
							chilk(findX, findY+150);
							delete[]pBits;
							return ;							
						}
					}
					++findX; colorIndex += 2;
				}//
				if (confirm == 3)return;
				++findY; findX = 1110;
			}
			//if (confirm != 3)AfxMessageBox("没有找到");
			DeleteObject(findHBitmap);
			Sleep(50);
		}
	}
}


void NarutoFunc::OnBnClickedCheckXj() {//龙珠采集1	
	::SetCursorPos(1319, 555);//移动鼠标位置
	Sleep(500);
	for (size_t i = 0; i < 400; ++i) {
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//左键点击抬起
		Sleep(6000);
	}	
}


// 设置当前窗口
bool NarutoFunc::findWindow(HWND top_hwnd) {//想要置顶的窗口句柄
	// TODO: 在此处添加实现代码.
	HWND frontWND = ::GetForegroundWindow();
	if (frontWND!= top_hwnd) {
		::SetForegroundWindow(top_hwnd);
	}	
	return false;
}

inline void chilk(int m_x, int m_pos_y) {
	m_x -= 1; m_pos_y -= 1; srand(1);
	BYTE randValue = rand();
	 m_x += randValue %3; m_pos_y += randValue % 3;
	::SetCursorPos(m_x, m_pos_y);//移动鼠标位置
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//左键点击抬起
	::SetCursorPos(10, 10);//恢复鼠标位置,以免停留致使图标亮着
}
inline void chilkDrag(int m_x, int m_pos_y,int drag_y) {//移动鼠标位置，拖动距离
	m_x -= 1; m_pos_y -= 1; srand(1);
	BYTE randValue = rand();
	m_x += randValue % 3; m_pos_y += randValue % 3;
	::SetCursorPos(m_x, m_pos_y);//移动鼠标位置
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTDOWN , 0, 0, 0, 0);//左键点击抬起| MOUSEEVENTF_LEFTUP
	mouse_event(MOUSEEVENTF_MOVE, 0, drag_y, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
//忍具特训
void NarutoFunc::OnBnClickedCheck1() {	
	++m_if_zd;
	m_if_zd = m_if_zd % 2;
	if (m_if_zd) {
		findWindow(m_narutoHWND);
		::ShowWindow(m_narutoHWND, SW_MAXIMIZE);
		Sleep(3000);
		chilk(633, 197);//限时活动
		RECT loginRect; LPRECT loginLPrect = &loginRect;
		COLORREF color1(RGB(200, 153, 37));
		loginRect.left = 1106;
		loginRect.top = 837;
		loginRect.right = 1109; loginRect.bottom = 840;
		BYTE red1 = GetRValue(color1);
		size_t chilkCount = 0;
		Sleep(2500);
		chilk(490, 649); Sleep(1000);//周末活动
		chilk(972, 627); Sleep(500);
		chilk(992, 627); Sleep(1000);
		BYTE pBits[36]; HBITMAP findHBitmap; CBitmap bmp; BITMAP BitMap; //BYTE red = 0;
		while (true) {
			findHBitmap = CopyScreenToBitmap2(loginLPrect);//登录位图, TRUE			
			bmp.Attach(findHBitmap);
			bmp.GetBitmap(&BitMap);
			if (pBits)bmp.GetBitmapBits(4, pBits);
			if (pBits[2] != red1) {
				chilk(1102, 599);
				++chilkCount;
				if (chilkCount == 3) {
					return;
				}Sleep(1000);
			}
		}
	}
}

HBITMAP NarutoFunc::CopyScreenToBitmap(LPRECT lpRect) {
	HDC       hScrDC, hMemDC;
	// 屏幕和内存设备描述表
	HBITMAP    hBitmap, hOldBitmap;
	// 位图句柄
	int       nX, nY, nX2, nY2;
	// 选定区域坐标
	int       nWidth, nHeight;
	// 确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
		return NULL;
	//为屏幕创建设备描述表
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	//确保选定区域是可见的
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > m_xScreen)
		nX2 = m_xScreen;
	if (nY2 > m_yScreen)
		nY2 = m_yScreen;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// 创建一个与屏幕设备描述表兼容的位图
	hBitmap = CreateCompatibleBitmap
	(hScrDC, nWidth, nHeight);
	// 把新位图选到内存设备描述表中
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);	
		BitBlt(hMemDC, 0, 0, nWidth, nHeight,
			hScrDC, nX, nY, SRCCOPY);	
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	//得到屏幕位图的句柄
	//清除 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC); 	
	return hBitmap;
}
MyPoint  NarutoFunc::areaFindPixel(LPRECT find_lprect, COLORREF color1, COLORREF color2) {
	// TODO: 在此处添加实现代码.
	//float startGameX1 = find_lprect->left / rightScale * right - 2 * GROUP_PIXEL;//开始游戏坐标范围第一点往左上偏移10像素扩大范围
	//float startGameY1 = find_lprect->top / bottomScale * bottom - 2 * GROUP_PIXEL;
	////开始游戏坐标范围第2点(这点不会被计算颜色，因为长度是startGameX2-startGameX1=300,所以只有从startGameX1-第299个点有计算)
	//float startGameX2 = find_lprect->right / rightScale * right + 2 * GROUP_PIXEL;
	//float startGameY2 = find_lprect->bottom / bottomScale * bottom + 2 * GROUP_PIXEL;
	////FULL_SCREEN_SHOT//全屏截图并把全屏位图句柄返回给m_pBitmap		
	//int maxX = (int)startGameX2; int maxY = (int)startGameY2;
	//int findX = (int)startGameX1; int findY = (int)startGameY1;
	int maxX = find_lprect->right; int maxY = find_lprect->bottom;
	int findX = find_lprect->left; int findY = find_lprect->top;
	int confirm = 0;
	RECT findRect;
	/*findRect.left = findX; findRect.top = findY;
	findRect.right = maxX; findRect.bottom = maxY;*/
	findRect.left = find_lprect->left; findRect.top = find_lprect->top;
	findRect.right = find_lprect->right; findRect.bottom = find_lprect->bottom;
	LPRECT findRectPtr = &findRect;
	HBITMAP findHBitmap = CopyScreenToBitmap(findRectPtr);//登录位图, TRUE
	/*CImage loginImage; loginImage.Attach(loginHBitmap);
	loginImage.Detach(); */
	//根据句柄加载位图进缓存
	CBitmap bmp;
	bmp.Attach(findHBitmap);
	BITMAP BitMap;
	bmp.GetBitmap(&BitMap);
	int byteCount = BitMap.bmWidthBytes * BitMap.bmHeight;
	BYTE* pBits = new BYTE[byteCount];
	if (pBits)bmp.GetBitmapBits(byteCount, pBits);//存储顺序BGR文件头图形头		
	size_t colorIndex = 0;
	int blue1 = GetBValue(color1);
	int green1 = GetGValue(color1);
	int red1 = GetRValue(color1);
	int blue2 = GetBValue(color2);
	int green2 = GetGValue(color2);
	int red2 = GetRValue(color2);
	int blue = 0; int green = 0; int red=0;
	while (findY < maxY) {//
		while (findX < maxX) {//
			 blue = pBits[colorIndex];
			 ++colorIndex;
			 green = pBits[colorIndex];
			 ++colorIndex;
			 red = pBits[colorIndex];			
			if (0 == confirm) {//
				if (red == red1 && green == green1 && blue == blue1) {//第一个点					
					++confirm;					
				}
			}
			//else if (1 == confirm) {
			//	if ((red1 - 1) <= red || red <= (red1 + 1) && (green1 - 1) <= green || green <= (green1 + 1) && (blue1 - 1) <= blue || blue <= (blue1 + 1)) {//第一个点
			//		++confirm;
			//	}
			//}
			else {//
				if (red == red2 && green == green2 && blue == blue2) {//第2个点
					++confirm;
					/*CString str1;
					str1.Format("找到2x:%d,y:%d,red:%d,green:%d,blue:%d", findX, findY, red, green, blue);
					MessageBox(_T(str1));*/
					Sleep(50); chilk(findX, findY);
					delete[] pBits;
					return MyPoint(findX, findY);					
				}
			}
			++findX; colorIndex += 2;
		}//
		if (confirm == 2)break;
		++findY; findX = findRect.left;
	}
	//if (confirm != 2)AfxMessageBox("没有找到");
	DeleteObject(findHBitmap);
	delete[] pBits;
	return MyPoint(0, 0);
}
inline size_t writePointToFile(MP point,std::string pointName,char* fileName) {
	FILE* fp;
	errno_t s32Err = ::fopen_s(&fp, fileName, "a");//创建	
	char pointNameBuf[24];
	size_t writeSize = pointName.length() + 10;
	sprintf_s(pointNameBuf, sizeof(pointName), (const char*)& pointName);//字符串转字符数组
	char pointBuf[32]; sprintf_s(pointBuf, _T("%s %d,%d\n"),pointNameBuf,point.x,point.y);
	if(fp)fwrite(pointBuf, 1, writeSize, fp);
	if (fp == 0) return 0;
	else {
		fclose(fp);
		return writeSize;
	}
}
inline void getFilePoint(char *readBuf, std::vector<string>& res, std::vector<string>& res2,MP& recPoint) {	
			 //会覆盖原有数据
	res = split(readBuf, " ");//第一次分割
	res2 = split(res[1], ",");//第2次分割得到坐标
	const char* sToi = res2[0].c_str();
	int x = atoi(sToi);
	const char* sToi2 = res2[1].c_str();
	int y = atoi(sToi2);
	recPoint.x = x; recPoint.y = y;	
}
inline void getFilePoint2(char* readBuf, std::vector<string>& res,MP& recPoint,int& timeLay) {
	res = split(readBuf, " ");//第一次分割	
	const char* sToi = res[1].c_str();
	int x = atoi(sToi);	
	const char* sToi2 = res[2].c_str();
	int y = atoi(sToi2);
	recPoint.x = x; recPoint.y = y;
	const char* sToi3 = res[3].c_str();
	timeLay = atoi(sToi3);
}
inline void getLoopNumber(char* readBuf, std::vector<string>& res, int& loopNumber) {
	res = split(readBuf, " ");//第一次分割
	const char* sToi = res[1].c_str();
	loopNumber = atoi(sToi);
}
inline void fengrao() {
		POINT_ARR_CHILK(15, 5)//选择丰饶
		POINT_ARR_CHILK(16, 3)//进入丰饶
		POINT_ARR_CHILK(17, 2)//扫荡赏金
		POINT_ARR_CHILK(18, 2)//完成扫荡
		POINT_ARR_CHILK(17, 2)//扫荡赏金
		POINT_ARR_CHILK(18, 2)//完成扫荡
		POINT_ARR_CHILK(19, 2)//扫荡食物
		POINT_ARR_CHILK(18, 2)//完成扫荡
		POINT_ARR_CHILK(19, 2)//扫荡食物
		POINT_ARR_CHILK(18, 2)//完成扫荡
		POINT_ARR_CHILK(20, 2)//关闭丰饶
}
inline void zuzhiliaotian() {
	chilk(pointArr[7].x, pointArr[7].y);//关闭福利大厅
	Sleep(2500);
	POINT_ARR_CHILK(121, 3)//本周科技
	chilk(pointArr[8].x, pointArr[8].y);//组织聊天1
	Sleep(2000);
	chilk(pointArr[9].x, pointArr[9].y);//组织聊天2
	Sleep(2000);
	POINT_ARR_CHILK(10, 2)//缩小对话框 214,677
		POINT_ARR_CHILK(11, 2)//隐藏玩家
		POINT_ARR_CHILK(12, 2)//缩小赛季
		POINT_ARR_CHILK(117, 3)//回城
}
inline void denglu_meiriqiandao() {
	chilk(pointArr[0].x, pointArr[0].y);//登录
	Sleep(1000);
	chilk(pointArr[0].x+10, pointArr[0].y+5);
	Sleep(1000);
	chilk(pointArr[0].x + 10, pointArr[0].y + 5);
	Sleep(23 * 1000);
	chilk(pointArr[1].x, pointArr[1].y);//每日签到1
	Sleep(3500);
	chilk(pointArr[2].x, pointArr[2].y);//今日签到
	Sleep(3000);
	chilk(pointArr[3].x, pointArr[3].y);//一键领取
	Sleep(3000);
}
inline void bamendunjia() {
	POINT_ARR_CHILK(21, 2)//提升
	POINT_ARR_CHILK(22, 4)//八门遁甲
	POINT_ARR_CHILK(23, 2)//召唤凯
	POINT_ARR_CHILK(24, 2)//点击召唤1
	POINT_ARR_CHILK(25, 2)//点击召唤2
	POINT_ARR_CHILK(26, 3)//关闭八门遁甲
}

inline void jiayuan() {
	POINT_ARR_CHILK(27, 6)//家园
		POINT_ARR_CHILK(28, 1)//许愿树
		POINT_ARR_CHILK(29, 10)//一键问好
		POINT_ARR_CHILK(31, 2)//关闭羁绊升级框
		POINT_ARR_CHILK(31, 2)
		POINT_ARR_CHILK(31, 2)
		POINT_ARR_CHILK(30, 3)//许愿电卷
		POINT_ARR_CHILK(32, 4)//浇水自己
		POINT_ARR_CHILK(30, 3)//许愿电卷
		POINT_ARR_CHILK(119, 3)//关闭许愿
		POINT_ARR_CHILK(32, 3)//浇水自己
		POINT_ARR_CHILK(33, 4)//许愿树动态
		POINT_ARR_CHILK(34, 5)//一键浇水
		POINT_ARR_CHILK(35, 3)//关闭许愿树动态
		POINT_ARR_CHILK(119, 3)//关闭许愿
		POINT_ARR_CHILK(36, 3)//关闭许愿树
}

inline void tongji() {
	POINT_ARR_CHILK(39, 4)//点击组队
		POINT_ARR_CHILK(40, 4)//创建队伍
		POINT_ARR_CHILK(41, 2)//创建
		POINT_ARR_CHILK(39, 4)//点击组队
		POINT_ARR_CHILK(42, 3)//不允许其他人进入
		POINT_ARR_CHILK(43, 4)//关闭组队框
		for (size_t i = 0; i < 8; ++i) {		
		POINT_ARR_CHILK(13, 1)//叉掉右下角活动	
		}
		POINT_ARR_CHILK(44, 3)//通缉
		POINT_ARR_CHILK(45, 3)//确认通缉			
}

inline void shengcun() {
	POINT_ARR_CHILK(117, 3)//回城
	POINT_ARR_CHILK(98, 10)//点击生存
	POINT_ARR_CHILK(101, 10)//SS
		POINT_ARR_CHILK(104, 3)//开战
		POINT_ARR_CHILK(105, 2)//加速
		POINT_ARR_CHILK(106, 5)//自动
}

inline void guandiaosc() {
	POINT_ARR_CHILK(107, 7)//胜利
		POINT_ARR_CHILK(112, 10)//一键领取
		POINT_ARR_CHILK(113, 7)//确认领取
		POINT_ARR_CHILK(114, 7)//确认获得
		POINT_ARR_CHILK(120, 3)//重置
		POINT_ARR_CHILK(115, 7)//关闭生存
}

inline void huanfu() {
	POINT_ARR_CHILK(56, 3)//换服
		POINT_ARR_CHILK(122, 10)//离开此页
		chilkDrag(1908, 483, 130);//拖动
	Sleep(2000);
	POINT_ARR_CHILK(57, 3)//重新选区		
}

bool NarutoFunc::imageDateComp(CString fileName, LPRECT compRectPtr) {
	HBITMAP hBitmap;
	//BITMAP bm;//获取位图
	hBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 10, 15, LR_LOADFROMFILE);
	int findX = 0; int findY = 0;
	CBitmap image;
	image.Attach(hBitmap);
	BITMAP BitMap;
	image.GetBitmap(&BitMap);
	int byteCount = BitMap.bmWidthBytes * BitMap.bmHeight;
	BYTE* pFileBits = new BYTE[byteCount];
	if (pFileBits)image.GetBitmapBits(byteCount, pFileBits);//图片数据
	RECT compRect;	
	compRect.left = compRectPtr->left; compRect.top = compRectPtr->top;
	compRect.right = compRectPtr->right; compRect.bottom = compRectPtr->bottom;
	LPRECT RectPtr = &compRect;
	HBITMAP compHBitmap = CopyScreenToBitmap(RectPtr);
	CBitmap compBmp;
	compBmp.Attach(compHBitmap);
	BITMAP compBitMap;
	compBmp.GetBitmap(&compBitMap);
	int compbyteCount = compBitMap.bmWidthBytes * compBitMap.bmHeight;
	BYTE* pBits = new BYTE[compbyteCount];
	if (pBits)compBmp.GetBitmapBits(compbyteCount, pBits);//屏幕数据
	size_t colorIndex = 0;
	BYTE red,compRed;
	BYTE green,compGreen;
	BYTE blue,compBlue;
	for (findY; findY < 15; ++findY) {
		findX = 0;
		for (findX; findX < 10; ++findX) {
			blue = pFileBits[colorIndex];			
			compBlue = pBits[colorIndex];
			++colorIndex;
			green = pFileBits[colorIndex];
			compGreen = pBits[colorIndex];
			++colorIndex;
			red = pFileBits[colorIndex];
			compRed = pBits[colorIndex];							
			colorIndex += 2;
			if (blue==compBlue&&green==compGreen&&red==compRed) {
				continue;
			}
			else {
				delete[] pFileBits; delete[] pBits;
				return false;
			}
		}
	}
	delete[] pFileBits; delete[] pBits;
	return true;
}


// //选区
bool NarutoFunc::xuanQu(BYTE qu) {
	RECT compRect1; LPRECT compLPrect1 = &compRect1;
	compRect1.left = 600;
	compRect1.top = 408;
	compRect1.right = 610; compRect1.bottom = 423;
	RECT compRect2; LPRECT compLPrect2 = &compRect2;
	compRect2.left = 795;
	compRect2.top = 408;
	compRect2.right = 805; compRect2.bottom = 423;
	RECT compRect3; LPRECT compLPrect3 = &compRect3;
	compRect3.left = 990;
	compRect3.top = 408;
	compRect3.right = 1000; compRect3.bottom = 423;
	//矩形底部那点不算入数据内,因为底部-顶部才是宽高,而数据是从顶点开始算
	switch (qu) {
	case 1:		
			if (imageDateComp("1.bmp", compLPrect1)) {
				chilk(compRect1.left, compRect1.top);
				return true;
			}
			else if (imageDateComp("1.bmp", compLPrect2)) {
				chilk(compRect2.left, compRect2.top);
				return true;
			}
			else if (imageDateComp("1.bmp", compLPrect3)) {
				chilk(compRect3.left, compRect3.top);
				return true;
			}		
		break;
	case 2:
		if (imageDateComp("2.bmp", compLPrect1)) {
			chilk(compRect1.left, compRect1.top);
			return true;
		}
		else if (imageDateComp("2.bmp", compLPrect2)) {
			chilk(compRect2.left, compRect2.top);
			return true;
		}
		else if (imageDateComp("2.bmp", compLPrect3)) {
			chilk(compRect3.left, compRect3.top);
			return true;
		}
		break;
	case 3:
		if (imageDateComp("3.bmp", compLPrect1)) {
			chilk(compRect1.left, compRect1.top);
			return true;
		}
		else if (imageDateComp("3.bmp", compLPrect2)) {
			chilk(compRect2.left, compRect2.top);
			return true;
		}
		else if (imageDateComp("3.bmp", compLPrect3)) {
			chilk(compRect3.left, compRect3.top);
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}
inline HBITMAP CopyScreenToBitmap2(LPRECT lpRect) {
	HDC       hScrDC, hMemDC;
	// 屏幕和内存设备描述表
	HBITMAP    hBitmap, hOldBitmap;
	// 位图句柄
	int       nX, nY, nX2, nY2;
	// 选定区域坐标
	int       nWidth, nHeight;
	// 确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
		return NULL;
	//为屏幕创建设备描述表
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	//确保选定区域是可见的
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > 1920)
		nX2 = 1920;
	if (nY2 > 1080)
		nY2 = 1080;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// 创建一个与屏幕设备描述表兼容的位图
	hBitmap = CreateCompatibleBitmap
	(hScrDC, nWidth, nHeight);
	// 把新位图选到内存设备描述表中
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	BitBlt(hMemDC, 0, 0, nWidth, nHeight,
		hScrDC, nX, nY, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	//得到屏幕位图的句柄
	//清除 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	return hBitmap;
}
