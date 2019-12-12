#include "pch.h"
#include "CHardwareInfo.h"
//#include "StdAfx.h"
//#include "HardwareInfo.h"

CHardwareInfo::CHardwareInfo(void) {}

CHardwareInfo::~CHardwareInfo(void) {}
void CHardwareInfo::Read() {
	
	GetMAC getMAC;
	GetCPUInfomation getCPUInfomation;
	GetIdeSN getIdeSN;
	GetBiosSN getBiosSN;
	HINSTANCE hInstDll = LoadLibrary(_T("HWInfo.dll"));
	if (hInstDll != NULL) {
		getMAC = (GetMAC)GetProcAddress(hInstDll, "getMAC");
		getCPUInfomation = (GetCPUInfomation)GetProcAddress(hInstDll, "getCPUInfomation");
		getIdeSN = (GetIdeSN)GetProcAddress(hInstDll, "getIdeSN");
		getBiosSN = (GetBiosSN)GetProcAddress(hInstDll, "getBiosSN");
		m_strMACAddress = CString(getMAC(0));
		/*m_strCPUSerialNumber = CString(getCPUInfomation(1));
		m_strCPUSpecification = CString(getCPUInfomation(2));
		m_strCPUManufacturers = CString(getCPUInfomation(3));
		m_strIDESerialNumber = CString(getIdeSN());*/
		m_strBIOSSerialNumber = CString(getBiosSN());
	}
	
}

