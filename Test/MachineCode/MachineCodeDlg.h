
// MachineCodeDlg.h: 头文件
//

#pragma once
#include "CHardwareInfo.h"


// CMachineCodeDlg 对话框
class CMachineCodeDlg : public CDialogEx
{
// 构造
public:
	CMachineCodeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MACHINECODE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 机器码
	CString m_machineCode; CHardwareInfo Chwi;
	//CString m_password;

	afx_msg void OnBnClickedButtonLogin();
	
	
	CString m_tip;
};
