#pragma once


// NarutoFunc 对话框

class NarutoFunc : public CDialogEx
{
	DECLARE_DYNAMIC(NarutoFunc)

public:
	NarutoFunc(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~NarutoFunc();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FUNC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckQz();
	afx_msg void OnBnClickedCheckZd();
	afx_msg void OnBnClickedCheckSc();
	afx_msg void OnBnClickedCheckFy();
	afx_msg void OnBnClickedCheckPr();
	afx_msg void OnBnClickedCheckJb();
	afx_msg void OnBnClickedCheckJbzs();
	afx_msg void OnBnClickedCheckDd();
	afx_msg void OnBnClickedCheckXj();
	// 获取火影窗口
	bool findWindow(HWND top_hwnd);
	/*int m_x;
	int m_pos_y;*/
	HWND m_narutoHWND;
	// 点击或取消选中
	BOOL m_ok_or_cancel;
	BOOL m_if_zd;
	BOOL m_if_sc;
	BOOL m_if_linshi;
	int m_xScreen;
	int m_yScreen;
	//屏幕宽高
	float right; float bottom ;
	//屏幕分组，5像素一组
	float rightScale ;
	float bottomScale;
	//CBitmap* m_pFSBitmap;
	afx_msg void OnBnClickedCheck1();
	HBITMAP CopyScreenToBitmap(LPRECT lpRect);//,bool bSave, bool bSave=FALSE
	typedef struct MyPoint MP;
	typedef struct MyAreaFindPixel Mafp;
	bool imageDateComp(CString fileName, LPRECT compRectPtr);
	MyPoint  areaFindPixel(LPRECT find_lprect, COLORREF color1, COLORREF color2);//找的区域数组下标矩形
																				 // //选区
	bool xuanQu(BYTE qu);
};
