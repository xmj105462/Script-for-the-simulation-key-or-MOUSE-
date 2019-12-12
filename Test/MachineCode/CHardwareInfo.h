#pragma once
#include <afxstr.h>
typedef char* (__stdcall* GetMAC)(int);
typedef char* (__stdcall* GetCPUInfomation)(int);
typedef char* (__stdcall* GetIdeSN)();
typedef char* (__stdcall* GetBiosSN)();
class CHardwareInfo {//»ñÈ¡»úÆ÷Âë
public:
	CHardwareInfo(void);
	~CHardwareInfo(void);
public:
	void Read();
public:
	CString m_strMACAddress;
	/*CString m_strCPUSerialNumber;
	CString m_strCPUSpecification;
	CString m_strCPUManufacturers;
	CString m_strIDESerialNumber;*/
	CString m_strBIOSSerialNumber;

};

